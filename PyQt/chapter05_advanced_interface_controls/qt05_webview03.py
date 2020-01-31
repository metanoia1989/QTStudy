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
        self.setGeometry(5, 30, 1355, 730)
        self.browser = QWebEngineView()
        # 加载html代码
        self.browser.setHtml('''
		<!DOCTYPE html>
		<html>
			<head>
				<meta charset="UTF-8">
				<title></title>
			</head>
			<body>
				<h1>Hello PyQt5</h1>
				<h1>Hello PyQt5</h1>
                <h1>hello PyQt5</h1>
                <h1>hello PyQt5</h1>
                <h1>hello PyQt5</h1>
                <h1>Hello PyQt5</h1>
                
			</body>
		</html>
        ''')
        self.setCentralWidget(self.browser)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MainWindow()
    win.show()
    sys.exit(app.exec_())