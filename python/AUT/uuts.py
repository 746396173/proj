#coding=gbk
"""
ufns : useful utils
"""
# import ctypes
import greenlet
import os
import sys


# default_encoding = 'gbk'
# if sys.getdefaultencoding() != default_encoding:
    # reload(sys)
    # sys.setdefaultencoding(default_encoding)

#--------------------------log system----------------------------------------
Log_trace = 0
Log_debug = 1
Log_info = 2
Log_warning = 3
Log_error = 4
Log_fatal = 5
_logLvlInfo_ = ["[trace] ", "[debug] ", "[info] ", "[warning] ", "[error] ", "[fatal] "]
_logFile_ = None

def SetLogFile(fileName, mode = "w"):
    global _logFile_
    _logFile_ = open(fileName, mode)

_logStackSize_ = 0
def LogPush():
    global _logStackSize_
    _logStackSize_ += 1

def LogPop():
    global _logStackSize_
    if _logStackSize_ > 0:
        _logStackSize_ -= 1

def LogStackClr():
    global _logStackSize_
    _logStackSize_ = 0

def LogStack(fn):
    def f(*args, **kwargs):
        global _logStackSize_
        old = _logStackSize_
        try:
            LogPush()
            return fn(*args, **kwargs)
        finally:
            _logStackSize_ = old
    return f

def Log(lvl, *infos):
    info = "    " * _logStackSize_
    info += _logLvlInfo_[lvl]
    info += "%s " * len(infos) % infos
    print info
    if _logFile_:
        info += "\n"
        _logFile_.write(info)
        _logFile_.flush()

def LogTrace(*infos):
    return Log(Log_trace, *infos)

def LogDebug(*infos):
    return Log(Log_debug, *infos)

def LogInfo(*infos):
    return Log(Log_info, *infos)

def LogWarning(*infos):
    return Log(Log_warning, *infos)

def LogError(*infos):
    return Log(Log_error, *infos)

def LogFatal(*infos):
    return Log(Log_fatal, *infos)
#------------------------------------------------------------------

class Serialize(object):
    def __init__(self, *args, **kwargs):
        # ֻ���жϵ�һ����������һ��������dict��ʱ���е�����Ҳ���еڶ�������������StrucOp.MemOp
        if len(args) != 0 and isinstance(args[0], dict):
            self._InitDict(*args, **kwargs)
        else:
            self._InitOrd(*args, **kwargs)

    # def __new__(cls, *args, **kwargs):
    #     o = object.__new__(cls, *args, **kwargs)
    #     o.__Init_(*args, **kwargs)
    #     return o

    def __repr__(self):
        v = {}
        self._BuildDict(v)
        BuildDictFromObj(v, self)
        return repr(v)

    #ֻ��Ҫ��ע��������������
    def _InitOrd(self, *args):
        pass

    def _InitDict(self, d):
        pass

    def _BuildDict(self, d):
        pass

    def WriteToFile(self, fileName):
        ObjToFile(fileName, self)

    def PrintDbgInfo(self):
        pass


class ProxyBase(Serialize):
    _impl_ = None

    def _InitOrd(self, impl):
        self._impl_ = impl

    def __getattr__(self, item):
        # if not self._impl_:
        #     return object.__getattr__(self, item)
        return getattr(self._impl_, item)

    def __setattr__(self, key, value):
        if hasattr(self._impl_, key):
            setattr(self._impl_, key, value)
        else:
            object.__setattr__(self, key, value)


class MultiIterCall(Serialize):
    """
     ���ģʽ������������ã�����itertools.chain����MultiIterCall���ڵ��ý׶ν��������������itertools.chainֻ���ڳ�ʼ��ʱ���������
    """
    def _InitDict(self, d):
        self._fns_ = [BuildObj(x) for x in d["_fns_"]]

    def _InitOrd(self, *fns):
        self._fns_ = []
        for item in fns:
            self.Add(item)

    def _BuildDict(self, d):
        d["_fns_"] = self._fns_

    def __call__(self, *args, **kwargs):
        for impl in self._fns_:
            for res in impl(*args, **kwargs):
                yield res

    def Add(self, fn):
        if fn is None:
            return
        self._fns_.append(fn)

    def AddFromFile(self, fileName):
        self.Add(ObjFromFile(fileName))

    def AddFromFiles(self, dir, subFileName):
        for f in IterDirFiles(dir, subFileName):
            self.AddFromFile(f)

    @LogStack
    def PrintDbgInfo(self):
        LogDebug("#---------------%s��ʼ--------------" % self.__class__.__name__)
        LogDebug("�ܸ�����", len(self._fns_))
        for i in self._fns_:
            i.PrintDbgInfo()
        LogDebug("#---------------%s����--------------" % self.__class__.__name__)

    def ItemSize(self):
        return len(self._fns_)


class ObjChain(object):
    def __init__(self, *objs):
        self.__dict__["__obj_"] = objs

    def __getattr__(self, item):
        for i in self.__dict__["__obj_"]:
            if hasattr(i, item):
                return getattr(i, item)
        return object.__getattr__(self, item)

    def __setattr__(self, key, value):
        for i in self.__dict__["__obj_"]:
            if hasattr(i, key):
                setattr(i, key, value)
                break


class Dict(dict):
    """
     ������������
    """
    def __init__(self, d):
        dict.__init__(self, {})
        self.__other_ = d


    def __getitem__(self, item):
        if not self.__other_ or self.has_key(item):
            return dict.__getitem__(self, item)
        return self.__other_[item]


    def __setitem__(self, key, value):
        if not self.__other_ or self.has_key(key):
            dict.__setitem__(self, key, value)
        else:
            if self.__other_.has_key(key):
                self.__other_[key] = value
            else:
                dict.__setitem__(self, key, value)


class Dicts(dict):
    """
     ������������
    """
    def __init__(self, *dicts):
        dict.__init__(self, {})
        self.__others_ = dicts


    def __getitem__(self, item):
        if not self.__others_ or self.has_key(item):
            return dict.__getitem__(self, item)
        for i in self.__others_:
            if i.has_key(item):
                return i[item]
        return dict.__getitem__(self, item)


    def __setitem__(self, key, value):
        if not self.__others_ or self.has_key(key):
            dict.__setitem__(self, key, value)
        else:
            for i in self.__others_:
                if i.has_key(key):
                    i[key] = value
                    break
            else:
                dict.__setitem__(self, key, value)

def ClsDicts(cls):
    dicts = [cls.__dict__]
    for i in cls.__bases__:
        dicts += ClsDicts(i)
    return dicts

def ObjDicts(obj):
    dicts = [obj.__dict__]
    dicts += ClsDicts(obj.__class__)
    return dicts

_execStdFns_ = compile("""
def SetRes(res):
    global __res_
    __res_ = res
    """, '', 'exec');
def Exec(str, l = None, g = None):
    """
    globals()�õ����ǵ�ǰģ�飬�����ǵ����ߵ�ģ�飬�������õ����ߵ�ģ�飬���ڵ���ʱ��globals()��
    ��g��None����Ĭ��ȫ���������ֻ��d����gΪ�ֵ䣬��������Χ�ǣ���d��g��
    ��l��None�������ȫ�ֺ����ͱ�������d�ֵ��У���������l�С�
    """
    d = Dict(g)
    d["__res_"] = None

    global _execStdFns_
    exec(_execStdFns_, d, None)
    exec(str, d, l)
    return d["__res_"]


def Execs(str, l = None, *g):
    """
    look Exec
    """
    glo = [x for x in g if x is not None]
    if len(glo) <= 0:
        d = Dicts()
    else:
        d = Dicts(*glo)
    d["__res_"] = None

    global _execStdFns_
    exec(_execStdFns_, d, None)
    exec(str, d, l)
    return d["__res_"]


def ExecsAtObj(str, obj, l = None, *g):
    dicts = ObjDicts(obj)
    dicts += list(g)
    return Execs(str, obj, l, *dicts)


class ExecEnv:
    def __init__(self, obj, l = None, *g):
        dicts = ObjDicts(obj)
        dicts += list(g)

        glo = [x for x in dicts if x is not None]
        if len(glo) <= 0:
            self.d = Dicts()
        else:
            self.d = Dicts(*glo)
        self.l = l

        global _execStdFns_
        exec (_execStdFns_, self.d, None)

    def __call__(self, str):
        self.d["__res_"] = None
        exec (str, self.d, self.l)
        return self.d["__res_"]


class ValueRange:
    def __init__(self, begin=0, end=0):
        assert end >= begin
        self.begin_ = begin
        self.end_ = end


    def IsInRange(self, value):
        return value >= self.begin_ and value < self.end_


    def OffsetToBegin(self, value):
        return value - self.begin_


    def Size(self):
        return self.end_ - self.begin_


    def ExistIntersection(self, rhs):
        """
        �Ƿ���ڽ���
        """
        if self.begin_ < rhs.begin_:
            if self.end_ > rhs.begin_:
                return  True
        else:
            if rhs.end_ > self.begin_:
                return True
        return False


    def IsProximity(self, rhs):
        """
        �Ƿ�����
        """
        if rhs.begin_ - self.end_ == 0:
            return True
        if self.begin_ - rhs.end_ == 0:
            return True
        return False


    def CalcIntersection(self, rhs):
        """
         ���㽻��
        """
        res = ValueRange()
        if self.begin_ < rhs.begin_:
            if self.end_ > rhs.begin_:
                res.begin_ = rhs.begin_
                if self.end_ > rhs.end_:
                    res.end_ = rhs.end_
                else:
                    res.end_ = self.end_
        else:
            if rhs.end_ > self.begin_:
                res.begin_ = self.begin_
                if rhs.end_ > self.end_:
                    res.end_ = self.end_
                else:
                    res.end_ = rhs.end_
        return res


    def CalcUnion(self, rhs):
        """
        ���㽻��
        """
        res = ValueRange()
        res.begin_ = min(self.begin_, rhs.begin_)
        res.end_ = max(self.end_, rhs.end_)
        return res

    def __repr__(self):
        return "%x, %x" % (self.begin_, self.end_)


def BasicTypes():
    return (int, long, basestring, float, dict, tuple, list, bool)


def FilterTypes(types):
    return lambda v: isinstance(v, types)


def LookObj(obj, filter_ = FilterTypes(BasicTypes()), beg = "__"):
    for i in dir(obj):
        if i.startswith(beg):
            continue
        v = getattr(obj, i)
        if filter_:
            if filter_(v):
                yield (i, v)
        else:
            yield i, v


def singleton(cls):
    instances = {}
    def _singleton(*args, **kw):
        if cls not in instances:
            instances[cls] = cls(*args, **kw)
        return instances[cls]
    return _singleton


def BuildDictFromObj(d, o):
    d["__name__"] = o.__module__ + "." + o.__class__.__name__


def BuildObjFromDict(d, g):
    name = d["__name__"]
    cls = eval(name, g)
    if cls is None:
        assert False, "BuildObjFromDictʧ�ܣ�name:%s" % name
        return
    return cls(d)


def DefGlobal():
    return globals()

def BuildObj(p):
    if p is None:
        return
    g = DefGlobal()
    if isinstance(p, dict):
        return BuildObjFromDict(p, g)
    elif isinstance(p, basestring):
        return BuildObjFromDict(eval(p, g), g)
    else:
        assert False, "BuildObj����Ŀ������Ϊ��%s" % type(p)


#Glet : greenlet
def GletParentSwitch(*args, **kwargs):
    glet = greenlet.getcurrent()
    if glet and glet.parent:
        return True, glet.parent.switch(*args, **kwargs)
    return (False,)


def Gbk2Utf8(str):
    if not str:
        return
    str = str.decode('gbk')
    return str.encode('utf-8')

def Utf82Gbk(str):
    if not str:
        return
    str = str.decode('utf-8')
    return str.encode('gbk')

def StrFromUStr(str):
    return Utf82Gbk(str)

def ObjToUStr(obj):
    return Gbk2Utf8(repr(obj))

def ObjFromUStr(str):
    return BuildObj(Utf82Gbk(str))

def ObjFromFile(strFileName):
    f = open(strFileName, "r")
    try:
        return BuildObj(f.read())
    finally:
        f.close()

def ObjToFile(strFileName, obj):
    f = open(strFileName, "w")
    try:
        f.write(repr(obj))
    finally:
        f.close()

def IterDirFiles(dir, subFileName):
    for dirpath, dirnames, filenames in os.walk(dir):
        for f in filenames:
            # fname = os.path.splitext(f)   #���ļ���ת����Ԫ��(fileName, ��׺��)
            if f.find(subFileName) >= 0:
                yield os.path.join(dirpath, f)

def FindFirstDirFile(dir, subFileName):
    for f in IterDirFiles(dir, subFileName):
        return f


def NormalPathCase(p):
    p = os.path.normpath(p)
    return os.path.normcase(p)


def CurFileDir():
    path = sys.path[-1]
    if os.path.isdir(path):
        return path
    elif os.path.isfile(path):
        return os.path.dirname(path)