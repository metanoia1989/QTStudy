#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
跨线程信号槽
'''

import sys
from PyQt5.QtCore import QThread, pyqtSignal
from PyQt5.QtWidgets import QApplication, QWidget

class Main(QWidget):
    def __init__(self, parent=None):
        super(Main, self).__init__(parent)

        # 创建一个线程实例并设置名称、变量、信号槽
        self.thread = MyThread()
        self.thread.setIdentity("thread1")
        self.thread.sinOut.connect(self.outText)
        self.thread.setVal(6)

    def outText(self, text):
        print(text)

class MyThread(QThread):
    sinOut = pyqtSignal(str)

    def __init__(self, parent=None):
        super(MyThread, self).__init__(parent)
        self.identity = None

    def setIdentity(self, text):
        self.identity = text

    def setVal(self, val):
        self.times = int(val)
        # 执行线程的run方法
        self.start()

    def run(self):
        while self.times > 0 and self.identity:
            # 发射信号
            self.sinOut.emit(self.identity + " ==> " + str(self.times))
            self.times -= 1

if __name__ == "__main__":
    app = QApplication(sys.argv)
    main = Main()
    main.show()
    sys.exit(app.exec_())