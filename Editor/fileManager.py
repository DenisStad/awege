from trackedFile import TrackedFile

class FileManager:

    def __init__(self):
        self.setFilesList([])

    def getFilesLabeledWithAllOf(self, labels):
        foundFiles = []

        for trackedFile in self.__files:
            fileHasAllLabels = True
            for label in labels:
                if label not in trackedFile.getLabels():
                    fileHasAllLabels = False
                    break

            if fileHasAllLabels:
                foundFiles.append(trackedFile)

        return foundFiles

    def getFilesLabeledWithOneOf(self, labels):
        foundFiles = []

        for trackedFile in self.__files:
            for label in labels:
                if label in trackedFile.getLabels():
                    foundFiles.append(trackedFile)
                    break

        return foundFiles

    def getFilesLabeled(self, label):
        foundFiles = []

        for trackedFile in self.__files:
            if label in trackedFile.getLabels():
                foundFiles.append(trackedFile)
                break

        return foundFiles

    def getFilesWithFullName(self, name):
        for trackedFile in self.__files:
            if trackedFile.getFilename() == name:
                return trackedFile

    def addFile(self, filename):
        trackedFile = TrackedFile.FromFilename(filename)
        self.__files.append(trackedFile)

    def getFilesList(self):
        return self.__files

    def setFilesList(self, fileList):
        self.__files = fileList
