#coding=gbk
"""
idaaut : ida auto update
"""
import idaapi
import idc
import idautils
import idaex
import uuts
import traceback
import Queue
import greenlet
import os

#----------------------------------------------------------------
#-------------------------------˵��---------------------------------------
#------------�����ǽ���
#ȫ���Զ�������һ����'@'��ͷ�������ھֲ���������ν��
#ȫ�ֱ�����"g"ǰ׺��
#ȫ�ֺ�����"f"ǰ׺��
#����������"l"ǰ׺��
#����˵�����ַ���(Ĭ���ֽڴ�СΪ1)��s�����飺a������/�ṹ�壺c��ָ�룺p���޷��ţ�u��������f�����㣺d��ָ��(insn)��i��ƫ��(Ĭ��Ϊ�з���)��o������(Ĭ���ֽڴ�СΪ1)��b��
#���ݴ�С���ֽ�Ϊ��λ�����֣���1��2��4��8�����ֱ��Ӧ��char��short��int��longlong����
#����������֮ǰҪ��'_'
#---�������ݸ�ʽʾ��
# ��Ա�����ĸ�ʽ��@f_ClassName_FunctionName��
# ȫ�ֶ��ֽ��ַ�����@gs_StrName��
# ȫ��utf16�ַ�����@gs2_StrName��
# ȫ��uint��@gu4_Name��
# ȫ��int*��@gp4_Name��
# ȫ�ֽṹ��ָ�룺@gpc_Name��
# ȫ�ֽṹ�������@gc_Name��
# uint�ı��ر�����lu4_Name��
#------------������Լ��
#lineA��Ĵ�������Դidb���ݿ���ִ�еģ����������ɶ�λ������Ķ���ġ�
#lineB��Ĵ�������Ŀ��idbִ�еģ���Ҫ�������º�ϸ΢֮���Ķ���֮��ģ������жϸõ�ַ��õ�ַ�����������Ƿ����������⡣
#lineB��ȻҲ�������������ݸõ�ַָʾ��ƫ�ƣ�������ĳ���ṹ���Ա��ƫ�ƣ���������enum��������ֵ��
#OpFn�ܹ��Զ�ʶ��������ڲ����õ�ȫ�����ƣ�ȫ�ֱ������������ڸ��µ�ʱ���Զ�����Щ���ø����ó���Ӧ�����ơ�
#OpFn�����ڲ�ĳ��ַ���Ƿ���ע�ͣ�����ע�ͣ�lineA��lineB��cmt��repeat cmt����(�����ע��)���Զ�������Ӧ�Ĳ�������Ϣ��o_imm��o_mem��o_phrase��o_displ����
#��������Ϣ��o_imm��Immediate Value. o_mem��Direct Memory Reference  (DATA). o_phrase��Memory Ref [Base Reg + Index Reg]. o_displ��Memory Reg [Base Reg + Index Reg + Displacement].
#-------------�������������
#��ʹ�ñ��ļ�����ǰ������Ҫ������DefGlobal����������uuts.DefGlobal = lambda : globals()
#uuts.SetLogFile("f:/tmp/tmp/log.txt")������������log�ļ��ģ����û�����ã��򲻻����log���ļ��С�
#���ó�����󱣴���ļ���idaaut.SetErrorObjFile("f:/tmp/tmp/errorObj.txt", "f:/tmp/tmp/continueErrorObj.txt")��
#-------------�������÷�
#EnvObjMgr�����ĳ�Ա�����õ��Ķ��󱣴���idb�ļ�Ҫ���µ���Ϣ������԰���Щ��Ϣ�������ļ��У���������obj.WriteToFile("f:/tmp/tmp/obj.txt")
#EnvObjMgr��name list���������֣�����ָ����ǰ׺��ָ�������֣�������������Щ������ȫ�ֱ����Ķ���ǰ׺��ָ�������ֿ��޸������ã�����ȥ��EnvObjMgr��ʵ�֡�
#Interface�еĳ�Ա��������ִ��EnvObjMgr���ɵĶ���Ҳ���ǽ��и��µĲ�������֧��xmlrpc��������ã�Ҳ֧��ͨ����ȡ�ļ�����ȡ�����ٵ��á�
#EaEnvGen����������������lineA��lineA��ȫ�ֱ���self��ָ����һ��EaEnvGen����
#EaEnvRun����������������lineB��lineB��ȫ�ֱ���self��ָ����һ��EaEnvRun����
#-------------�����㷨��ظ���
#��һ����ַ���и��£���Ҫ�����֣���λ�Ͳ�����
#��λ(Finder)����Ҫ���Ҷ�λ�������뷽ʽ����ǰ׺ΪLoc��һ�����ʾ��
#���⣬Finder��Ҫ��λ����ȷ�����ݣ�����Ҫǰ�ö��ԡ�ת��������ö��ԣ�ǰ�ö��Ժͺ��ö�����ǰ׺ΪAssert��һ�����ʾ��ת������ǰ׺ΪTr��һ�����ʾ��
#ǰ�ö��ԣ�Loc�õ�һ����ַ���Ƚ���ǰ�ö��Դ�������ͨ����Loc��ȥ������һ��ַ����ͨ���ɽ���Tr������
#ת����������ǰ�ö��Դ��ݹ����ĵ�ַ�����ж���ת��������ɹ��򷵻ص�����ĵ�ַ�����ö��ԣ�����Loc��ȥ������һ��ַ��
#���ö��ԣ�����ǰ�ö��Ի�ת�����������ĵ�ַ���������жϣ���ͨ����Finder���ҵ������յĵ�ַ������Loc��ȥ������һ��ַ��
#Finder��Loc����Ϊ�գ���������Ϊ�ա�
#������Op���ص�һ���࣬���ڶ�Finder�õ��ĵ�ַ���в�����
#----------------------------------------------------------------------------------
#--------------��������---------------------------------------------
#���²��������ȼ����壬��ֵԽС�Ż���Խ�ߡ�UPL -> Update Priority Level
UPL_Enum = 1
UPL_Struct = 1000
UPL_Func = 2000
UPL_Chunk = 3000
UPL_GloData = 4000
UPL_Last = 10000
#----------------------------------------------------------------------------------
#----------------------------------------------------------------
#ea����
class _EaEnvBase:
    # ��ǰ�ĵ�ַ
    curEa = idc.BADADDR

#ea�������������ɶ���
class EaEnvGen(_EaEnvBase):
    """
    GF: Gen Finder
    GOF: Gen Operate Function
    GOD: Gen Operate Data
    """
    #��ǰ���ɵ�loc(��λ��)
    curLoc = None
    #��ǰ��ǰ�ö���
    curPa = None
    #��ǰ��ת����
    curTr = None
    #��ǰ�ĺ��ö���
    curAa = None
    #��ǰ���ɵĲ���
    curOp = None

    def _Reset(self):
        self.curLoc = None
        self.curPa = None
        self.curTr = None
        self.curAa = None
        self.curOp = None

    def GF_FnBiOrd(self, offsetBegin = 0, offsetSize = 20, fnCheckSum = True, occurCnt = None):
        """
        �򵥳��õĶ���������
        Bi : Binary
        """
        seg = idaapi.getseg(self.curEa)
        if not seg:
            assert False, "FnBiOrd֮û�ҵ�����"
            return
        fnRange = idaex.EaRangeFn(self.curEa)
        subRange = fnRange.SubRange(offsetBegin, offsetSize, True)
        bvalue = idaex.GenBinary(subRange.eaBegin, subRange.eaEnd)
        findRange = idaex.EaRangeSegName(idaapi.get_true_segm_name(seg))
        self.curLoc = LocBinary(bvalue, findRange)
        self.curPa = AssertAllOf(AssertFuncSize(fnRange.Size()))
        if fnCheckSum:
            sumSrc = idaex.FuncFullCheck(subRange.eaBegin, fnRange.eaEnd)
            sumDst = AssertFuncFullCheck(sumSrc)
            self.curPa.Add(sumDst)
        if occurCnt is not None:
            self.curPa.Add(AssertAsCnt(occurCnt))
        self.curTr = TrFnOffsetStart(-offsetBegin)

    def GF_FnCrefByName(self, fnSubName, isFnOffset=None, fnCheckSum=True):
        """
        �򵥳��õ�code ref by name
        GF : Gen Finder
        """
        frm, to = idaex.FindNameOfFuncCallsFrom(fnSubName, self.curEa)
        self.curLoc = LocCodeRefTo(to, isFnOffset)
        fnRange = idaex.EaRangeFn(self.curEa)
        if fnCheckSum:
            # AssertFuncFullCheck���ǵ���ǰ�ö��ԵĻ�����֤���Ǵ�frm��������β��check sum��
            sumSrc = idaex.FuncFullCheck(fnRange.eaBegin, fnRange.eaEnd)
            self.curAa = AssertFuncFullCheck(sumSrc)
        self.curPa = AssertFuncSize(fnRange.Size())
        self.curTr = TrFnOffsetStart(self.curEa - frm)

    def GF_FnDrefByName(self, subName, fnCheckSum=True):
        """
        �򵥳��õ�data ref by name
        GF : Gen Finder
        """
        frm, to = idaex.FindNameOfFuncDrefFrom(subName, self.curEa)
        self.curLoc = LocDataRefTo(to)
        fnRange = idaex.EaRangeFn(self.curEa)
        if fnCheckSum:
            sumSrc = idaex.FuncFullCheck(fnRange.eaBegin, fnRange.eaEnd)
            # AssertFuncFullCheck���ǵ���ǰ�ö��ԵĻ�����֤���Ǵ�frm��������β��check sum��
            self.curAa = AssertFuncFullCheck(sumSrc)
        self.curPa = AssertFuncSize(fnRange.Size())
        self.curTr = TrFnOffsetStart(self.curEa - frm)

    def GF_FnDrefByText(self, subStartText, fnCheckSum=True):
        """
        �򵥳��õ�data ref by text
        GF : Gen Finder
        """
        frm, to = idaex.FindTextOfFuncTextFrom(subStartText, self.curEa)
        # ��to��Ŀ�����ݿ���δ�ҵ����֣�����subStartTextѰ��
        self.curLoc = LocDataRefTo(idaex.NetnodeText(to, subStartText))
        fnRange = idaex.EaRangeFn(self.curEa)
        if fnCheckSum:
            sumSrc = idaex.FuncFullCheck(fnRange.eaBegin, fnRange.eaEnd)
            # AssertFuncFullCheck���ǵ���ǰ�ö��ԵĻ�����֤���Ǵ�frm��������β��check sum��
            self.curAa = AssertFuncFullCheck(sumSrc)
        self.curPa = AssertFuncSize(fnRange.Size())
        self.curTr = TrFnOffsetStart(self.curEa - frm)

    def GF_FnXrefAuto(self, startswidth=None, fnCheckSum=True):
        """
        ���ܵõ������е��Ѵ��ڵ�ȫ������
        GF : Gen Finder
        """
        xref = idaex.FindAnyFnXrefFrom(self.curEa, startswidth)
        self.curLoc = LocXrefTo(xref.to, xref.type, xref.iscode, xref.user)
        fnRange = idaex.EaRangeFn(self.curEa)
        if fnCheckSum:
            sumSrc = idaex.FuncFullCheck(fnRange.eaBegin, fnRange.eaEnd)
            # AssertFuncFullCheck���ǵ���ǰ�ö��ԵĻ�����֤���Ǵ�frm��������β��check sum��
            self.curAa = AssertFuncFullCheck(sumSrc)
        self.curPa = AssertFuncSize(fnRange.Size())
        self.curTr = TrFnOffsetStart(self.curEa - xref.frm)

    def GF_ByNameNormal(self):
        self.curLoc = LocByGloName(self.curEa)

    def GOF_Normal(self):
        self.curOp = OpFn(self.curEa)

    def GOD_Normal(self, doUknFlag=idc.DOUNK_SIMPLE):
        """
        DOUNK_SIMPLE��ʱ��ʧ�ܣ�DOUNK_DELNAMES�ܹ��������ʧ�ܵ������������ڴ�����������ʱ��DOUNK_SIMPLE��ʧ�ܡ�
        """
        self.curOp = OpData(self.curEa, doUknFlag)


#ea����������ִ�У����ڸ��º��ִ��
class EaEnvRun(_EaEnvBase):
    pass

#--------------------------ͨ�Žӿ�------------------------------
@uuts.singleton
class Interface:
    """
     ���½ӿ�
    """
    def __init__(self, changeCoding):
        self.changeCoding = changeCoding

    #ִ��һ������
    def Exec(self, execStr, dictLocal, dictGlobal):
        try:
            if self.changeCoding:
                execStr = uuts.StrFromUStr(execStr)
            res = uuts.Execs(execStr, dictLocal, dictGlobal, uuts.DefGlobal())
            if self.changeCoding:
                res = uuts.ObjToUStr(res)
            return res
        except:
            # traceback.print_exc()
            uuts.LogError(traceback.format_exc())
            # return False, traceback.format_exc()

    def ExecObj(self, strObj):
        if self.changeCoding:
            strObj = uuts.StrFromUStr(strObj)
        obj = uuts.BuildObj(strObj)
        res = obj()
        if self.changeCoding:
            res = uuts.ObjToUStr(res)
        return res

    def ExecObjFromFile(self, strFilePath):
        if self.changeCoding:
            strFilePath = uuts.StrFromUStr(strFilePath)
        obj = uuts.ObjFromFile(strFilePath)
        res = obj()
        if self.changeCoding:
            res = uuts.ObjToUStr(res)
        return res

    def ExecObjFromFiles(self, strMainFile, subFileName):
        if self.changeCoding:
            strMainFile = uuts.StrFromUStr(strMainFile)
            subFileName = uuts.StrFromUStr(subFileName)
        strMainFile = uuts.NormalPathCase(strMainFile)
        obj = uuts.ObjFromFile(strMainFile)
        dir = os.path.dirname(strMainFile)
        for f in uuts.IterDirFiles(dir, subFileName):
            f = uuts.NormalPathCase(f)
            if f != strMainFile:
                obj.AddFromFile(f)
        res = obj()
        if self.changeCoding:
            res = uuts.ObjToUStr(res)
        return res


#----------------------------------------------------------------
#---------------------global variable-------------------------
def _GenDefCodeRange():
    res = uuts.ValueRange()
    for n in xrange(idaapi.get_segm_qty()):
        seg = idaapi.getnseg(n)
        if seg:
           if idc.SEG_CODE == idc.GetSegmentAttr(seg.startEA, idc.SEGATTR_TYPE):
               if res.begin_ == 0:
                    res.begin_ = seg.startEA
                    res.end_ = seg.endEA
               else:
                    v = uuts.ValueRange(seg.startEA, seg.endEA)
                    if res.IsProximity(v):
                        res = res.CalcUnion(v)
                    else:
                        break
    return res

defCodeAddr = _GenDefCodeRange()
#----------------------------------------------------------------
#----------------------------------------------------------------
class Finder(uuts.Serialize):
    """
     loc_ : locator,��λ��ʽ����λ��������λ����
     pa_ : pre assert,ǰ�ö���
     tr_ : translator,ת����
     aa_ : after assert,���ö���
     ea_ : result address
    """
    ea_ = idc.BADADDR
    errorPos = -2

    #init ordinary
    def _InitOrd(self, loc, pa = None, tr = None, aa = None):
        self.loc_ = loc
        assert self.loc_
        self.pa_ = pa
        self.tr_ = tr
        self.aa_ = aa

    def _InitDict(self, d):
        self.loc_ = uuts.BuildObj(d["loc"])
        assert self.loc_
        self.pa_ = uuts.BuildObj(d["pa"])
        self.tr_ = uuts.BuildObj(d["tr"])
        self.aa_ = uuts.BuildObj(d["aa"])

    @uuts.LogStack
    def Do(self, isDbg = False):
        """
         �㷨���ģ����в��Ҷ�λ�������Թ���
        """
        cnt = 0
        self.errorPos = -1
        for ea in self.loc_():
            cnt += 1
            self.errorPos = 0
            self.ea_ = ea
            if self.pa_ and self.pa_(ea, cnt) <= 0:
                if isDbg:
                    uuts.LogDebug("Finder.DebugDo֮ǰ�ö���ʧ�ܣ���ַ: %x " % ea)
                    self.pa_.PrintDbgInfo()
                continue
            if self.tr_:
                self.errorPos = 1
                ea = self.tr_(ea)
                self.ea_ = ea
                self.errorPos = 2
                if ea is None or ea == idc.BADADDR or ea == -1 or ea == 0:
                    if isDbg:
                        uuts.LogDebug("Finder.DebugDo֮ת��������ʧ�ܣ�ת����ĵ�ַ: %x " % ea)
                        self.tr_.PrintDbgInfo()
                    continue
            self.errorPos = 3
            if self.aa_ and self.aa_(ea, cnt) <= 0:
                if isDbg:
                    uuts.LogDebug("Finder.DebugDo֮���ö���ʧ�ܣ���ַ: %x " % ea)
                    self.aa_.PrintDbgInfo()
                continue
            self.errorPos = -2
            return ea
        if cnt == 0:
            self.errorPos = 4
            if isDbg:
                uuts.LogDebug("Finder.DebugDo֮û�ж�λ���κε�ַ")
                self.loc_.PrintDbgInfo()
        return 0

    @uuts.LogStack
    def PrintDbgInfo(self):
        if self.errorPos == -2:
            return
        uuts.LogDebug("-----������Finder�����ҵ��ĵ�ַ�Ĵ�����Ϣ")
        if self.errorPos == -1:
            uuts.LogDebug("finder���ƽ�����ѭ������")
        elif self.errorPos == 0:
            uuts.LogDebug("ǰ�ö���ʧ�ܣ���ַ: %x " % self.ea_)
            self.pa_.PrintDbgInfo()
        elif self.errorPos == 1:
            uuts.LogDebug("ת����ʧ�ܣ���ַ: %x " % self.ea_)
            self.tr_.PrintDbgInfo()
        elif self.errorPos == 2:
            uuts.LogDebug("�ҵ��˵�ַ������ת��������ʧ�ܣ�ת����ĵ�ַ��%x" % self.ea_)
            self.tr_.PrintDbgInfo()
        elif self.errorPos == 3:
            uuts.LogDebug("���ö���ʧ�ܣ���ַ: %x "%self.ea_)
            self.aa_.PrintDbgInfo()
        else:
            uuts.LogDebug("û�ж�λ���κε�ַ")
            self.loc_.PrintDbgInfo()
        uuts.LogDebug("-----������Finder���ҵ�ÿ����ַ����ϸ������Ϣ")

        try:
            self.Do(True)
        except:
            uuts.LogError("Finder֮DebugDo�����쳣\n", traceback.format_exc())
        uuts.LogDebug("-----������Finder�ĳ�����Ϣ�����˽���---------------------")

    def _BuildDict(self, d):
        d["loc"] = self.loc_
        d["pa"] = self.pa_
        d["tr"] = self.tr_
        d["aa"] = self.aa_


class LocMulti(uuts.MultiIterCall):
    """
    loc : locator
    """
    pass

class _LocBase(uuts.Serialize):
    def _InitOrd(self, value, eaRange, flag=idc.SEARCH_DOWN | idc.SEARCH_NOSHOW):
        self.value = value
        self.eaRange = eaRange
        self.flag = flag

    def _InitDict(self, d):
        self.value = d["value"]
        self.eaRange = uuts.BuildObj(d["eaRange"])
        self.flag = d["flag"]

    def __call__(self, *args, **kwargs):
        return self.iterFn(self.value, self.eaRange.eaBegin, self.eaRange.eaEnd, self.flag)

    def _BuildDict(self, d):
        d["value"] = self.value
        d["eaRange"] = self.eaRange
        d["flag"] = self.flag


class LocByGloName(uuts.Serialize):
    """
    by global name
    """
    def _InitOrd(self, netnodeId):
        self.nnode = idaex.Netnode(netnodeId)

    def _InitDict(self, d):
        self.nnode_ = d["nnode"]
        self.nnode = None

    def _BuildDict(self, d):
        if self.nnode:
            d["nnode"] = self.nnode
        else:
            d["nnode"] = self.nnode_

    def __call__(self, *args, **kwargs):
        if not self.nnode:
            self.nnode = uuts.BuildObj(self.nnode_)
        yield self.nnode.id


class LocBinary(_LocBase):
    iterFn = lambda self, *args: idaex.IterBinary(*args)

    def PrintDbgInfo(self):
        uuts.LogDebug("LocBinary,eaRange")
        self.eaRange.PrintDbgInfo()


class LocMnem(_LocBase):
    iterFn = lambda self, *args: idaex.IterMnem(*args)

    def PrintDbgInfo(self):
        uuts.LogDebug("LocMnem,eaRange")
        self.eaRange.PrintDbgInfo()


class LocText(_LocBase):
    iterFn = lambda self, *args : idaex.IterText(*args)

    def PrintDbgInfo(self):
        uuts.LogDebug("LocText,eaRange")
        self.eaRange.PrintDbgInfo()


class LocImme(_LocBase):
    iterFn = lambda self, *args : idaex.IterImme(*args)

    def PrintDbgInfo(self):
        uuts.LogDebug("LocImme,eaRange")
        self.eaRange.PrintDbgInfo()


class _LocCrossRefBase(uuts.Serialize):
    def _InitOrd(self, netnode, isTo, isCode):
        self.netnode = netnode
        self.isTo = isTo
        self.isCode = isCode
        if isCode == True:
            if isTo == True:
                self.iterFn = lambda ea: idautils.CodeRefsTo(ea, 0)
            else:
                self.iterFn = lambda ea: idautils.CodeRefsFrom(ea, 0)
        else:
            if isTo == True:
                self.iterFn = idautils.DataRefsTo
            else:
                self.iterFn = idautils.DataRefsFrom

    def _InitDict(self, d):
        self.nnode_ = d["nnode"]
        _LocCrossRefBase._InitOrd(self, None, d["isTo"], d["isCode"])

    def _BuildDict(self, d):
        if self.netnode:
            d["nnode"] = self.netnode
        else:
            d["nnode"] = self.nnode_
        d["isTo"] = self.isTo
        d["isCode"] = self.isCode

    def __call__(self, *args, **kwargs):
        if not self.netnode:
            self.netnode = uuts.BuildObj(self.nnode_)
        return self.iterFn(self.netnode.id)


class _LocCrossRef(_LocCrossRefBase):
    def _InitOrd(self, nnode, isFnOffset, isTo, isCode):
        if not isinstance(nnode, idaex.Netnode):
            if isFnOffset == None:
                nnode = idaex.Netnode(nnode)
            elif isFnOffset == True:
                nnode = idaex.NetnodeFnOffset(nnode)
            else:
                nnode = idaex.NetnodeFnInsn(nnode)
        _LocCrossRefBase._InitOrd(self, nnode, isTo, isCode)


class LocCodeRefTo(_LocCrossRef):
    def _InitOrd(self, nnode, isFnOffset = None):
        _LocCrossRef._InitOrd(self, nnode, isFnOffset, True, True)


class LocCodeRefFrom(_LocCrossRef):
    def _InitOrd(self, nnode, isFnOffset = None):
        _LocCrossRef._InitOrd(self, nnode, isFnOffset, False, True)


class LocDataRefTo(_LocCrossRef):
    def _InitOrd(self, nnode):
        #DataRefTo��Ե������ݵ�ַ
        _LocCrossRef._InitOrd(self, nnode, None, True, False)


class LocDataRefFrom(_LocCrossRef):
    def _InitOrd(self, nnode, isFnOffset = None):
        #DataRefFrom��Լȿ����Ǵ����ַ��Ҳ���������ݵ�ַ�����ݵ�ַʱisFnOffset����None
        _LocCrossRef._InitOrd(self, nnode, isFnOffset, False, False)


class _LocXrefBase(uuts.Serialize):
    def _InitDict(self, d):
        self.type = d["type"]
        self.iscode = d["iscode"]
        self.user = d["user"]

    def _InitOrd(self, type = None, iscode = None, user = None):
        self.type = type
        self.iscode = iscode
        self.user = user

    def _BuildDict(self, d):
        d["type"] = self.type
        d["iscode"] = self.iscode
        d["user"] = self.user

    def __call__(self, *args, **kwargs):
        assert False


class _LocXref(_LocXrefBase):
    def _InitDict(self, d):
        _LocXrefBase._InitDict(self, d)
        self.nnode_ = d["nnode"]
        self.nnode = None

    def _InitOrd(self, ea, type = None, iscode = None, user = None):
        _LocXrefBase._InitOrd(self, type, iscode, user)
        self.nnode = idaex.ParseNetnode(ea)

    def _BuildDict(self, d):
        _LocXrefBase._BuildDict(self, d)
        if self.nnode:
            d["nnode"] = self.nnode
        else:
            d["nnode"] = self.nnode_

class LocXrefTo(_LocXref):
    def __call__(self, *args, **kwargs):
        if not self.nnode:
            self.nnode = uuts.BuildObj(self.nnode_)
        for xref in idaex.XrefsToEx(self.nnode.id):
            if self.type is not None and self.type != xref.type:
                continue
            if self.iscode is not None and self.iscode != xref.iscode:
                continue
            if self.user is not None and self.user != xref.user:
                continue
            yield xref.frm


class LocXrefFrom(_LocXref):
    def __call__(self, *args, **kwargs):
        if not self.nnode:
            self.nnode = uuts.BuildObj(self.nnode_)
        for xref in idaex.XrefsFromEx(self.nnode.id):
            if self.type is not None and self.type != xref.type:
                continue
            if self.iscode is not None and self.iscode != xref.iscode:
                continue
            if self.user is not None and self.user != xref.user:
                continue
            yield xref.to


#translator,ת����
class _TrBase(uuts.Serialize):
    pass

class TrHolder(_TrBase):
    def _InitDict(self, d):
        self.data = d["data"]

    def _InitOrd(self, data):
        self.data = data

    def __call__(self, ea, *args, **kwargs):
        return self.data

    def _BuildDict(self, v):
        v["data"] = self.data


class TrFnEnd(_TrBase):
    _res = idc.BADADDR

    def __call__(self, ea, *args, **kwargs):
        self._res = idc.FindFuncEnd(ea)
        return self._res

    def PrintDbgInfo(self):
        if self._res != idc.BADADDR:
            return
        uuts.LogDebug("TrFnEnd֮û�ҵ�������β")


class TrFnStart(_TrBase):
    notFn = False

    def __call__(self, ea, *args, **kwargs):
        ptr = idaapi.get_func(ea)
        # assert False, "TrFnStart����ַ( %x )���Ǻ����ڵĵ�ַ" % ea
        if not ptr:
            self.notFn = True
            return
        self.notFn = False
        return ptr.startEA

    def PrintDbgInfo(self):
        if self.notFn == False:
            return
        uuts.LogDebug("TrFnStart֮�õ�ַ�����ں���")


class TrEaOffset(_TrBase):
    def _InitDict(self, d):
        self.offset = d["offset"]

    def _InitOrd(self, offset):
        self.offset = offset

    def __call__(self, ea, *args, **kwargs):
        return ea + self.offset

    def _BuildDict(self, v):
        v["offset"] = self.offset


class TrFnOffset(TrEaOffset):
    errorCode = -1

    def __call__(self, ea, *args, **kwargs):
        res = ea + self.offset
        ptr = idaapi.get_func(res)
        if not ptr:
            self.errorCode = 0
            return
        srcPtr = idaapi.get_func(ea)
        if not srcPtr:
            self.errorCode = 1
            return
        if srcPtr.startEA != ptr.startEA:
            self.errorCode = 2
            return
        self.errorCode = -1
        return res

    def PrintDbgInfo(self):
        if self.errorCode == -1:
            return
        elif self.errorCode == 0:
            uuts.LogDebug("TrFnOffset֮�õ�ַ����ƫ�ƾͲ����ں����ˣ�ƫ�ƣ�%d"%self.offset)
        elif self.errorCode == 1:
            uuts.LogDebug("TrFnOffset֮�õ�ַ�����ں���")
        else:
            uuts.LogDebug("TrFnOffset֮�õ�ַ����ƫ�Ƶõ��ĵ�ַ��õ�ַ������ͬһ�������ˣ�ƫ�ƣ�%d" % self.offset)


class TrFnOffsetStart(TrFnOffset):
    errorCode = -1

    def __call__(self, ea, *args, **kwargs):
        res = ea + self.offset
        ptr = idaapi.get_func(res)
        if not ptr:
            self.errorCode = 0
            return
        if ptr.startEA != res:
            self.errorCode = 1
            return
        srcPtr = idaapi.get_func(ea)
        if not srcPtr:
            self.errorCode = 2
            return
        if srcPtr.startEA != res:
            self.errorCode = 3
            return
        self.errorCode = -1
        return res

    def PrintDbgInfo(self):
        if self.errorCode == -1:
            return
        elif self.errorCode == 0:
            uuts.LogDebug("TrFnOffsetStart֮�õ�ַ����ƫ�ƾͲ����ں����ˣ�ƫ�ƣ�%d"%self.offset)
        elif self.errorCode == 1:
            uuts.LogDebug("TrFnOffsetStart֮�õ�ַ����ƫ�Ƶõ���ַ����Ϊa,a����a���ں������׵�ַ��ƫ�ƣ� %x " % self.offset)
        elif self.errorCode == 2:
            uuts.LogDebug("TrFnOffsetStart֮�õ�ַ�����ں���")
        else:
            uuts.LogDebug("TrFnOffsetStart֮�õ�ַ����ƫ�Ƶõ���ַ����Ϊa,a���ں�����õ�ַ���ں�������ͬһ��������ƫ�ƣ� %x " % self.offset)


class _AssertMultiBase(uuts.MultiIterCall):
    pass


class AssertAllOf(_AssertMultiBase):
    def __call__(self, *args, **kwargs):
        for i in self._fns_:
            if i(*args, **kwargs) <= 0:
                return 0
        return len(self._fns_)

class AssertAnyOf(_AssertMultiBase):
    def __call__(self, *args, **kwargs):
        for i in self._fns_:
            res = i(*args, **kwargs)
            if res > 0:
                return res
        return 0

class AssertInRange(uuts.Serialize):
    _res = 1
    def _InitDict(self, d):
        self.eaRange = uuts.BuildObj(d)

    def _InitOrd(self, eaRange):
        self.eaRange = eaRange

    def __call__(self, ea, *args, **kwargs):
        if ea >= self.eaRange.eaBegin and ea < self.eaRange.eaEnd:
            self._res = 1
        else:
            self._res = 0
        return self._res

    def _BuildDict(self, d):
        d["eaRange"] = self.eaRange

    def PrintDbgInfo(self):
        if self._res == 1:
            return
        uuts.LogDebug("AssertInRange֮�õ�ַ������Ч��Χ��")


class AssertAsCnt(uuts.Serialize):
    asCnt = True
    def _InitDict(self, d):
        self.cnt_ = d["cnt"]

    def _InitOrd(self, cnt):
        self.cnt_ = cnt

    def __call__(self, ea, cnt, *args, **kwargs):
        self.asCnt = cnt == self.cnt_
        return self.asCnt

    def _BuildDict(self, d):
        d["cnt"] = self.cnt_

    def PrintDbgInfo(self):
        if self.asCnt:
            return
        uuts.LogDebug("AssertAsCnt֮���ִ������ԣ���Ч������%d" % self.cnt_)


class AssertEqual(uuts.Serialize):
    valid = True
    def _InitDict(self, d):
        self.what = uuts.BuildObj(d["what"])
        self.value = d["value"]

    def _InitOrd(self, what, value):
        self.what = what
        self.value = value

    def __call__(self, ea, *args, **kwargs):
        self.valid = self.what(ea) == self.value
        return self.valid

    def _BuildDict(self, d):
        d["what"] = self.what
        d["value"] = self.value

    def PrintDbgInfo(self):
        if self.valid:
            return
        uuts.LogDebug("AssertEqual֮value����ͬ����Чvalue��", self.value)


class AssertIsFunc(uuts.Serialize):
    valid = True

    def __call__(self, ea, *args, **kwargs):
        self.valid = idaapi.get_func(ea) is not None
        return self.valid

    def PrintDbgInfo(self):
        if self.valid:
            return
        uuts.LogDebug("AssertIsFunc֮�õ�ַ���Ǻ���")


class AssertFuncStart(uuts.Serialize):
    valid = True
    def __call__(self, ea, *args, **kwargs):
        self.valid = idaex.IsFunctionStart(ea)
        return self.valid

    def PrintDbgInfo(self):
        if self.valid:
            return
        uuts.LogDebug("AssertFuncStart֮�õ�ַ���Ǻ������Ǻ����׵�ַ")


class _AssertWithTrBase(uuts.Serialize):
    def _InitDict(self, d):
        self.value = d["value"]
        self.tr = uuts.BuildObj(d["tr"])
        if not self.tr:
            self.tr = TrHolder(idc.BADADDR)

    def _InitOrd(self, value, tr = None):
        self.value = value
        self.tr = tr
        if not self.tr:
            self.tr = TrHolder(idc.BADADDR)

    def _BuildDict(self, d):
        d["value"] = self.value
        if isinstance(self.tr, TrHolder) and self.tr.data == idc.BADADDR:
            d["tr"] = None
        else:
            d["tr"] = self.tr

    def __call__(self, ea, *args, **kwargs):
        assert False, "����ö���һ��call"


class AssertSameInsnOffset(_AssertWithTrBase):
    valid = True

    def _InitOrd(self, offsetDelta, insnDelta, ea2Bound = None):
        _AssertWithTrBase._InitOrd(self, (offsetDelta, insnDelta), ea2Bound)

    def __call__(self, ea, *args, **kwargs):
        self.valid = idaex.IsSameInsnOffset(self.value[0], self.value[1], ea, self.tr(ea))
        return self.valid

    def PrintDbgInfo(self):
        if self.valid:
            return
        uuts.LogDebug("AssertSameInsnOffset֮�õ�ַ�����ں��������ָ�������ƫ�Ʋ���")


class _AssertWithTrBase_Equal(_AssertWithTrBase):
    valid = True

    def __call__(self, ea, *args, **kwargs):
        self.valid = self.fn(ea, self.tr(ea)) == self.value
        return self.valid


class AssertFuncSize(_AssertWithTrBase_Equal):
    fn = lambda self, ea, *args: idaex.EaRangeFn(ea).Size()

    def PrintDbgInfo(self):
        if self.valid:
            return
        uuts.LogDebug("AssertFuncSize֮�õ�ַ���ں�����size����")


class AssertInsnAndSize(_AssertWithTrBase_Equal):
    fn = lambda self, *args : idaex.InsnAndSize(*args)

    def PrintDbgInfo(self):
        if self.valid:
            return
        uuts.LogDebug("AssertInsnAndSize֮��ַ��Χ��size���Ի�ָ���������")


class AssertFuncInsnAndSize(_AssertWithTrBase_Equal):
    fn = lambda self, *args : idaex.FuncInsnAndSize(*args)

    def PrintDbgInfo(self):
        if self.valid:
            return
        uuts.LogDebug("AssertFuncInsnAndSize֮�õ�ַ��������β��size���Ի�ָ���������")


class AssertInsnCheckSum(_AssertWithTrBase_Equal):
    fn = lambda self, *args : idaex.InsnCheckSum(*args)

    def PrintDbgInfo(self):
        if self.valid:
            return
        uuts.LogDebug("AssertInsnCheckSum֮��ַ��Χ��checksum����")


class AssertFuncCheckSum(_AssertWithTrBase_Equal):
    fn = lambda self, *args : idaex.FuncCheckSum(*args)

    def PrintDbgInfo(self):
        if self.valid:
            return
        uuts.LogDebug("AssertFuncCheckSum֮�õ�ַ��������β�ĵ�checksum����")


class AssertInsnFullCheck(_AssertWithTrBase_Equal):
    fn = lambda self, *args : idaex.InsnFullCheck(*args)

    def PrintDbgInfo(self):
        if self.valid:
            return
        uuts.LogDebug("AssertInsnFullCheck֮��ַ��Χ��ָ��������ֽڸ�����checksum����")


class AssertFuncFullCheck(_AssertWithTrBase_Equal):
    fn = lambda self, *args : idaex.FuncFullCheck(*args)

    def PrintDbgInfo(self):
        if self.valid:
            return
        uuts.LogDebug("AssertFuncFullCheck֮�õ�ַ��������β��ָ��������ֽڸ�����checksum����")


class _OpMultiBase(uuts.MultiIterCall):
    def __call__(self, ea, *args, **kwargs):
        assert False, "������Լ�ʵ��"

    def Valid(self):
        if not self._fns_:
            return False
        return len(self._fns_) > 0

    def IsExistName(self, name):
        for i in self._fns_:
            if i.IsExistName(name):
                return True
        return False


class OpAllOf(_OpMultiBase):
    def __call__(self, ea, *args, **kwargs):
        for impl in self._fns_:
            res = impl(ea, *args, **kwargs)
            if res == 0:
                return res
        return len(self._fns_)

class OpSetName(idaex._OpBase):
    _res = True

    def _InitOrd(self, name, globalName = True):
        assert name
        self.name = name
        self.globalName = globalName

    def _InitDict(self, d):
        self.name = d["name"]
        self.globalName = d["globalName"]

    def _BuildDict(self, d):
        d["name"] = self.name
        d["globalName"] = self.globalName

    def __call__(self, ea, *args, **kwargs):
        name = idaapi.netnode(ea).name()
        self._res = True
        if not name or name != self.name:
            self._res = idaex.MakeNameStrict(ea, self.name, self.globalName)
        return self._res

    def IsExistName(self, name):
        return self.name == name

    def PrintDbgInfo(self):
        if self._res:
            return
        uuts.LogDebug("OpSetName֮��������ʧ�ܣ����֣�", self.name)


class OpEaCmt(idaex._OpBase):
    errorCode = -1

    def _InitDict(self, d):
        self.lineA = d["lineA"]
        self.lineB = d["lineB"]
        self.cmt = d["cmt"]
        self.rcmt = d["rcmt"]

    def _InitOrd(self, ea):
        self.lineA = idaex.GetLineCmt(ea, True)
        self.lineB = idaex.GetLineCmt(ea, False)
        self.cmt = idaapi.get_cmt(ea, False)
        self.rcmt = idaapi.get_cmt(ea, True)

    def _BuildDict(self, d):
        d["lineA"] = self.lineA
        d["lineB"] = self.lineB
        d["cmt"] = self.cmt
        d["rcmt"] = self.rcmt

    def __call__(self, ea, *args, **kwargs):
        self.errorCode = 1
        if self.lineB:
            self.errorEa = ea
            idaex.SetLineCmt(ea, self.lineB, False)
            env = EnvObjMgr()
            env.RunByEa(ea, self.lineB)
        self.errorCode = 0
        if self.lineA:
            idaex.SetLineCmt(ea, self.lineA, True)
        if self.cmt:
            idc.MakeComm(ea, self.cmt)
        if self.rcmt:
            idc.MakeRptCmt(ea, self.rcmt)
        self.errorCode = -1
        return True

    @uuts.LogStack
    def PrintDbgInfo(self):
        if self.errorCode == -1:
            return
        elif self.errorCode == 0:
            uuts.LogDebug("OpEaCmt֮����ע��ʧ��")
        else:
            uuts.LogDebug("OpEaCmt֮����LineBʧ�ܣ���ַ�� %x ��������OpEaCmt����LineB����ϸ������Ϣ" % self.errorEa)
            try:
                self(self.errorEa)
            except:
                uuts.LogError(traceback.format_exc())
        uuts.LogDebug("-----������OpEaCmt�ĳ�����Ϣ�����˽���---------------------")

    def Valid(self):
        return self.lineA or self.lineB or self.cmt or self.rcmt


class OpEaOffset(OpAllOf):
    def _InitDict(self, d):
        OpAllOf._InitDict(self, d)
        self.offset = d["offset"]

    def _InitOrd(self, offset, *fns):
        # assert len(fns) > 0
        OpAllOf._InitOrd(self, *fns)
        self.offset = offset

    def _BuildDict(self, d):
        OpAllOf._BuildDict(self, d)
        d["offset"] = self.offset

    def __call__(self, ea, *args, **kwargs):
        return OpAllOf.__call__(self, ea + self.offset, *args, **kwargs)


class OpEaXrefInfo(_LocXrefBase):
    errorCode = -1

    def _InitDict(self, d):
        _LocXrefBase._InitDict(self, d)
        self.nameInfo = OpSetName(d["nameInfo"])

    def _InitOrd(self, name, globalName = True, type = None, iscode = None, user = None):
        _LocXrefBase._InitOrd(self, type, iscode, user)
        self.nameInfo = OpSetName(name, globalName)

    def _BuildDict(self, d):
        _LocXrefBase._BuildDict(self, d)
        d["nameInfo"] = self.nameInfo

    def __call__(self, ea, xref, *args, **kwargs):
        if self.type and self.type != xref.type:
            self.errorCode = 0
            assert False, "OpEaXrefInfo֮��ַ�� %x ��xref type��ͬ�ˡ�" % ea
            return False
        if self.iscode and self.iscode != xref.iscode:
            self.errorCode = 1
            assert False, "OpEaXrefInfo֮��ַ�� %x ��xref iscode��ͬ�ˡ�" % ea
            return False
        if self.user and self.user != xref.user:
            self.errorCode = 2
            assert False, "OpEaXrefInfo֮��ַ�� %x ��xref user��ͬ�ˡ�" % ea
            return False
        self.errorCode = 3
        res = self.nameInfo(ea)
        if res != 0:
            self.errorCode = -1
        return res

    def PrintDbgInfo(self):
        if self.errorCode == -1:
            return
        if self.errorCode == 0:
            uuts.LogDebug("OpEaXrefInfo֮xref type��ͬ��")
        elif self.errorCode == 1:
            uuts.LogDebug("OpEaXrefInfo֮xref iscode��ͬ��")
        elif self.errorCode == 2:
            uuts.LogDebug("OpEaXrefInfo֮xref user��ͬ��")
        else:
            uuts.LogDebug("OpEaXrefInfo֮����nameInfoʧ��")
            self.nameInfo.PrintDbgInfo()

    def Valid(self):
        return self.nameInfo.Valid()

    def IsExistName(self, name):
        return self.nameInfo.IsExistName(name)


class OpEaFromXrefName(idaex._OpBase):
    errorCode = -1
    errorIdx = -1

    def _InitDict(self, d):
        tos = d["tos"]
        if tos:
            self.tos = [uuts.BuildObj(x) for x in tos]
        else:
            self.tos = None

    def _InitOrd(self, ea, top = None):
        self.tos = None
        self.top = top
        fn = idaapi.get_func(ea)
        if fn:
            fnStart = fn.startEA
        else:
            fnStart = idc.BADADDR
        for xref in idaex.XrefsFromEx(ea, 0):
            #���õ�ַû���ֶ�������name��Ϊ��
            name = idaapi.netnode(xref.to).name()
            globalName = True
            if not name:
                if not xref.iscode:
                    continue
                # �ж��Ƿ���������
                name = idaapi.get_true_name(ea, xref.to)    #idc.GetTrueNameEx
                if name and idaapi.is_uname(name):
                    globalName = False
                else:
                    continue
            #���˵��ṹ�����Ա������
            if not xref.iscode:
                if idaapi.get_member_by_id(xref.to) or idaapi.get_struc(xref.to):
                    continue
            #ȥ�ظ�
            if self.FindToEa(name) or self.top and self.top.IsExistName(name):
                continue
            # print name
            if not self.tos:
                self.tos = []
            self.tos.append(OpEaXrefInfo(name, globalName, xref.type, xref.iscode, xref.user))

    def _BuildDict(self, d):
        d["tos"] = self.tos

    def FindToEa(self, name, idxLimit = -1):
        if not self.tos:
            return
        if idxLimit < 0:
            idxLimit = len(self.tos)
        idx = 0
        for i in self.tos:
            if idx >= idxLimit:
                return
            if i.nameInfo.name == name:
                return i
            idx += 1

    def IsExistName(self, name):
        return self.FindToEa(name) is not None

    def Valid(self):
        if not self.tos:
            return False
        return len(self.tos) > 0

    def __call__(self, ea, *args, **kwargs):
        if not self.tos:
            return True
        size = len(self.tos)
        idx = 0
        for xref in idaex.XrefsFromEx(ea, 0):
            if idaapi.get_member_by_id(xref.to) or idaapi.get_struc(xref.to):
                continue
            name = idaapi.netnode(xref.to).name()
            #ֻ���Լ��ĳ�Ա����������
            if name and self.FindToEa(name, idx):
                continue
            if idx >= size:
                self.errorCode = 0
                assert False, "OpEaFromXrefName֮��������idx:%d, size:%d, ea: %x " % (idx, size, ea)
                return False
            self.errorCode = 1
            self.errorIdx = idx
            if self.tos[idx](xref.to, xref, *args, **kwargs) == 0:
                return False
            idx += 1
        if idx != size:
            self.errorCode = 2
            assert False, "OpEaFromXrefName֮xref��Ϣ������ƥ�䣬idx:%d, size:%d, ea: %x " % (idx, size, ea)
            return False
        self.errorCode = -1
        return True

    def PrintDbgInfo(self):
        if self.errorCode == -1:
            return
        elif self.errorCode == 0:
            uuts.LogDebug("OpEaFromXrefName֮�������󣬿��������ڵ�xref��������ԭ�ȵ�xref�����ˣ�ԭ��xref������", len(self.tos))
        elif self.errorCode == 1:
            uuts.LogDebug("OpEaFromXrefName֮tosִ�д���")
            self.tos[self.errorIdx].PrintDbgInfo()
        else:
            uuts.LogDebug("OpEaFromXrefName֮xref������ƥ�䣬ԭ��xref������", len(self.tos))


class OpDataFlags(idaex._OpBase):
    errorCode = -1

    def _InitDict(self, d):
        self.flag0 = uuts.BuildObj(d["flag0"])
        self.size = d["size"]
        self.duf = d["duf"]

    #DOUNK_SIMPLE��ʱ��ʧ�ܣ�DOUNK_DELNAMES�ܹ��������ʧ�ܵ������������ڴ�����������ʱ��DOUNK_SIMPLE��ʧ�ܡ�
    def _InitOrd(self, ea, doUknFlag = idc.DOUNK_SIMPLE):
        self.flag0 = idaex.FlagsOp0(ea, idc.GetFlags(ea))
        self.size = idc.ItemSize(ea)
        # self.size = idaex.ItemSizeEx(ea)
        self.duf = doUknFlag

    def _BuildDict(self, d):
        d["flag0"] = self.flag0
        d["size"] = self.size
        d["duf"] = self.duf

    def __call__(self, ea, *args, **kwargs):
        flag = self.flag0.flag & ~idc.MS_VAL
        #���ǰ������ע�͵��ɣ���Ϊ�п����ǽṹ��������flag����ͬ�ģ���opinfoȴ�ǲ�ͬ�ġ�
        # if idc.GetFlags(ea) & ~idc.MS_VAL == flag and self.size == idc.ItemSize(ea):    #�жϴ�С�Ƿ�ֹ���������flag����ͬ�����
        #     return True
        size = self.size
        if idaapi.isStruct(flag):
            nid = self.flag0.GetOpinfo().tid
            setOpinfo = False
        elif idc.isASCII(flag):
            size = idaapi.get_max_ascii_length(ea, self.flag0.GetOpinfo().strtype)
            assert size >= 0
            nid = idaapi.BADNODE
            setOpinfo = False
        else:
            nid = idaapi.BADNODE
            setOpinfo = True
        if idaapi.do_data_ex(ea, flag, size, nid) == 0:
            # ��ȡ�������ٽ������ã������ַ��Χ���в����ϸ����ݸ�ʽ�ģ�do_data_ex�ͻ����
            idaapi.do_unknown_range(ea, size, self.duf)
            self.errorCode = 0
            if idaapi.do_data_ex(ea, flag, size, nid) == 0:
                assert False, "OpDataFlags֮do_data_exʧ�ܣ�ea: %x , flag: %x " % (ea, self.flag0.flag)
                return False
        self.errorCode = 1
        if setOpinfo and not self.flag0.SetOpinfo(ea):
            assert False, "_FlagsOpBase֮SetOpInfoʧ�ܣ���ַ�� %x " % ea
            return False
        self.errorCode = 2
        if idc.GetFlags(ea) & ~idc.MS_VAL != flag:
            assert False, "OpDataFlags֮����flagʧ�ܣ�ea: %x , flag: %x " % (ea, self.flag0.flag)
            return False
        self.errorCode = -1
        return True

    def PrintDbgInfo(self):
        if self.errorCode == -1:
            return
        if self.errorCode == 0:
            uuts.LogDebug("OpDataFlags֮do_data_exʧ��")
        elif self.errorCode == 1:
            uuts.LogDebug("OpDataFlags֮SetOpInfoʧ��")
            self.flag0.PrintDbgInfo()
        else:
            uuts.LogDebug("OpDataFlags֮��Ȼ�ɹ�������flag�����������֤flagȴʧ����")


class OpData(OpSetName):
    errorCode = -1

    def _InitDict(self, d):
        OpSetName._InitDict(self, d)
        self.flag = uuts.BuildObj(d["flag"])
        self.type = uuts.BuildObj(d["type"])
        self.cmt = uuts.BuildObj(d["cmt"])

    # DOUNK_SIMPLE��ʱ��ʧ�ܣ�DOUNK_DELNAMES�ܹ��������ʧ�ܵ������������ڴ�����������ʱ��DOUNK_SIMPLE��ʧ�ܡ�
    def _InitOrd(self, ea, doUknFlag = idc.DOUNK_SIMPLE):
        name = idaapi.netnode(ea).name()
        assert name, "OpData���ֲ���Ϊ��, ea: %x " % ea
        OpSetName._InitOrd(self, name, True)
        self.flag = OpDataFlags(ea, doUknFlag)
        tmp = OpEaType(ea)
        if tmp.Valid():
            self.type = tmp
        else:
            self.type = None
        tmp = OpEaCmt(ea)
        if tmp.Valid():
            self.cmt = tmp
        else:
            self.cmt = None

    def _BuildDict(self, d):
        OpSetName._BuildDict(self, d)
        d["flag"] = self.flag
        d["type"] = self.type
        d["cmt"] = self.cmt

    def __call__(self, ea, *args, **kwargs):
        self.errorCode = 0
        if OpSetName.__call__(self, ea, *args, **kwargs) == False:
            return False
        self.errorCode = 1
        if self.type and self.type(ea, *args, **kwargs) == False:
            return False
        self.errorCode = 2
        # cmt��÷ŵ����棬��Ϊ�п��ܻ�����cmt
        if self.cmt and self.cmt(ea, *args, **kwargs) == False:
            return False
        self.errorCode = 3
        #flag�����������ã���Ϊע�͵Ȼ�ı�flag�ġ�
        if self.flag(ea, *args, **kwargs) == False:
            return False
        self.errorCode = -1
        return True

    def PrintDbgInfo(self):
        if self.errorCode == -1:
            return
        elif self.errorCode == 0:
            uuts.LogDebug("OpData֮��������ʧ��")
            OpSetName.PrintDbgInfo(self)
        elif self.errorCode == 1:
            uuts.LogDebug("OpData֮����typeʧ��")
            self.type.PrintDbgInfo()
        elif self.errorCode == 2:
            uuts.LogDebug("OpData֮ע�ͷ����������")
            self.cmt.PrintDbgInfo()
        else:
            uuts.LogDebug("OpData֮����flagʧ��")
            self.flag.PrintDbgInfo()


class OpCodeFlags(idaex._OpBase):
    errorCode = -1

    def _InitDict(self, d):
        self.flag0 = uuts.BuildObj(d["flag0"])
        self.flag1 = uuts.BuildObj(d["flag1"])
        self.type0 = d["type0"]
        self.type1 = d["type1"]

    def _InitOrd(self, ea):
        self.type0 = idc.GetOpType(ea, 0)
        if self.type0 == idc.o_void:
            self.flag0 = None
        else:
            self.flag0 = idaex.FlagsOp0(ea, idc.GetFlags(ea))
        self.type1 = idc.GetOpType(ea, 1)
        if self.type1 == idc.o_void:
            self.flag1 = None
        else:
            self.flag1 = idaex.FlagsOp1(ea, idc.GetFlags(ea))

    def _BuildDict(self, d):
        d["flag0"] = self.flag0
        d["flag1"] = self.flag1
        d["type0"] = self.type0
        d["type1"] = self.type1

    def Valid(self):
        return self.flag1 is not None or self.flag0 is not None

    #��ʱ���������o_mem��ƫ�ƣ������е�ʱ����o_imm�����Ե���ע�͵�ʱ���������Ӹ�ʽ��Ϣ����Ҳ��Ϊ�˼��ٸ�����Ϣ
    def HasImme(self):
        return self.type0 == idc.o_imm or self.type1 == idc.o_imm

    #�Ƿ���Ҫ������Ϣ
    def NeedInfo(self):
        if self.type0 != idc.o_void:
            if self.type0 == idc.o_mem or self.type0 == idc.o_phrase or self.type0 == idc.o_displ or self.type0 == idc.o_imm:
                return True
        if self.type1 != idc.o_void:
            if self.type1 == idc.o_mem or self.type1 == idc.o_phrase or self.type1 == idc.o_displ or self.type1 == idc.o_imm:
                return True
        return False

    def __call__(self, ea, *args, **kwargs):
        self.errorCode = 0
        if self.flag0 and not self.flag0.SetFlag(ea, False):
            return False
        self.errorCode = 1
        if self.flag1 and not self.flag1.SetFlag(ea, False):
            return False
        if self.flag0:
            flag = self.flag0.flag
        elif self.flag1:
            flag = self.flag1.flag
        self.errorCode = 2
        if idc.GetFlags(ea) != flag:
            assert False, "OpCodeFlags֮����flagʧ�ܣ�ea: %x , flag: %x " %(ea, flag)
            return False
        self.errorCode = -1
        return True

    def PrintDbgInfo(self):
        if self.errorCode == -1:
            return
        elif self.errorCode == 0:
            uuts.LogDebug("OpCodeFlags֮����flag0ʧ��")
            self.flag0.PrintDbgInfo()
        elif self.errorCode == 1:
            uuts.LogDebug("OpCodeFlags֮����flag1ʧ��")
            self.flag1.PrintDbgInfo()
        else:
            uuts.LogDebug("OpCodeFlags֮��Ȼ�ɹ�������flag���������У��ȴʧ����")


class OpFnInfo(idaex._OpBase):
    errorCode = -1

    def _InitDict(self, d):
        self.size = d["size"]
        self.frsize = d["frsize"]
        self.frregs = d["frregs"]
        self.argsize = d["argsize"]
        self.fpd = d["fpd"]
        self.color = d["color"]
        self.flag = d["flag"]

    def _InitOrd(self, ea):
        end = idc.GetFunctionAttr(ea, idc.FUNCATTR_END)
        assert end != idc.BADADDR
        self.size = end - ea
        self.frsize = idc.GetFunctionAttr(ea, idc.FUNCATTR_FRSIZE)
        self.frregs = idc.GetFunctionAttr(ea, idc.FUNCATTR_FRREGS)
        self.argsize = idc.GetFunctionAttr(ea, idc.FUNCATTR_ARGSIZE)
        self.fpd = idc.GetFunctionAttr(ea, idc.FUNCATTR_FPD)
        self.color = idc.GetFunctionAttr(ea, idc.FUNCATTR_COLOR)
        self.flag = idc.GetFunctionFlags(ea)
        #FUNCATTR_OWNER  FUNCATTR_REFQTY�������в�֪����


    def _BuildDict(self, d):
        d["size"] = self.size
        d["frsize"] = self.frsize
        d["frregs"] = self.frregs
        d["argsize"] = self.argsize
        d["fpd"] = self.fpd
        d["color"] = self.color
        d["flag"] = self.flag

    def __call__(self, ea, *args, **kwargs):
        dst = OpFnInfo(ea)
        self.errorCode = 0
        if self.size != dst.size:
            if 0 == idc.SetFunctionAttr(ea, idc.FUNCATTR_END, ea + self.size):
                assert False, "���ú���������ַʧ�ܣ�������ַ�� %x ��������С��%d" % (ea, self.size)
                return False
        self.errorCode = 1
        if self.frsize != dst.frsize:
            if 0 == idc.SetFunctionAttr(ea, idc.FUNCATTR_FRSIZE, self.frsize):
                assert False, "���ú���frsizeʧ�ܣ�������ַ�� %x ��frsize��%d" % (ea, self.frsize)
                return False
        self.errorCode = 2
        if self.frregs != dst.frregs:
            if 0 == idc.SetFunctionAttr(ea, idc.FUNCATTR_FRREGS, self.frregs):
                assert False, "���ú���frregsʧ�ܣ�������ַ�� %x ��frregs��%d" % (ea, self.frregs)
                return False
        self.errorCode = 3
        if self.argsize != dst.argsize:
            if 0 == idc.SetFunctionAttr(ea, idc.FUNCATTR_ARGSIZE, self.argsize):
                assert False, "���ú���argsizeʧ�ܣ�������ַ�� %x ��argsize��%d" % (ea, self.argsize)
                return False
        self.errorCode = 4
        if self.fpd != dst.fpd:
            if 0 == idc.SetFunctionAttr(ea, idc.FUNCATTR_FPD, self.fpd):
                assert False, "���ú���fpdʧ�ܣ�������ַ�� %x ��fpd��%d" % (ea, self.fpd)
                return False
        self.errorCode = 5
        if self.color != dst.color:
            if 0 == idc.SetFunctionAttr(ea, idc.FUNCATTR_COLOR, self.color):
                assert False, "���ú���colorʧ�ܣ�������ַ�� %x ��color��%d" % (ea, self.color)
                return False
        self.errorCode = 6
        if self.flag != dst.flag:
            if 0 == idc.SetFunctionFlags(ea, self.flag):
                assert False, "���ú���flagʧ�ܣ�������ַ�� %x ��flag��%d" % (ea, self.flag)
                return False
        self.errorCode = -1
        return True

    def PrintDbgInfo(self):
        if self.errorCode == -1:
            return
        elif self.errorCode == 0:
            uuts.LogDebug("OpFnInfo֮������β����ʧ��")
        elif self.errorCode == 1:
            uuts.LogDebug("OpFnInfo֮frsize����ʧ��")
        elif self.errorCode == 2:
            uuts.LogDebug("OpFnInfo֮frregs����ʧ��")
        elif self.errorCode == 3:
            uuts.LogDebug("OpFnInfo֮argsize����ʧ��")
        elif self.errorCode == 4:
            uuts.LogDebug("OpFnInfo֮fpd����ʧ��")
        elif self.errorCode == 5:
            uuts.LogDebug("OpFnInfo֮color����ʧ��")
        elif self.errorCode == 1:
            uuts.LogDebug("OpFnInfo֮flag����ʧ��")


class OpFrame(idaex._OpBase):
    errorCode = -1

    def _InitDict(self, d):
        self.s = uuts.BuildObj(d["s"])

    def _InitOrd(self, ea):
        fnPtr = idaapi.get_func(ea)
        assert fnPtr
        sPtr = idaapi.get_frame(fnPtr)
        if sPtr:
            self.s = idaex.StrucOp(sPtr.id)
        else:
            self.s = None

    def _BuildDict(self, d):
        d["s"] = self.s

    def __call__(self, ea, *args, **kwargs):
        fnPtr = idaapi.get_func(ea)
        assert fnPtr
        sPtr = idaapi.get_frame(fnPtr)
        if sPtr:
            if self.s:
                self.errorCode = 0
                dst = idaex.StrucOp(sPtr.id)
                if dst.size != self.s.size:
                    assert False, "��ַ�� %x �Ķ�ջ��С�ѱ�,ԭ��С�� %x ���ִ�С�� %x "%(ea, self.s.size, dst.size)
                    return False
                self.errorCode = 1
                res = dst.Update(self.s)
                if res != 0:
                    self.errorCode = -1
                return res
            else:
                self.errorCode = 2
                assert False, "��ַ�� %x ��ԭ��û��ջ�������ж�ջ��" % ea
                return False
        else:
            if self.s:
                self.errorCode = 3
                assert False, "��ַ�� %x ��ԭ���ж�ջ������û��ջ��" % ea
                return False
            else:
                self.errorCode = -1
                return True

    def PrintDbgInfo(self):
        if self.errorCode == -1:
            return
        elif self.errorCode == 0:
            uuts.LogDebug("OpFrame֮StrucOpʧ��")
        elif self.errorCode == 1:
            uuts.LogDebug("OpFrame֮StrucOp�ĸ��²���ʧ��")
        elif self.errorCode == 2:
            uuts.LogDebug("OpFrame֮ԭ��û��ջ�������ж�ջ��")
        else:
            uuts.LogDebug("OpFrame֮ԭ���ж�ջ������û��ջ��")


class OpEaType(idaex.OpType):
    pass


class OpFn(OpSetName):
    errorCode = -1
    errorSub = None

    def _InitDict(self, d):
        OpSetName._InitDict(self, d)
        self.cmt = d["cmt"]
        self.rcmt = d["rcmt"]
        self.info = uuts.BuildObj(d["info"])
        self.frame = uuts.BuildObj(d["frame"])
        self.subs = [uuts.BuildObj(x) for x in d["subs"]]
        self.type = uuts.BuildObj(d["type"])

    def _InitOrd(self, eaFunc):
        OpSetName._InitOrd(self, idaapi.netnode(eaFunc).name(), True)
        self.cmt = idaex.GetFuncCmt(eaFunc, False)
        self.rcmt = idaex.GetFuncCmt(eaFunc, True)
        self.info = OpFnInfo(eaFunc)
        self.frame = OpFrame(eaFunc)
        self._InitSubs(eaFunc)
        self.type = OpEaType(eaFunc)

    def _InitSubs(self, eaFunc):
        self.subs = []
        for ea in idautils.FuncItems(eaFunc):
            eao = OpEaOffset(ea - eaFunc)
            cmt = OpEaCmt(ea)
            if cmt.Valid():
                #cmt�������ں��棬��Ϊ�п��ܻ�����cmt
                eao.Add(cmt)
                #flag�����cmt���棬��Ϊע�ͻ�Ӱ��flag�ġ�
                flags = OpCodeFlags(ea)
                if flags.NeedInfo():
                    eao.Add(flags)  # ����ע�ͣ�����Ӳ�������Ϣ
                    # print "OpCodeFlags,ea: %x " % ea
            #Ҫ����OpCodeFlags������Ӳ���
            xrefFrom = OpEaFromXrefName(ea, self)
            if xrefFrom.Valid():
                eao.Add(xrefFrom)

            if eao.Valid():
                self.subs.append(eao)

    def _BuildDict(self, d):
        OpSetName._BuildDict(self, d)
        d["cmt"] = self.cmt
        d["rcmt"] = self.rcmt
        d["info"] = self.info
        d["frame"] = self.frame
        d["subs"] = self.subs
        d["type"] = self.type

    def IsExistName(self, name):
        if OpSetName.IsExistName(self, name) == True:
            return True
        for sub in self.subs:
            if sub.IsExistName(name):
                return True
        return False

    def __call__(self, ea, *args, **kwargs):
        self.errorCode = 0
        res = OpSetName.__call__(self, ea, *args, **kwargs)
        if res == 0:
            return 0
        if self.cmt:
            self.errorCode = 1
            idc.SetFunctionCmt(ea, self.cmt, 0)
        if self.rcmt:
            self.errorCode = 2
            idc.SetFunctionCmt(ea, self.rcmt, 1)
        self.errorCode = 3
        if self.info(ea) == False:
            return 0
        self.errorCode = 4
        if self.type(ea, *args, **kwargs) == 0:
            return 0
        self.errorCode = 5
        if self.frame(ea) == False:
            return 0
        self.errorCode = 6
        #subs�������������Ϊsubs�п��ܰ���cmt�������п��ܻ�����cmt
        for sub in self.subs:
            self.errorSub = sub
            if sub(ea) == 0:
                return 0
        self.errorCode = -1
        return 1

    def PrintDbgInfo(self):
        if self.errorCode == -1:
            return
        uuts.LogDebug("OpFn֮�����е�ĳ�����ʧ�ܣ���������", self.name)
        if self.errorCode == 0:
            uuts.LogDebug("OpFn֮����������ʧ��")
            OpSetName.PrintDbgInfo(self)
        elif self.errorCode == 1:
            uuts.LogDebug("OpFn֮����ע������ʧ��")
            self.cmt.PrintDbgInfo()
        elif self.errorCode == 2:
            uuts.LogDebug("OpFn֮�����Ŀ��ظ�ע������ʧ��")
            self.rcmt.PrintDbgInfo()
        elif self.errorCode == 3:
            uuts.LogDebug("OpFn֮��������Ϣ����ʧ��")
            self.info.PrintDbgInfo()
        elif self.errorCode == 4:
            uuts.LogDebug("OpFn֮��������������ʧ��")
            self.type.PrintDbgInfo()
        elif self.errorCode == 5:
            uuts.LogDebug("OpFn֮�����Ķ�ջ����ʧ��")
            self.frame.PrintDbgInfo()
        else:
            if self.errorSub:
                uuts.LogDebug("OpFn֮������������Ϣ����ʧ��")
                self.errorSub.PrintDbgInfo()


class _DoUpdateBase(uuts.Serialize):
    """
    ���и��µĲ���
    DU : Do Update
    """
    def _InitDict(self, d):
        self.upl = d["upl"]

    def _InitOrd(self, upl):
        self.upl = upl

    def _BuildDict(self, d):
        d["upl"] = self.upl

    def SetUpl(self, upl):
        self.upl = upl

    def __cmp__(self, other):
        return cmp(self.upl, other.upl)

    def __call__(self):
        assert False


_errorFile_ = None
_continueErrorFile_ = None
def SetErrorObjFile(errorFileName, continueErrorFileName = None):
    """
    ��continueErrorFileNameΪ�գ�������д�����Ϣ�������_errorFile_
    """
    global _errorFile_, _continueErrorFile_
    _errorFile_ = errorFileName
    _continueErrorFile_ = continueErrorFileName

class DU_Multi(uuts.MultiIterCall):
    def Add(self, item):
        if item is None:
            return
        if isinstance(item, DU_Multi):
            for i in item._fns_:
                self.Add(i)
        else:
            assert isinstance(item, _DoUpdateBase)
            self._fns_.append(item)

    def __call__(self):
        for item in self._fns_:
            if item() == idaex.DUR_Error:
                return idaex.DUR_Error
        return idaex.DUR_Succeed


class DU_Queue(DU_Multi):
    queue = None

    #greenlet.greenlet.run��ִ���Ժ󣬺���ͱ�ȡ�������������
    class GletWapper(greenlet.greenlet):
        def __init__(self, run=None, parent=None):
            greenlet.greenlet.__init__(self, run, parent)
            self._MyRun_ = run

        def __cmp__(self, other):
            return cmp(self._MyRun_, other._MyRun_)

    def __call__(self):
        if not self.queue:
            self.queue = Queue.PriorityQueue()
        #clear
        while not self.queue.empty():
            self.queue.get_nowait()
        #add
        for item in self._fns_:
            self.queue.put_nowait(self.GletWapper(item))

        errors = DU_Queue()
        succeedCnt = 0
        eqCnt = 0
        while not self.queue.empty():
            queCnt = self.queue._qsize()
            glet = self.queue.get_nowait()
            gletItem = glet._MyRun_
            try:
                res = glet.switch()
                if res == idaex.DUR_Error:
                    uuts.LogError("DU_Queue  ������һ��")
                    errors.Add(gletItem)
                elif res == idaex.DUR_Succeed:
                    succeedCnt += 1
                    uuts.LogTrace("DU_Queue  �ɹ���һ��")
                elif res == idaex.DUR_Continue:
                    uuts.LogStackClr()
                    gletItem.SetUpl(UPL_Last)
                    self.queue.put_nowait(glet)
                    uuts.LogInfo("DU_Queue  ������һ��")
                else:
                    assert False
            except:
                uuts.LogError("DU_Queue�����쳣\n", traceback.format_exc())
                errors.Add(gletItem)
            if queCnt == self.queue._qsize():
                eqCnt += 1
            else:
                eqCnt = 0
            if eqCnt > queCnt:
                uuts.LogError("������������û�б仯,queue size:%d, equal cnt:%d" % (queCnt, eqCnt))
                break

        continus = None
        if not self.queue.empty():
            continus = DU_Queue()
            while not self.queue.empty():
                continus.Add(self.queue.get_nowait()._MyRun_)

        errorCnt = errors.ItemSize()
        conCnt = continus.ItemSize() if continus else 0
        if errorCnt == 0 and conCnt == 0:
            uuts.LogInfo("�������ݸ��³ɹ���Ҫ���µ��ܸ�����%d���ܳɹ�������%d" % (self.ItemSize(), succeedCnt))
            return idaex.DUR_Succeed

        uuts.LogInfo("������ϣ����г���ģ�Ҫ���µ��ܸ�����%d���ܳɹ�������%d" % (self.ItemSize(), succeedCnt))

        isAdded = False
        if errorCnt > 0:
            uuts.LogDebug("----------------�����Ǹ��µĳ�����ϸ��Ϣ----------------------")
            errors.PrintDbgInfo()
            if _errorFile_:
                uuts.LogInfo("���������Ϣ������ļ��У�", _errorFile_)
                if not _continueErrorFile_:
                    isAdded = True
                    errors.Add(continus)
                errors.WriteToFile(_errorFile_)
            uuts.LogDebug("----------------���µĳ�����ϸ��Ϣ����----------------------")
        if conCnt > 0:
            uuts.LogDebug("----------------������ѭ�����ó������ϸ��Ϣ----------------------")
            continus.PrintDbgInfo()
            if isAdded == False:
                if _continueErrorFile_:
                    errorFile = _continueErrorFile_
                else:
                    errorFile = _errorFile_
                if errorFile:
                    uuts.LogInfo("���ѭ�����ô�����Ϣ������ļ��У�", errorFile)
                    continus.WriteToFile(errorFile)
            uuts.LogDebug("----------------ѭ�����ó������ϸ��Ϣ����----------------------")
        return idaex.DUR_Error


#ö�ٳ���
class DU_SetEnums(_DoUpdateBase):
    errorE = None

    def _InitOrd(self, upl = UPL_Enum):
        _DoUpdateBase._InitOrd(self, upl)
        self.enums = [idaex.EnumOp(x) for x in idaex.EnumMgr().Enums()]

    def _InitDict(self, d):
        _DoUpdateBase._InitDict(self, d)
        self.enums = [uuts.BuildObj(x) for x in d["enums"]]

    def _BuildDict(self, d):
        _DoUpdateBase._BuildDict(self, d)
        d["enums"] = self.enums

    @uuts.LogStack
    def __call__(self):
        uuts.LogTrace("��ʼ����ö��")
        for e in self.enums:
            self.errorE = e
            if not e.AddEnum():
                assert False, "DU_SetEnums���%sö��ʧ��" % e.name
                return idaex.DUR_Error
        self.errorE = None
        uuts.LogTrace("ö�����͸��³ɹ�")
        return idaex.DUR_Succeed

    @uuts.LogStack
    def PrintDbgInfo(self):
        if not self.errorE:
            return
        uuts.LogDebug("ö����ʧ�ܵģ��뿴�������ϸ��Ϣ")
        # uuts.LogDebug("#--------------ö��DbgInfo begin--------------------------")
        # self.errorE.PrintDbgInfo()
        # uuts.LogDebug("#--------------ö��DbgInfo end--------------------------")


#�ṹ��
class DU_SetStructs(_DoUpdateBase):
    errorCode = -1
    errorS = None

    def _InitOrd(self, upl = UPL_Struct):
        _DoUpdateBase._InitOrd(self, upl)
        self.structs = [idaex.StrucOp(x[1]) for x in idautils.Structs()]

    def _InitDict(self, d):
        _DoUpdateBase._InitDict(self, d)
        self.structs = [idaex.StrucOp(x) for x in d["structs"]]

    def _BuildDict(self, d):
        _DoUpdateBase._BuildDict(self, d)
        d["structs"] = self.structs

    @uuts.LogStack
    def __call__(self):
        uuts.LogTrace("��ʼ���½ṹ��")
        self.errorCode = 0
        for s in self.structs:
            self.errorS = s
            if not s.AddStruct(False):
                assert False, "DU_SetStructs���%s�ṹ��ʧ��" % s.name
                return idaex.DUR_Error

        self.errorCode = 1
        for s in self.structs:
            self.errorS = s
            if not s.AddMembers():
                assert False, "DU_SetStructs���%s�ṹ���Աʧ��" % s.name
                return idaex.DUR_Error
        self.errorCode = -1
        uuts.LogTrace("�ṹ����³ɹ�")
        return idaex.DUR_Succeed

    @uuts.LogStack
    def PrintDbgInfo(self):
        if self.errorCode == -1:
            return
        uuts.LogDebug("�ṹ����ʧ�ܵģ��뿴�������ϸ��Ϣ")
        # uuts.LogDebug("#--------------�ṹ��DbgInfo begin--------------------------")
        # if self.errorCode == 0:
        #     uuts.LogDebug("��ӽṹ��ʧ��")
        # else:
        #     uuts.LogDebug("��ӽṹ���Աʧ��")
        # self.errorE.PrintDbgInfo()
        # uuts.LogDebug("#--------------�ṹ��DbgInfo end--------------------------")


#����ָ���ַ����δ�㶨
class DU_SetChunk(_DoUpdateBase):
    def _InitOrd(self, upl = UPL_Chunk):
        _DoUpdateBase._InitOrd(self, upl)

    def _InitDict(self, d):
        _DoUpdateBase._InitDict(self, d)

    def _BuildDict(self, d):
        _DoUpdateBase._BuildDict(self, d)


#���ú���
class DU_SetFunc(_DoUpdateBase):
    errorCode = -1

    def _InitOrd(self, finder, toDo, upl = UPL_Func):
        _DoUpdateBase._InitOrd(self, upl)
        assert isinstance(finder, Finder)
        assert isinstance(toDo, (_OpMultiBase, idaex._OpBase))
        self.finder = finder
        self.toDo = toDo

    def _InitDict(self, d):
        _DoUpdateBase._InitDict(self, d)
        self.finder = uuts.BuildObj(d["finder"])
        self.toDo = uuts.BuildObj(d["toDo"])

    def _BuildDict(self, d):
        _DoUpdateBase._BuildDict(self, d)
        d["finder"] = self.finder
        d["toDo"] = self.toDo

    def _DoCall(self):
        self.errorCode = 0
        addr = self.finder.Do()
        if addr == idc.BADADDR:
            return idaex.DUR_Error
        self.errorCode = 1
        if self.toDo(addr) == 0:
            return idaex.DUR_Error
        self.errorCode = -1
        return idaex.DUR_Succeed

    @uuts.LogStack
    def __call__(self):
        if hasattr(self.toDo, "name"):
            name = self.toDo.name
        else:
            name = None
        if name is not None:
            uuts.LogTrace("��ʼ�������������", name)
        else:
            uuts.LogTrace("��ʼ����һ������")
        res = self._DoCall()
        if idaex.DUR_Succeed == res:
            if name is not None:
                uuts.LogTrace("����������³ɹ���", name)
            else:
                uuts.LogTrace("�Ǹ��������³ɹ�")
        else:
            if name is not None:
                uuts.LogTrace("�����������ʧ�ܣ�", name)
            else:
                uuts.LogTrace("�Ǹ���������ʧ��")
        return res

    @uuts.LogStack
    def PrintDbgInfo(self):
        if self.errorCode == -1:
            return
        elif self.errorCode == 0:
            uuts.LogDebug("DU_SetFunc֮finderʧ��")
            self.finder.PrintDbgInfo()
        else:
            uuts.LogDebug("DU_SetFunc֮toDoʧ��")
            self.toDo.PrintDbgInfo()
            uuts.LogDebug("DU_SetFunc֮��ȻtoDoʧ���ˣ����п�����finder��ɵģ�����鿴һ��finderʧ�ܵ���Ϣ")
            self.finder.PrintDbgInfo()


class DU_SetGloData(DU_SetFunc):
    """
    ȫ�ֱ����������ַ����������麯����
    """
    def _InitOrd(self, finder, toDo, upl=UPL_GloData):
        DU_SetFunc._InitOrd(self, finder, toDo, upl)

    @uuts.LogStack
    def __call__(self):
        if hasattr(self.toDo, "name"):
            name = self.toDo.name
        else:
            name = None
        if name is not None:
            uuts.LogTrace("��ʼ�������ȫ�ֱ�����", name)
        else:
            uuts.LogTrace("��ʼ����һ��ȫ�ֱ���")
        res = self._DoCall()
        if idaex.DUR_Succeed == res:
            if name is not None:
                uuts.LogTrace("���ȫ�ֱ������³ɹ���", name)
            else:
                uuts.LogTrace("�Ǹ�ȫ�ֱ������³ɹ�")
        else:
            if name is not None:
                uuts.LogTrace("���ȫ�ֱ�������ʧ�ܣ�", name)
            else:
                uuts.LogTrace("�Ǹ���������ʧ��")
        return res

    @uuts.LogStack
    def PrintDbgInfo(self):
        if self.errorCode == -1:
            return
        elif self.errorCode == 0:
            uuts.LogDebug("DU_SetGloData֮finderʧ��")
            self.finder.PrintDbgInfo()
        else:
            uuts.LogDebug("DU_SetGloData֮toDoʧ��")
            self.toDo.PrintDbgInfo()
            uuts.LogDebug("DU_SetGloData֮��ȻtoDoʧ���ˣ����п�����finder��ɵģ�����鿴һ��finderʧ�ܵ���Ϣ")
            self.finder.PrintDbgInfo()


#����ͷ�ļ��еĽṹ������˳���������ṹ���˳��
# def SetStrucOrderBy
# def SetEnumOrderBy
# def UpdateStructs(self):    #���Խṹ��ı仯
# def UpdateEnums(self):      #���Գ����ı仯
# def XrefEnums(self):
# def XrefStructs(self):
# def XrefOthers(self):
# def Check         #У���������֡�xref����Ϣ


#�����������
@uuts.singleton
class EnvObjMgr:
    #name list�����Դ�Ϊǰ׺�Ķ������
    sysPrefixes = ("@",)
    #name list��ָ�����֣�Ҳ�����������е�һ���֣��Ļ���и���
    subNames = []

    def __init__(self, clsEnvGen = None, clsEnvRun = None):
        class Wrapper:
            def __init__(self, env):
                self.self = env

        if not clsEnvGen:
            clsEnvGen = EaEnvGen
        if not clsEnvRun:
            clsEnvRun = EaEnvRun
        self.genEnv = clsEnvGen()
        self.genExec = uuts.ExecEnv(Wrapper(self.genEnv), None, uuts.DefGlobal())
        self.runEnv = clsEnvRun()
        self.runExec = uuts.ExecEnv(Wrapper(self.runEnv), None, uuts.DefGlobal())

    def GenByEa(self, ea):
        return DU_Queue(self._GenByEa(ea))

    def GenBySubName(self, subName):
        for ea, name in idautils.Names():
            if name.find(subName) >= 0:
                return self.GenByEa(ea)

    def GenAll(self, addStructEnum = True):
        que = DU_Queue()
        for ea, name in idautils.Names():
            if name.startswith(self.sysPrefixes):
                que.Add(self._GenByEa(ea))
            else:
                for i in self.subNames:
                    if name.find(i) >= 0:
                        que.Add(self._GenByEa(ea))
        if addStructEnum:
            que.Add(DU_SetEnums())
            que.Add(DU_SetStructs())
        uuts.LogTrace("����%d��Do Update����" % que.ItemSize())
        return que

    def GenAllStructEnum(self):
        que = DU_Queue()
        que.Add(DU_SetEnums())
        que.Add(DU_SetStructs())
        return que

    def RunByEa(self, ea, cmt = None):
        if cmt is None:
            cmt = idaex.GetLineCmt(ea, False)
        if not cmt:
            assert False, "����ûLineBע�ͣ���ַ�� %x " % ea
            return
        self.runEnv.curEa = ea
        return self.runExec(cmt)

    def RunBySubName(self, subName):
        for ea, name in idautils.Names():
            if name.find(subName) >= 0:
                return self.RunByEa(ea)

    def _GenByEa(self, ea):
        flag = idc.GetFlags(ea)
        cmt = idaex.GetLineCmt(ea, True)
        if not cmt:
            if idc.isCode(flag):
                assert False, "û��LineA���޷�ִ������Do Update����ea: %x " % ea
            else:
                return

        self.genEnv.curEa = ea
        self.genEnv._Reset()
        try:
            self.genExec(cmt)
        except:
            uuts.LogError("ִ��LineAʧ�ܣ���ַ��  %x  �����룺\n%s\n�����Ƕ�ջ�����\n" % (ea, cmt), traceback.format_exc())
            return

        assert self.genEnv.curLoc is not None, "ִ��LineA�����û�еõ������������ǲ�������������ˣ�name:%s, ea: %x " % (idaapi.netnode(ea).name(), ea)
        assert self.genEnv.curOp is not None, "ִ��LineA�����û�еõ�Ҫ�����Ķ����ǲ�������������ˣ�name:%s, ea: %x " % (idaapi.netnode(ea).name(), ea)
        finder = Finder(self.genEnv.curLoc, self.genEnv.curPa, self.genEnv.curTr, self.genEnv.curAa)
        if idc.isCode(flag):
            if idaapi.isFunc(flag):
                return DU_SetFunc(finder, self.genEnv.curOp)
            else:
                assert False, "�õ�ַ���Ǻ����׵�ַ��������chunk֮��ģ�Ŀǰ��֧�֣���ַ�� %x " % ea
        else:
            return DU_SetGloData(finder, self.genEnv.curOp)
