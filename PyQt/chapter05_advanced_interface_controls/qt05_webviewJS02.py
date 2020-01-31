#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout
from PyQt5.QtWebEngineWidgets import QWebEngineView
from PyQt5.QtWebChannel import QWebChannel
from PyQt5.QtCore import QUrl
from MySharedObject import MySharedObject

app = QApplication(sys.argv)
win = QWidget()
win.setWindowTitle("Web页面中的JavaScript与QWebEngineView交互例子")

layout = QVBoxLayout()
win.setLayout(layout)

view = QWebEngineView()
htmlUrl = "http://localhost:9000/web/index.html"
view.load(QUrl(htmlUrl))

# 创建一个 QWebChannel 对象，用来传递pyqt参数到JavaScript
channel = QWebChannel()
myObj = MySharedObject()
channel.registerObject("bridge", myObj)
view.page().setWebChannel(channel)


layout.addWidget(view)

win.show()
sys.exit(app.exec_())