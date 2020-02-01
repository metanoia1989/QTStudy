#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
partial 传递额外参数
'''

import sys
from functools import partial
from PyQt5.QtWidgets import QMainWindow, QHBoxLayout, QPushButton, QApplication, QWidget, QMessageBox

class WinForm(QMainWindow):

    def __init__(self, parent=None):
        super(WinForm, self).__init__(parent)
        self.setWindowTitle("信号和槽传递额外参数例子")
        button1 = QPushButton("Button1")
        button2 = QPushButton("Button2")
        button1.clicked.connect(partial(self.onButtonClick, 1))
        button2.clicked.connect(partial(self.onButtonClick, 2))

        layout = QHBoxLayout()
        layout.addWidget(button1)
        layout.addWidget(button2)

        main_frame = QWidget()
        main_frame.setLayout(layout)
        self.setCentralWidget(main_frame)

    def onButtonClick(self, n):
        print("The button{0} 被按下了".format(n))
        QMessageBox.information(self, "信息提示框", "Button {0}：".format(n))

if __name__ == "__main__":
    app = QApplication(sys.argv)
    form = WinForm()
    form.show()
    sys.exit(app.exec_())

