#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QHBoxLayout, QPushButton

class WindowDemo(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("addStretch例子")
        self.resize(800, 50)

        hbox = QHBoxLayout()


        hbox.addWidget(QPushButton(str(1)))
        hbox.addWidget(QPushButton(str(2)))
        hbox.addWidget(QPushButton(str(3)))
        hbox.addWidget(QPushButton(str(4)))
        hbox.addWidget(QPushButton(str(5)))

        hbox.addStretch(0)

        self.setLayout(hbox)
        
if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = WindowDemo()
    win.show()
    sys.exit(app.exec_())