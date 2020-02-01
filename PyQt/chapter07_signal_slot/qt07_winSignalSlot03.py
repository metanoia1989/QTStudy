#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
控件中的信号槽通信
'''

import sys
from PyQt5.QtWidgets import QMainWindow, QHBoxLayout, QPushButton, QApplication, QWidget, QMessageBox
from PyQt5.QtCore import pyqtSignal

class WinForm(QMainWindow):
    btnlClickedSignal = pyqtSignal(int)

    def __init__(self, parent=None):
        super(WinForm, self).__init__(parent)
        self.setWindowTitle("控件中的信号槽通信")
        # 声明自定义的信号
        self.btnlClickedSignal.connect(self.getSignal)
        self.button1 = QPushButton("Button1")
        # 使用信号连接槽函数，槽函数不用加括号
        self.button1.clicked.connect(self.onButtonClick)

        layout = QHBoxLayout()
        layout.addWidget(self.button1)

        main_frame = QWidget()
        main_frame.setLayout(layout)
        self.setCentralWidget(main_frame)

    def onButtonClick(self):
        print("The button1 被按下了")
        self.btnlClickedSignal.emit(10)

    def getSignal(self, intVal):
        QMessageBox.information(self, "信息提示框", "收到信号传过来的值：" + str(intVal))

if __name__ == "__main__":
    app = QApplication(sys.argv)
    form = WinForm()
    form.show()
    sys.exit(app.exec_())

