from project import Project

projectPath = '../test/test.awege'
project = Project.LoadFromProjectFilePath(projectPath)
print(project)
