#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import (QWidget, QPushButton, QApplication,
    QVBoxLayout, QHBoxLayout, QGridLayout, QMainWindow)
from PyQt5.QtGui import QColor
from PyQt5.QtCore import QSize
from PyQt5.QtCore import Qt, pyqtSignal as Signal

PALETTES = {
    # bokeh paired 12
    'paired12':['#000000', '#a6cee3', '#1f78b4', '#b2df8a', '#33a02c', '#fb9a99', '#e31a1c', '#fdbf6f', '#ff7f00', '#cab2d6', '#6a3d9a', '#ffff99', '#b15928', '#ffffff'],
    # d3 category 10
    'category10':['#000000', '#1f77b4', '#ff7f0e', '#2ca02c', '#d62728', '#9467bd', '#8c564b', '#e377c2', '#7f7f7f', '#bcbd22', '#17becf', '#ffffff'],
    # 17 undertones https://lospec.com/palette-list/17undertones
    '17undertones': ['#000000', '#141923', '#414168', '#3a7fa7', '#35e3e3', '#8fd970', '#5ebb49', '#458352','#dcd37b', '#fffee5', '#ffd035', '#cc9245', '#a15c3e', '#a42f3b', '#f45b7a', '#c24998', '#81588d', '#bcb0c2', '#ffffff']
}

class _PaletteButton(QPushButton):
    def __init__(self, color, parent=None):
        super(_PaletteButton, self).__init__(parent)
        self.setFixedSize(QSize(24, 24))
        self.color = color
        self.setStyleSheet("background-color: %s;" % color)

class _PaletteBase(QWidget):
    selected = Signal(object)

    def _emit_color(self, color):
        self.selected.emit(color)

class _PaletteLinearBase(_PaletteBase):
    def __init__(self, colors, parent=None):
        super(_PaletteLinearBase, self).__init__(parent)

        if isinstance(colors, str):
            if colors in PALETTES:
                colors = PALETTES[colors]
        
        palette = self.layoutvh()

        for c in colors:
            b = _PaletteButton(c)
            b.pressed.connect(
                lambda : self._emit_color(c)
            )
            palette.addWidget(b)
        
        self.setLayout(palette)

class PaletteHorizontal(_PaletteLinearBase):
    layoutvh = QHBoxLayout

class PaletteVertical(_PaletteLinearBase):
    layoutvh = QVBoxLayout


class PaletteGrid(_PaletteBase):
    def __init__(self, colors, n_columns=5, parent=None):
        super(PaletteGrid, self).__init__(parent)

        if isinstance(colors, str):
            if colors in PALETTES:
                colors = PALETTES[colors]

        palette = QGridLayout()
        row, col = 0, 0

        for c in colors:
            b = _PaletteButton(c)
            b.pressed.connect(lambda : self._emit_color(c))
            palette.addWidget(b, row, col)
            col += 1
            if col == n_columns:
                col = 0
                row += 1
            
        self.setLayout(palette)

if __name__ == "__main__":
    class Window(QMainWindow):
        def __init__(self, parent=None):
            super(Window, self).__init__(parent)

            palette = PaletteGrid("17undertones")
            self.setCentralWidget(palette)

        def show_selected_color(self, c):
            print("Selected: {}".format(c))

    
    app = QApplication(sys.argv)
    w = Window()
    w.show()
    app.exec_()