#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import sys
from PyQt5.QtWidgets import *
from PyQt5.QtCore import pyqtSignal

class CustWin(QWidget):
    signal1 = pyqtSignal(list)
    signal2 = pyqtSignal(dict)
    signal3 = pyqtSignal(tuple)

    def __init__(self, parent=None):
        super(CustWin, self).__init__(parent)
        btnLayout = QHBoxLayout()
        mainLayout = QVBoxLayout()

        btn1 = QPushButton("发射带参数的信号")
        btnLayout.addStretch()
        btnLayout.addWidget(btn1)

        mainLayout.addLayout(btnLayout)
        self.setLayout(mainLayout)

        btn1.clicked.connect(self.emitDictSign)

    def emitDictSign(self):
        self.signal1.emit([1, 2, 3, 4])
        self.signal2.emit({"monday": 1, "tuesday": 2, "Wednesday": 3})
        self.signal3.emit((1, "2", ("learn", "python")))


class WinForm(QWidget):

    def __init__(self, parent=None):
        super(WinForm, self).__init__(parent)
        self.setWindowTitle("部件中的信号发射参数")

        widget = CustWin(self)
        mainLayout = QVBoxLayout()
        mainLayout.addWidget(widget)
        self.setLayout(mainLayout)
        widget.signal1.connect(self.displayDict)
        widget.signal2.connect(self.displayList)
        widget.signal3.connect(self.displayTuple)

    def displayDict(self, data):
        print("--- displayDict ---")
        print(type(data))

    def displayList(self, data):
        print("--- displayList ---")
        print(data)

    def displayTuple(self, data):
        print("--- displayTuple ---")
        print(data)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    form = WinForm()
    form.show()
    sys.exit(app.exec_())

