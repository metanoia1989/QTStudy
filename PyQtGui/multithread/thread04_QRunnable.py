#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *

import time, sys

class Worker(QRunnable):
    @pyqtSlot()
    def run(self):
        print("Thread start")
        time.sleep(5)
        print("Thread complete")

class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)

        self.counter = 0

        layout = QVBoxLayout()
        self.label = QLabel("Start")
        btn = QPushButton("DANGER!")
        btn.pressed.connect(self.oh_no)

        layout.addWidget(self.label)
        layout.addWidget(btn)

        w = QWidget()
        w.setLayout(layout)

        self.setCentralWidget(w)
        self.show()

        self.threadpool = QThreadPool()
        print("Multithreading with maximum %d threads " % self.threadpool.maxThreadCount())

    def oh_no(self):
        worker = Worker()
        self.threadpool.start(worker)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MainWindow()
    app.exec_()