#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
无边窗口
'''

import sys
from PyQt5.QtCore import Qt, QTimer
from PyQt5.QtWidgets import QMainWindow, QApplication

class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.resize(477, 258)
        self.setWindowTitle("设置窗口样式例子")
        # 设置窗口样式为窗口无边框化
        # self.setWindowFlag(Qt.SubWindow)
        self.setWindowFlag(Qt.FramelessWindowHint)
        self.setObjectName("MainWindow")
        self.setStyleSheet("#MainWindow{border-image:url(images/python.jpg);}")

        QTimer.singleShot(5000, self.close)
        

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MainWindow()
    win.show()
    sys.exit(app.exec_())