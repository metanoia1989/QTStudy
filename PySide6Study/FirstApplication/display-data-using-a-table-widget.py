#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import sys
from PySide6.QtGui import QColor
from PySide6.QtWidgets import (
    QApplication, QTableWidget, QTableWidgetItem
)

colors = [
    ("Red", "#ff0000"),
    ("Green", "#00ff00"),
    ("Blue", "#0000ff"),
    ("Black", "#000000"),
    ("White", "#ffffff"),
    ("Electric Green", "#41cd52"),
    ("Dark Blue", "#222840"),
    ("Yellow", "#f9e56d"),
]

def get_rgb_from_hex(code):
    code_hex = code.replace('#', '')
    rgb = tuple(int(code_hex[i:i+2], 16) for i in (0, 2, 4))
    return QColor.fromRgb(rgb[0], rgb[1], rgb[2])

app = QApplication()

table = QTableWidget()
table.setRowCount(len(colors))
table.setColumnCount(len(colors[0]) + 1)
table.setHorizontalHeaderLabels(["Name", "Hex Code", "Color"])

for i, (name, code) in enumerate(colors):
    item_name = QTableWidgetItem(name)
    item_code = QTableWidgetItem(code)
    item_color = QTableWidgetItem()
    item_color.setBackground(get_rgb_from_hex(code))
    table.setItem(i, 0, item_name)
    table.setItem(i, 1, item_code)
    table.setItem(i, 2, item_color)

table.show()
sys.exit(app.exec())