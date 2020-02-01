#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
信号槽连接滑块LCD
'''

import sys
from PyQt5.QtWidgets import QWidget, QApplication, QVBoxLayout, QLCDNumber, QSlider
from PyQt5.QtCore import Qt

class WinForm(QWidget):

    def __init__(self, parent=None):
        super(WinForm, self).__init__(parent)
        self.initUI()

    def initUI(self):
        self.setGeometry(300, 300, 350, 150)
        self.setWindowTitle("信号与槽：连接滑块LCD")

        lcd = QLCDNumber(self)
        slider = QSlider(Qt.Horizontal, self)

        vBox = QVBoxLayout()
        vBox.addWidget(lcd)
        vBox.addWidget(slider)
        self.setLayout(vBox)

        slider.valueChanged.connect(lcd.display)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    form = WinForm()
    form.show()
    sys.exit(app.exec_())

