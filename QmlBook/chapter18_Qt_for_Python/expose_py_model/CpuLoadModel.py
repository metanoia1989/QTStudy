import sys
import os
import psutil

from PySide2.QtGui import QGuiApplication
from PySide2.QtQml import QQmlApplicationEngine, qmlRegisterType
from PySide2.QtCore import QUrl, QTimer, QAbstractListModel
from PySide2.QtCore import QObject, Signal, Slot, Property, Qt

class CpuLoadModel(QAbstractListModel):
    def __init__(self):
        super(CpuLoadModel, self).__init__()

        self.__cpu_count = psutil.cpu_count()
        self.__cpu_load = [0] * self.__cpu_count

        self.__update_timer = QTimer(self)
        self.__update_timer.setInterval(1000)
        self.__update_timer.timeout.connect(self.__update)
        self.__update_timer.start()

        # 第一个调用返回无效的数据
        psutil.cpu_percent(percpu=True)

    def __update(self):
        self.__cpu_load = psutil.cpu_percent(percpu=True)
        self.dataChanged.emit(self.index(0,0), self.index(self.__cpu_count-1,0))

    def rowCount(self, parent):
        return self.__cpu_count

    def data(self, index, role):
        if (role == Qt.DisplayRole and
            index.row() >=0 and 
            index.row() < len(self.__cpu_load) and
            index.column() == 0):
            return self.__cpu_load[index.row()]
        else:
            return None




if __name__ == "__main__":
    app = QGuiApplication(sys.argv)
    engine = QQmlApplicationEngine()

    # 暴露python类给qml
    qmlRegisterType(CpuLoadModel, "PsUtils", 1, 0, "CpuLoadModel")

    curPath = os.path.abspath(os.path.dirname(__file__))
    qmlFile = os.path.join(curPath, "main.qml")
    engine.load(QUrl.fromLocalFile(qmlFile))

    if not engine.rootObjects():
        sys.exit(-1)
    
    sys.exit(app.exec_())
