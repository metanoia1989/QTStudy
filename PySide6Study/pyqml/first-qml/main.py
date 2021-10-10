#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import sys
from PySide6.QtWidgets import QApplication
from PySide6.QtQuick import QQuickView
from os.path import dirname

if __name__ == "__main__":
    app = QApplication()
    view = QQuickView()

    view.setSource(dirname(__file__) + '/view.qml')
    view.show()
    sys.exit(app.exec())