#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from PyQt5.QtWidgets import QMainWindow, QStackedLayout, QWidget, QApplication, QLabel
from PyQt5.QtCore import Qt
from layout_colorwidget import Color
import sys

class MainWindow(QMainWindow):
    def __init__(self, *args, **kwargs):
        super(MainWindow, self).__init__(*args, **kwargs)
        self.setWindowTitle("My Awesome App")
        self.resize(300, 300)

        widget = QWidget()
        
        # redColor = Color("red", self)
        # redColor.setGeometry(0, 0, 100, 100)

        label = QLabel("测试文件透明层", self)
        label.resize(120, 100)

        yellowColor = Color("yellow", self)
        yellowColor.setGeometry(0, 0, 150, 150)

        # label.raise_()
        yellowColor.stackUnder(label)
        label.setStyleSheet("background-color: rgba(0,0,0,0.1)")

        self.setCentralWidget(widget)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MainWindow()
    win.show()
    app.exec()