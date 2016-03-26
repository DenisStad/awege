from project import Project

# projectPath = '../test/'
# p = Project.CreateNew('test', projectPath)
# p.addFile('../test/AutoScreenshot.png')
# p.saveToFile()

import modules.build.build

projectPath = '../test/test.awege'
project = Project.LoadFromProjectFilePath(projectPath)

build = modules.build.build.initializeModule(project)
build.buildTarget(build.getTarget('default'))
