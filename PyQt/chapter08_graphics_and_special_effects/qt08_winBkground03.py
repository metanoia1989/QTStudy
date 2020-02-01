#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import QMainWindow, QApplication, QLabel, QWidget, QVBoxLayout, QPushButton
from PyQt5.QtGui import QPalette, QBrush, QPixmap
from PyQt5.QtCore import Qt

app = QApplication(sys.argv)
win = QMainWindow()
win.setWindowTitle("界面背景图片设置")

palette = QPalette()
palette.setColor(QPalette.Background, Qt.red)
win.setPalette(palette)

win.resize(350, 250)
win.show()
sys.exit(app.exec_())