#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QMainWindow, QApplication

'''
自定义窗口类 全屏
'''
class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.resize(477, 258)
        self.setWindowTitle("设置窗口样式例子")
        # 设置窗口样式为窗口无边框化
        self.setWindowFlag(Qt.FramelessWindowHint)
        # 设置窗口背景颜色
        self.setStyleSheet("background-color:blue;")

    '''覆盖最大化函数'''
    def showMaximized(self):
        desktop = QApplication.desktop()
        rect = desktop.availableGeometry()
        self.setGeometry(rect)
        self.show()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MainWindow()
    win.showMaximized()
    sys.exit(app.exec_())