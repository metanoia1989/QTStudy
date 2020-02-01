#!/usr/bin/env python3
# -*- coding: utf-8 -*-
'''
多线程更新数据
'''
import sys 
import time
from PyQt5.QtCore import QThread, pyqtSignal, QDateTime
from PyQt5.QtWidgets import QApplication, QDialog, QLineEdit

class BackendThraed(QThread):
    # 通过类成员对象定义信号对象
    update_date = pyqtSignal(str)

    def run(self):
        while True:
            date = QDateTime.currentDateTime()
            currTime = date.toString("yyyy-MM-dd hh:mm:ss")
            self.update_date.emit(str(currTime))
            time.sleep(1)

class Window(QDialog):
    def __init__(self):
        super(Window, self).__init__()
        self.setWindowTitle("PyQt5界面实时更新例子")
        self.resize(400, 100)

        self.input = QLineEdit(self) 
        self.input.resize(400, 100)
        self.initUI()

    def initUI(self):
        # 创建线程
        self.backend = BackendThraed()
        # 连接信号
        self.backend.update_date.connect(self.handleDisplay)
        # 开始线程
        self.backend.start()

    # 将当前时间输出到文本框
    def handleDisplay(self, data):
        self.input.setText(data)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    sys.exit(app.exec_())
