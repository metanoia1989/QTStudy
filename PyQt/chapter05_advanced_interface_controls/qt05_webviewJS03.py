#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
加载本地网页，并且禁用JS代码
'''

import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton
from PyQt5.QtWebEngineWidgets import QWebEngineView, QWebEngineSettings
from PyQt5.QtWebChannel import QWebChannel
from PyQt5.QtCore import QUrl
from PyQt5.QtGui import QIcon
from MySharedObject import MySharedObject

class Web(QWebEngineView):
    def load(self, url):
        self.setUrl(QUrl(url))

    def adjustTitle(self):
        self.setWindowTitle(self.title())

    def disableJS(self):
        settings = QWebEngineSettings.globalSettings()
        settings.setAttribute(QWebEngineSettings.JavascriptEnabled, False)

class Main(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle("Name")
        self.setWindowIcon(QIcon("./images/cartoon1.ico"))

        web = Web()
        web.load("http://localhost:9000/web/index2.html")
        web.disableJS()
        web.adjustTitle()

        self.btn = QPushButton("Button", self)
        self.btn.resize(self.btn.sizeHint())

        lay = QVBoxLayout(self)
        lay.addWidget(self.btn)
        lay.addWidget(web)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    main = Main()
    main.show()
    sys.exit(app.exec_())