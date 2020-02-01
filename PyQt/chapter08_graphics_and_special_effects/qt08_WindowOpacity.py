#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import QApplication, QMainWindow

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = QMainWindow()
    win.setWindowTitle("窗口的透明度设置")
    win.setWindowOpacity(0.5)

    win.resize(350, 250)
    win.show()
    sys.exit(app.exec_())