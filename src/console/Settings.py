import json
import os

class Settings:
    filePath = None
    data = None

    def __init__(self, filePath):
        if not os.path.exists(filePath):
            self.filePath = "settings-default.json"
        self.filePath = filePath;
        self.load()

    def load(self):
        file = open(self.filePath, 'r')
        self.data = json.load(file)
        file.close()

    def save(self):
        file = open(self.filePath, 'w')
        json.dump(self.data, file)
        file.close()
