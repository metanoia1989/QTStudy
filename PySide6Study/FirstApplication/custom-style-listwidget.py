#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import sys
from os.path import dirname
from PySide6.QtCore import Qt
from PySide6.QtWidgets import QApplication, QHBoxLayout, QLabel, QListWidget, QListWidgetItem, QPushButton, QVBoxLayout, QWidget

_placeholder = """
And what is the middle way realized by the Tathagata that — producing vision, 
producing knowledge — leads to calm, to direct knowledge, to self-awakening, to Unbinding? 
Precisely this Noble Eightfold Path: right view, right resolve, right speech, 
right action, right livelihood, right effort, right mindfulness, right concentration. 
This is the middle way realized by the Tathagata that — producing vision, 
producing knowledge — leads to calm, to direct knowledge, to self-awakening, to Unbinding.
"""

class Widget(QWidget):
    def __init__(self, parent=None):
        super(Widget, self).__init__(parent)
        
        menu_widget = QListWidget()
        for i in range(10):
            item = QListWidgetItem(f"Item {i}")
            item.setTextAlignment(Qt.AlignCenter)
            menu_widget.addItem(item)
            
        text_widget = QLabel(_placeholder)
        button = QPushButton("Something")
        
        content_layout = QVBoxLayout()
        content_layout.addWidget(text_widget)
        content_layout.addWidget(button)
        main_widget = QWidget()
        main_widget.setLayout(content_layout)
        
        layout = QHBoxLayout()
        layout.addWidget(menu_widget, 1)
        layout.addWidget(main_widget, 4)
        self.setLayout(layout)

if __name__ == "__main__":
    app = QApplication()
    
    w = Widget()
    w.show()
     
    with open(dirname(__file__) + "/style.qss", "r") as f:
        _style = f.read()
        app.setStyleSheet(_style)

    sys.exit(app.exec())
