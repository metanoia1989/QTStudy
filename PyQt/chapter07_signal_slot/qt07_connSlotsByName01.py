#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
信号和槽自动连接
'''

import sys
from PyQt5.QtCore import QMetaObject, pyqtSlot
from PyQt5.QtWidgets import QApplication, QWidget, QHBoxLayout, QPushButton

class CustWidget(QWidget):

    def __init__(self, parent=None):
        super(CustWidget, self).__init__(parent)

        self.okButton = QPushButton("OK", self)
        # 使用 setObjectName 设置对象名称
        self.okButton.setObjectName("okButton")

        layout = QHBoxLayout()
        layout.addWidget(self.okButton)
        self.setLayout(layout)

        QMetaObject.connectSlotsByName(self)

    @pyqtSlot()
    def on_okButton_clicked(self):
        print("点击了OK按钮")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = CustWidget()
    win.show()
    sys.exit(app.exec_())