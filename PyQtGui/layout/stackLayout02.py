#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from PyQt5.QtWidgets import QMainWindow, QStackedLayout, QWidget,   \
    QApplication, QVBoxLayout, QHBoxLayout, QPushButton

from layout_colorwidget import Color
import sys

class MainWindow(QMainWindow):
    def __init__(self, *args, **kwargs):
        super(MainWindow, self).__init__(*args, **kwargs)
        self.setWindowTitle("My Awesome App")

        pageLayout = QVBoxLayout()
        button_layout = QHBoxLayout()
        layout = QStackedLayout()

        pageLayout.addLayout(button_layout)
        pageLayout.addLayout(layout)

        for n, color in enumerate(['red', 'green', 'blue', 'yellow']):
            btn = QPushButton(str(color))
            btn.pressed.connect(lambda n = n: layout.setCurrentIndex(n))
            button_layout.addWidget(btn)
            layout.addWidget(Color(color))


        widget = QWidget()
        widget.setLayout(pageLayout)
        self.setCentralWidget(widget)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MainWindow()
    win.show()
    app.exec()