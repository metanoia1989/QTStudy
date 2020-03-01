#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *

import time, sys

class Worker(QRunnable):
    '''
    Worker thread 
    :param fn: The function to be executed
    :param args: Arguments to make available to the run code
    :param kwargs: Keywords arguments to make available to the run code 
    '''

    def __init__(self, fn, *args, **kwargs):
        super(Worker, self).__init__()
        self.fn = fn
        self.args = args
        self.kwargs = kwargs

    @pyqtSlot()
    def run(self):
        self.fn(*self.args, **self.kwargs)

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
        def fn(thread_name):
            print("Thread %s start..." % thread_name)
            time.sleep(4)
            print("Thread %s end..." % thread_name)

        worker1 = Worker(fn, "one")
        worker2 = Worker(fn, "two")
        worker3 = Worker(fn, "three")
        self.threadpool.start(worker1)
        self.threadpool.start(worker2)
        self.threadpool.start(worker3)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MainWindow()
    app.exec_()