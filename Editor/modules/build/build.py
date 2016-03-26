import json
import os
import importlib.util

def makeDefaultConfig():
    config = {}
    config['targets'] = [ { 'name': 'default', 'platform': 'OSX', 'active': True, 'targetLocation': '/Users/denis/Projects/Awege/testbuild' } ]
    return config

def loadConfigFromFile():
    configFile = open(os.path.join(os.path.dirname(__file__), 'config.json'))
    configContents = configFile.read()
    configFile.close()
    config = json.loads(configContents)

def loadConfig():
    try:
        config = loadConfigFromFile()
    except Exception:
        config = makeDefaultConfig()
    return config

class Build:

    def __init__(self, project, config):
        self.__project = project
        self.__config = config

    def buildTarget(self, target):
        spec = importlib.util.spec_from_file_location("Platform", os.path.join(os.path.dirname(__file__), 'platforms', target['platform'], 'build.py'))
        platform = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(platform)

        platform.build(target, self.__project)

    def getTarget(self, name):
        for target in self.__config['targets']:
            if target['name'] == 'default':
                return target

def initializeModule(project):
    config = loadConfig()
    return Build(project, config)
