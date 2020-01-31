#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import QApplication, QWidget, QFormLayout, QLabel, QLineEdit, QTextEdit
from PyQt5.QtCore import Qt

class Winform(QWidget):
    def __init__(self, parent=None):
        super(Winform, self).__init__(parent)
        self.initUI()

    def initUI(self):
        self.setWindowTitle("故障报告")
        self.resize(400, 100)

        formLayout = QFormLayout()
        lbl1 = QLabel("标签1")
        lineEdit1 = QLineEdit()
        lbl2 = QLabel("标签1")
        lineEdit2 = QLineEdit()
        lbl3 = QLabel("标签3")
        lineEdit3 = QLineEdit()

        formLayout.addRow(lbl1, lineEdit1)
        formLayout.addRow(lbl2, lineEdit2)
        formLayout.addRow(lbl3, lineEdit3)

        self.setLayout(formLayout)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    form = Winform()
    form.show()
    sys.exit(app.exec_())