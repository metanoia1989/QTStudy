#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import *

class WindowDemo(QWidget):
    def __init__(self):
        super().__init__()

        combo = QComboBox(self)
        combo.setObjectName("myQComboBox")
        combo.addItem("Window")
        combo.addItem("Ubuntu")
        combo.addItem("Red Hat")
        combo.move(50, 50)

        self.setGeometry(250, 200, 320, 150)
        self.setWindowTitle("QSS样式")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = WindowDemo()
    qssStyle = '''
    QComboBox#myQComboBox::drop-down {
        image: url(./images/dropdown.png)
    }
    '''
    win.setStyleSheet(qssStyle)
    win.show()
    sys.exit(app.exec_())