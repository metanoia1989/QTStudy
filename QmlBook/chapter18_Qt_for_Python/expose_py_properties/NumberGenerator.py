import sys
import os
import random

from PySide2.QtGui import QGuiApplication
from PySide2.QtQml import QQmlApplicationEngine, qmlRegisterType
from PySide2.QtCore import QUrl
from PySide2.QtCore import QObject, Signal, Slot, Property

class NumberGenerator(QObject):
    numberChanged = Signal(int)
    maxNumberChanged = Signal()

    def __init__(self):
        super(NumberGenerator, self).__init__()
        self.__number = 42
        self.__max_number = 99

    #max number
    @Slot(int)
    def setMaxNumber(self, val):
        self.set_max_number(val)

    def set_max_number(self, val):
        if val < 0:
            val = 0
        
        if self.__max_number != val:
            self.__max_number = val
            self.maxNumberChanged.emit()
        
        if self.__number > self.__max_number:
            self.__set_number(self.__max_number)

    def get_max_number(self):
        return self.__max_number

    # number
    @Slot()
    def updateNumber(self):
        self.__set_number(random.randint(0, self.__max_number))

    def __set_number(self, val):
        if self.__number != val:
            self.__number = val
            self.numberChanged.emit(int)

    def get_number(self):
        return self.__number

    number = Property(int, get_number, notify=numberChanged)
    maxNumber = Property(int, get_max_number, set_max_number, notify=maxNumberChanged)


if __name__ == "__main__":
    app = QGuiApplication(sys.argv)
    engine = QQmlApplicationEngine()

    # 暴露python类给qml
    number_generator = NumberGenerator()
    engine.rootContext().setContextProperty("numberGenerator", number_generator)

    curPath = os.path.abspath(os.path.dirname(__file__))
    qmlFile = os.path.join(curPath, "main.qml")
    engine.load(QUrl.fromLocalFile(qmlFile))

    if not engine.rootObjects():
        sys.exit(-1)
    
    sys.exit(app.exec_())
