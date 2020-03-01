#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *

import sys
import requests

class WorkerSignals(QObject):
    '''
    Defines the signals available from a running worker thread.
    data 
        tuple of (identifier data)
    '''
    data = pyqtSignal(tuple)

class Worker(QRunnable):
    '''
    Worker thread 
    Inherits from QRunnable to handler worker thread setup, signals and wrap-up
    :param id: The id for this worker
    :param url: The url to retrieve
    '''

    def __init__(self, id, url):
        super(Worker, self).__init__()
        self.id = id
        self.url = url
        self.signals = WorkerSignals()

    @pyqtSlot()
    def run(self):
        r = requests.get(self.url)

        for line in r.text.splitlines():
            self.signals.data.emit((self.id, line))

class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)

        self.urls = [
            'http://www.example.com',
            'https://martinfitzpatrick.name',
            'https://www.baidu.com',
            'https://www.udemy.com/create-simple-gui-applications-with-python-and-qt/',
            'https://martinfitzpatrick.name/create-simple-gui-applications/'
        ]

        layout = QVBoxLayout()

        self.text = QPlainTextEdit()
        self.text.setReadOnly(True)

        btn = QPushButton("GO GET EM!")
        btn.pressed.connect(self.execute)

        layout.addWidget(self.text)
        layout.addWidget(btn)

        w = QWidget()
        w.setLayout(layout)

        self.setCentralWidget(w)
        self.show()

        self.threadpool = QThreadPool()
        print("Multithreading with maximum %d threads " % self.threadpool.maxThreadCount())

    def execute(self):
        for n, url in enumerate(self.urls):
            worker = Worker(n, url)
            worker.signals.data.connect(self.display_output)
            self.threadpool.start(worker)

    def display_output(self, data):
        id, s = data
        self.text.appendPlainText("WORKER %d: %s" % (id, s))
    

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MainWindow()
    app.exec_()