#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *

import time, sys, traceback

class WorkerSignals(QObject):
    finished = pyqtSignal()
    error = pyqtSignal(tuple)
    result = pyqtSignal(object)

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
        self.signals = WorkerSignals()

    @pyqtSlot()
    def run(self):
        try:
            result = self.fn(
                *self.args, **self.kwargs,
                status=self.signals.status,
                progress=self.signals.progress
            )
        except: 
            traceback.print_exc()
            exctype, value = sys.exc_info()[:2]
            self.signals.error.emit((exctype, value, traceback.format_exc()))
        else:
            self.signals.result.emit(result)
        finally:
            self.signals.finished.emit()

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
        def execute_this_fn():
            for n in range(0, 5):
                time.sleep(1)
            return "Done."

        def print_output(s):
            print(s)
        
        def thread_complete():
            print("THREAD COMPLETE!")

        worker = Worker(execute_this_fn)
        worker.signals.result.connect(print_output)
        worker.signals.finished.connect(thread_complete)

        self.threadpool.start(worker)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MainWindow()
    app.exec_()