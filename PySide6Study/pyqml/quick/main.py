#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import sys
from pathlib import Path
from PySide6.QtGui import QGuiApplication
from PySide6.QtQml import QQmlApplicationEngine
from PySide6.QtQuickControls2 import QQuickStyle
from bridge import Bridge

import style_rc


if __name__ == "__main__":
    app = QGuiApplication(sys.argv)
    QQuickStyle.setStyle("Material")
    engine = QQmlApplicationEngine()
    
    qml_file = Path(__file__).parent / 'view.qml'
    engine.load(str(qml_file))
    
    if not engine.rootObjects():
        sys.exit(-1)

    sys.exit(app.exec())
        
