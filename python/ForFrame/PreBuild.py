#coding=gbk
import subprocess
import os

#-----------------------------------------------------------------
_projRoot = os.getenv('zhpProjRootDir')
if _projRoot == None:
    _projRoot = "F:/proj/"

_cppPath = _projRoot + "cpp/"

assetExploreFullName = os.getenv('AssetExplorePath')
if assetExploreFullName == None:
    assetExploreFullName = _cppPath + "Frame/Libs/AssetExplore.exe"
if not os.path.exists(assetExploreFullName):
    assetExploreFullName = _cppPath + r"apps/DEBUG/AssetExplore.exe"

_allProjectPath = [
    #apps
    "apps/AssetExplore/",
    "apps/CheckServer/",
    "apps/CSViewer/",
    "apps/ExtractFeatureCode/",
    #tools
    #"tools/HijackDll/",
    "tools/LoginHlp/",
    "tools/RecordMap/",
    #subs
    "subs/FIFA/Console/",
    "subs/FIFA/Game/",
    "subs/FIFA/Login/",
    "subs/FIFA/Test/",
    "subs/FIFA/CrackData/FeatureCode/AutoUpdate/",
    #lfzl
    "subs/PathOfExile/Console/",
    "subs/PathOfExile/Game/",
    "subs/PathOfExile/Login/",
]
#-----------------------------------------------------------------
def RunAssetExplore(inFile, outFile):
    p = subprocess.Popen(assetExploreFullName + " /i " + inFile + " /o " + outFile + " -c", stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    (stdoutput, erroutput) = p.communicate()
    print(stdoutput)
    print(erroutput)

def GenPerFilePair(projPath):
    theFile = projPath + "as.assf"
    if not os.path.isfile(theFile):
        print(theFile + " �ļ�������")
        return
    resDir = projPath + "res/"
    if not os.path.isdir(resDir):
        print(resDir + " resĿ¼������")
        return
    return theFile, resDir + "as.assf"

def GenAllFile():
    inFiles = ""
    outFiles = ""
    for path in _allProjectPath:
        res = GenPerFilePair(_cppPath + path)
        if res == None:
            # assert False, ""
            continue
        inFiles += res[0] + ";"
        outFiles += res[1] + ";"
    return inFiles, outFiles

def DeleteAllFile():
    for path in _allProjectPath:
        theFile = _cppPath + path + "res/as.assf"
        if os.path.exists(theFile):
            print ("ɾ���ļ���" + theFile)
            os.remove(theFile)

#Application StaticLibrary DynamicLibrary
_configurationType = os.getenv('ConfigurationType_')
if _configurationType == None:
    #DeleteAllFile()
    RunAssetExplore(*GenAllFile())

elif _configurationType == "StaticLibrary":
    RunAssetExplore(*GenAllFile())
else:
    def GenCurProj():
        projDir = os.getenv('ProjectDir_')
        if projDir == None:
            print("ProjectDir_��������������")
            return
        res = GenPerFilePair(projDir)
        if res == None:
            assert False, ""
            return
        RunAssetExplore(*res)
    GenCurProj()
