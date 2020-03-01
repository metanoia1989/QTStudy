#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *

import time, sys

class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)

        self.counter = 0

        layout = QVBoxLayout()
        self.label = QLabel("Start")
        btn = QPushButton("DANGER!")
        btn.pressed.connect(self.oh_no)

        btn2 = QPushButton("?")
        btn2.pressed.connect(self.change_message)

        layout.addWidget(self.label)
        layout.addWidget(btn)
        layout.addWidget(btn2)

        w = QWidget()
        w.setLayout(layout)

        self.setCentralWidget(w)
        self.show()

    def oh_no(self):
        self.message = "Pressed"

        for _ in range(100):
            time.sleep(0.1)
            self.label.setText(self.message)
            QApplication.processEvents()

    def change_message(self):
        self.message = "OH NO"

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MainWindow()
    app.exec_()