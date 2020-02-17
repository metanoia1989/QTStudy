import sys
import os
from PySide2.QtGui import QGuiApplication
from PySide2.QtQml import QQmlApplicationEngine
from PySide2.QtCore import QUrl

if __name__ == "__main__":
    app = QGuiApplication(sys.argv)
    engine = QQmlApplicationEngine()
    curPath = os.path.abspath(os.path.dirname(__file__))
    qmlFile = os.path.join(curPath, "main.qml")
    engine.load(QUrl.fromLocalFile(qmlFile))

    if not engine.rootObjects():
        sys.exit(-1)
    
    sys.exit(app.exec_())