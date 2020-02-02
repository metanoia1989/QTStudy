#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import QApplication, QPushButton, QColorDialog, QWidget
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QColor

class ColorDialog(QWidget):
    def __init__(self):
        super().__init__()
        color = QColor(0, 0, 0)
        self.setGeometry(300, 300, 350, 280)
        self.setWindowTitle("颜色选择")
        self.button = QPushButton("Dialog", self)
        self.button.setFocusPolicy(Qt.NoFocus)
        self.button.move(20, 20)
        self.button.clicked.connect(self.showDialog)
        self.setFocus()

        self.widget = QWidget(self)
        self.widget.setStyleSheet("QWidget{background-color:%s}" % color.name())
        self.widget.setGeometry(130, 22, 100, 100)

    def showDialog(self):
        color = QColorDialog.getColor()
        if color.isValid():
            self.widget.setStyleSheet("QWidget{background-color:%s}" % color.name())

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = ColorDialog()
    win.show()
    sys.exit(app.exec_())