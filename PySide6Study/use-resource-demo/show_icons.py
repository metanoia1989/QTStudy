#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import sys
from PySide6.QtCore import Qt
from PySide6.QtGui import QPixmap
from PySide6.QtWidgets import QHBoxLayout, QLabel, QWidget, QVBoxLayout, QApplication
import icons_rc

class MyWidget(QWidget):
    def __init__(self):
        super().__init__()

        clickIcon = QPixmap(":/icons/click.png")
        monkeyIcon = QPixmap(":/icons/monkey.png")
        nextIcon = QPixmap(":/icons/next.png")
        playIcon = QPixmap(":/icons/play-button.png")
        
        self.layout = QHBoxLayout(self)

        for icon in [clickIcon, monkeyIcon, nextIcon, playIcon]:
            label = QLabel()
            label.setPixmap(icon.scaled(100, 100, Qt.KeepAspectRatio))
            self.layout.addWidget(label)
        


if __name__ == '__main__':
    app = QApplication()
    
    widget = MyWidget()
    widget.resize(800, 600)
    widget.show()
    
    sys.exit(app.exec())