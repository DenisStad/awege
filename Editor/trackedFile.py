import uuid
import os.path, time

class TrackedFile:

    @staticmethod
    def FromFilename(filename):
        if not os.path.exists(filename):
            raise Exception("File does not exist")
        file = TrackedFile()
        file.__generateID()
        file.__filename = filename
        file.__creationTime = time.ctime(os.path.getctime(filename))
        return file

    @staticmethod
    def FromDictionary(object):
        file = TrackedFile()
        file.__id = object['id']
        file.__filename = object['filename']
        file.__creationTime = object['creationTime']
        file.__labels = set(object['labels'])
        return file

    def toDictionary(self):
        object = {}
        object['id'] = self.__id
        object['filename'] = self.__filename
        object['creationTime'] = self.__creationTime
        object['labels'] = list(self.__labels)
        return object

    def __init__(self):
        self.__labels = set()

    def getFilename(self):
        return self.__filename

    def getID(self):
        return self.id

    def __generateID(self):
        self.__id = str(uuid.uuid1())

    def addLabel(self, label):
        self.__labels.add(label)

    def removeLabel(self, label):
        self.__labels.remove(label)

    def getLabels(self):
        return self.__labels.copy()
