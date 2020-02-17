import sys
import os
import random

from PySide2.QtGui import QGuiApplication
from PySide2.QtQml import QQmlApplicationEngine, qmlRegisterType
from PySide2.QtCore import QUrl
from PySide2.QtCore import QObject, Signal, Slot

class NumberGenerator(QObject):
    nextNumber = Signal(int)

    def __init__(self):
        super(NumberGenerator, self).__init__()

    @Slot()
    def giveNumber(self):
        self.nextNumber.emit(random.randint(0, 99))


if __name__ == "__main__":
    app = QGuiApplication(sys.argv)
    engine = QQmlApplicationEngine()

    # 暴露python类给qml
    qmlRegisterType(NumberGenerator, "Generators", 1, 0, "NumberGenerator")

    curPath = os.path.abspath(os.path.dirname(__file__))
    qmlFile = os.path.join(curPath, "main.qml")
    engine.load(QUrl.fromLocalFile(qmlFile))

    if not engine.rootObjects():
        sys.exit(-1)
    
    sys.exit(app.exec_())
