import os
import shutil
# from mod_pbxproj import XcodeProject
from modules.build.platforms.OSX.mod_pbxproj.xcodeProject import XcodeProject

def copyFiles(sourceDir, targetDir):
    names = os.listdir(sourceDir)
    for name in names:
        srcname = os.path.join(sourceDir, name)
        dstname = os.path.join(targetDir, name)
        if os.path.exists(dstname):
            continue
        if not os.path.exists(targetDir):
            os.makedirs(targetDir)
        if os.path.isdir(srcname):
            copyFiles(srcname, dstname)
        else:
            shutil.copy(srcname, dstname)

def getLocationOfXcodeFilesToCopy():
    return os.path.join(os.path.dirname(__file__), 'Awege')

def getXcodeProject(targetDir):
    path = os.path.join(targetDir, 'Awege.xcodeproj', 'project.pbxproj')
    if not os.path.exists(path):
        raise Exception("Xcode project not found")
    xcodeProject = XcodeProject.Load(path)
    return xcodeProject

def build(target, project):
    targetLocation = target['targetLocation']
    try:
        os.makedirs(targetLocation)
    except OSError:
        pass

    names = os.listdir(targetLocation)
    if 'Awege.xcodeproj' not in names:
        copyFiles(getLocationOfXcodeFilesToCopy(), targetLocation)

    xcodeProject = getXcodeProject(targetLocation)
    xcodeProject.backup()

    selectors = [ 'Platform:All', 'Platform:OSX', 'Target:All', 'Target:' + target['name'] ]

    group = xcodeProject.get_or_create_group('AwegeRuntime')
    for selector in selectors:
        files = project.files().getFilesLabeledWithAllOf([ selector, 'Runtime' ])
        for trackedFile in files:
            xcodeProject.add_file_if_doesnt_exist(trackedFile.getFilename(), parent=group)

    group = xcodeProject.get_or_create_group('AwegeAssets')
    for selector in selectors:
        files = project.files().getFilesLabeledWithAllOf([ selector, 'Asset' ])
        for trackedFile in files:
            xcodeProject.add_file_if_doesnt_exist(trackedFile.getFilename(), parent=group)

    xcodeProject.save()
