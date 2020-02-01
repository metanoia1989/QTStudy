#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *

class AppWidget(QWidget):
    def __init__(self, parent=None):
        super(AppWidget, self).__init__(parent)
        self.setWindowTitle("界面风格例子")

        horizontalLayout = QHBoxLayout()
        self.styleLabel = QLabel("Set Style: ")
        self.styleComboBox = QComboBox()
        self.styleComboBox.addItems(QStyleFactory.keys())
        # 选择当前界面风格
        index = self.styleComboBox.findText(
            QApplication.style().objectName(),
            Qt.MatchFixedString
        )
        # 设置当前界面风格
        self.styleComboBox.setCurrentIndex(index)
        self.styleComboBox.activated[str].connect(self.handleStyleChanged)

        horizontalLayout.addWidget(self.styleLabel)
        horizontalLayout.addWidget(self.styleComboBox)
        self.setLayout(horizontalLayout)

    # 改变界面风格
    def handleStyleChanged(self, style):
        QApplication.setStyle(style)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = AppWidget()
    win.show()
    sys.exit(app.exec_())