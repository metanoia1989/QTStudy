#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *

import time, sys, traceback

class WorkerSignals(QObject):
    progress = pyqtSignal(int)

class Worker(QRunnable):
    '''
    Worker thread 
    :param fn: The function to be executed
    :param args: Arguments to make available to the run code
    :param kwargs: Keywords arguments to make available to the run code 
    '''

    def __init__(self, *args, **kwargs):
        super(Worker, self).__init__()
        self.signals = WorkerSignals()

    @pyqtSlot()
    def run(self):
        total_n = 1000
        for n in range(total_n):
            progress_pc = int(100 * float(n) / total_n)
            self.signals.progress.emit(progress_pc)
            time.sleep(0.01)

class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)

        self.counter = 0

        self.bar = QProgressBar()

        layout = QVBoxLayout()

        btn = QPushButton("START IT UP!")
        btn.pressed.connect(self.execute)

        layout.addWidget(self.bar)
        layout.addWidget(btn)

        w = QWidget()
        w.setLayout(layout)

        self.setCentralWidget(w)
        self.show()

        self.threadpool = QThreadPool()
        print("Multithreading with maximum %d threads " % self.threadpool.maxThreadCount())

    def execute(self):
        worker = Worker()
        worker.signals.progress.connect(self.update_progress)
        self.threadpool.start(worker)

    def update_progress(self, progress):
        self.bar.setValue(progress)
    

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MainWindow()
    app.exec_()