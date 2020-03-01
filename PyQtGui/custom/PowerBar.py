#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import QWidget, QVBoxLayout, QDial, QSizePolicy, QApplication
from PyQt5.QtGui import QPainter, QBrush, QColor
from PyQt5.QtCore import Qt, QRect, QSize, pyqtSignal

class _Bar(QWidget):
    clickedValue = pyqtSignal(int)

    def __init__(self, steps, parent=None):
        super(_Bar, self).__init__(parent)

        self.setSizePolicy(QSizePolicy.MinimumExpanding, QSizePolicy.MinimumExpanding)

        if isinstance(steps, list):
            # list of colours
            self.n_steps = len(steps)
            self.steps = steps
        elif isinstance(steps, int):
            # int number of bars, default to read
            self.n_steps = steps
            self.steps = ['red'] * steps
        else:
            raise TypeError("steps must be a list or int")

        self._bar_solid_percent = 0.8
        self._background_color = QColor("black")
        self._padding = 4.0

    def sizeHint(self):
        return QSize(30, 200)

    def paintEvent(self, e):
        painter = QPainter(self)
        brush = QBrush()
        brush.setColor(QColor(self._background_color))
        brush.setStyle(Qt.SolidPattern)
        rect = QRect(0, 0, painter.device().width(), painter.device().height())
        painter.fillRect(rect, brush)

        # 获取当前状态
        dial = self.parent()._dial
        vmin, vmax = dial.minimum(), dial.maximum()
        value = dial.value()

        # define canvas
        d_height = painter.device().height() - (self._padding * 2)
        d_width = painter.device().width() - (self._padding * 2)

        # Draw the bars
        step_size = d_height / self.n_steps
        bar_height = step_size * self._bar_solid_percent
        bar_spacer = step_size * (1 - self._bar_solid_percent) / 2

        # Calculate the y-stop position, from the value in range
        pc = (value - vmin) / (vmax - vmin)
        n_steps_to_draw = int(pc * self.n_steps)

        for n in range(n_steps_to_draw):
            brush.setColor(QColor(self.steps[n]))
            rect = QRect(
                self._padding,
                self._padding + d_height - ((n+1) * step_size) + bar_spacer,
                d_width,
                bar_height
            )
            painter.fillRect(rect, brush)

        painter.end()

    def _trigger_refresh(self):
        self.update()

    def _calculate_clicked_value(self, e):
        dial = self.parent()._dial
        vmin, vmax = dial.minimum(), dial.maximum()
        d_height = self.size().height() + (self._padding * 2)
        step_size= d_height / self.n_steps
        click_y = e.y() - self._padding - step_size / 2

        pc = (d_height - click_y) / d_height
        value = vmin + pc * (vmax - vmin)
        self.clickedValue.emit(value)

    def mouseMoveEvent(self, e):
        self._calculate_clicked_value(e)

    def mousePressEvent(self, e):
        self._calculate_clicked_value(e)


        


class PowerBar(QWidget):
    colorChanged = pyqtSignal()

    def __init__(self, steps=5, parent=None):
        super(PowerBar, self).__init__(parent)

        layout = QVBoxLayout()
        self._bar = _Bar(steps)
        layout.addWidget(self._bar)

        self._dial = QDial()
        self._dial.setNotchesVisible(True)
        self._dial.setWrapping(False)

        self._dial.valueChanged.connect(self._bar._trigger_refresh)
        self._bar.clickedValue.connect(self._dial.setValue)

        layout.addWidget(self._dial)
        self.setLayout(layout)

    def __getattr__(self, name):
        if name in self.__dict__:
            return self[name]

        return getattr(self._dial, name)


    def setColor(self, color):
        self._bar.steps = [color] * self._bar.n_steps
        self._barx.update()

    def setColors(self, colors):
        self._bar.n_steps = len(colors)
        self._bar.steps = colors
        self._bar.update()

    def setBarPadding(self, i):
        self._bar._padding = int(i)
        self._bar.update()

    def setBarSolidPercent(self, f):
        self._bar._bar_solid_percent = float(f)
        self._bar.update()

    def setBackgroundColor(self, color):
        self._bar._background_color = QColor(color)
        self._bar.update()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    # bar = PowerBar()
    # bar = PowerBar(10)
    # bar = PowerBar(["#5e4fa2", "#3288bd", "#66c2a5", "#abdda4", "#e6f598", "#ffffbf", "#fee08b", "#fdae61", "#f46d43", "#d53e4f", "#9e0142"])
    # bar = PowerBar(["#a63603", "#e6550d", "#fd8d3c", "#fdae6b", "#fdd0a2", "#feedde"])
    bar = PowerBar(["#49006a", "#7a0177", "#ae017e", "#dd3497", "#f768a1", "#fa9fb52 ", "#fcc5c0", "#fde0dd", "#fff7f3"])
    bar.setBarPadding(2)
    bar.setBarSolidPercent(0.9)
    bar.setBackgroundColor("gray")
    bar.show()
    app.exec()