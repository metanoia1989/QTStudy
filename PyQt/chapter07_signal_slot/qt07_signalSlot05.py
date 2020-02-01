#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
自定义信号和内置槽
'''

import sys
from PyQt5.QtCore import pyqtSignal
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton

class Main(QWidget):
    button_clicked_signal = pyqtSignal()

    def __init__(self, parent=None):
        super(Main, self).__init__(parent)
        self.resize(330, 50)
        self.setWindowTitle("自定义信号和内置槽示例")

        btn = QPushButton("关闭", self)
        # 连接信号/槽
        btn.clicked.connect(self.btn_clicked)
        # 接收信号，连接到槽
        self.button_clicked_signal.connect(self.close)

    def btn_clicked(self):
        self.button_clicked_signal.emit()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    main = Main()
    main.show()
    sys.exit(app.exec_())