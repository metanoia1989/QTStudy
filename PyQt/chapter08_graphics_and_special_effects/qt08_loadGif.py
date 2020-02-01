#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import QApplication, QLabel, QWidget
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QMovie

class LoadingGifWin(QWidget):
    def __init__(self, parent=None):
        super(LoadingGifWin, self).__init__(parent)
        self.label = QLabel("", self)
        self.setFixedSize(128, 128)
        self.setWindowFlags(Qt.Dialog|Qt.CustomizeWindowHint)
        self.movie = QMovie("./images/loading.gif")
        self.label.setMovie(self.movie)
        self.movie.start()

    
if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = LoadingGifWin()
    win.show()
    sys.exit(app.exec_())