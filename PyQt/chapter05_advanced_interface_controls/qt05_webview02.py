#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtWebEngineWidgets import *

class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.setWindowTitle("加载并显示本地页面例子")
        self.setGeometry(5, 30, 755, 530)
        self.browser = QWebEngineView()
        # 加载外部页面
        url = r"F:/WORKSPACE/QT/QTStudy/PyQt/chapter05_advanced_interface_controls/web/index.html"
        self.browser.load(QUrl(url))
        self.setCentralWidget(self.browser)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MainWindow()
    win.show()
    sys.exit(app.exec_())