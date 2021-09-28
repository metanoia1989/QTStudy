#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import sys

from PySide6.QtWidgets import QApplication, QLabel

app = QApplication(sys.argv)
# label = QLabel("Hello World")
# QLabel 也支持富文本内容显示
label = QLabel("<font color=red size=40>Hello World</font>")
label.show()
app.exec()
