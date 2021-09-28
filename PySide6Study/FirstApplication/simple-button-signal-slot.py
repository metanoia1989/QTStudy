#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import sys
from PySide6.QtCore import Slot
from PySide6.QtWidgets import QApplication, QPushButton


@Slot()
def say_hello():
    print("Button clicked, Hello!")
    
app = QApplication([])
button = QPushButton("Click me")
button.clicked.connect(say_hello)
button.show()
app.exec()