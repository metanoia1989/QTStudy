#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
重新实现信号槽函数
'''

import sys
from PyQt5.QtWidgets import *
from PyQt5.QtCore import Qt

class WinForm(QWidget):

    def __init__(self, parent=None):
        super(WinForm, self).__init__(parent)
        self.initUI()

    def initUI(self):
        self.setGeometry(300, 300, 400, 300)
        self.setWindowTitle("重新实现信号槽函数例子")

    # 重新实现信号槽函数
    def keyPressEvent(self, e):
        if e.key() == Qt.Key_Escape:
            self.close()
        elif e.key() == Qt.Key_Alt:
            self.setWindowTitle("按下Alt键")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    form = WinForm()
    form.show()
    sys.exit(app.exec_())

