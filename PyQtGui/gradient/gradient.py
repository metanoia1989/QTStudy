#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import (QWidget, QPushButton, QApplication,
    QVBoxLayout, QHBoxLayout, QGridLayout, QMainWindow, QSizePolicy,
    QColorDialog)
from PyQt5.QtGui import QColor, QPainter, QLinearGradient, QPen
from PyQt5.QtCore import QSize, QRect
from PyQt5.QtCore import Qt, pyqtSignal as Signal

class Gradient(QWidget):
    gradientChanged = Signal()

    def __init__(self, gradient=None, parent=None):
        super(Gradient, self).__init__(parent)

        self.setSizePolicy(
            QSizePolicy.MinimumExpanding, 
            QSizePolicy.MinimumExpanding
        )

        if gradient:
            self._gradient = gradient
        else:
            self._gradient = [
                (0.0, "#000000"),
                (1.0, "#ffffff"),
            ]

        self._handle_w = 10
        self._handle_h = 10

        self._drag_position = None

    def paintEvent(self, e):
        painter = QPainter(self)
        width  = painter.device().width()
        height  = painter.device().height()

        gradient = QLinearGradient(0, 0, width, 0)
        for stop, color in self._gradient:
            gradient.setColorAt(stop, QColor(color))

        rect = QRect(0, 0, width, height)
        painter.fillRect(rect, gradient)

        pen = QPen()

        y = painter.device().height() / 2

        for stop, _ in self._gradient:
            pen.setColor(QColor("white"))
            painter.setPen(pen)
            painter.drawLine(stop * width, y - self._handle_h,
                stop * width, y + self._handle_h)

            pen.setColor(QColor("red"))
            painter.setPen(pen)

            rect = QRect(
                stop * width - self._handle_w / 2,
                y - self._handle_h / 2,
                self._handle_w,
                self._handle_h
            )

            painter.drawRect(rect)

        painter.end()

    def sizeHint(self):
        return QSize(200, 50)

    def _sort_gradient(self):
        self._gradient = sorted(self._gradient, key = lambda g: g[0])

    def _constrain_gradient(self):
        self._gradient = [
            (max(0.0, min(1.0, stop)), color)
            for stop, color in self._gradient
        ]

    def setGradient(self, gradient):
        assert all([0.0 <= stop <= 1.0 for stop, _ in gradient])
        self._gradient = gradient
        self._constrain_gradient()
        self._sort_gradient()
        self.gradientChanged.emit()

    def gradient(self):
        return self._gradient

    @property
    def _end_stops(self):
        return [0, len(self._gradient) - 1]

    def addStop(self, stop, color=None):
        assert 0.0 <= stop <= 1.0

        for n, g in enumerate(self._gradient):
            if g[0] > stop:
                self._gradient.insert(n, (stop, color or g[1]))
                break
        self._constrain_gradient()
        self.gradientChanged.emit()
        self.update()

    def removeStopAtPosition(self, n):
        if n not in self._end_stops:
            del self._gradient[n]
            self.gradientChanged.emit()
            self.update()
            
    def setColorAtPosition(self, n, color):
        if n < len(self._gradient):
            stop, _ = self._gradient[n]
            self._gradient[n] = stop, color
            self.gradientChanged.emit()
            self.update()

    def chooseColorAtPosition(self, n, current_color=None):
        dlg = QColorDialog(self)
        if current_color:
            dlg.setCurrentColor(QColor(current_color))

        if dlg.exec_():
            self.setColorAtPosition(n, dlg.currentColor().name())

    def _find_stop_handle_for_event(self, e, to_exclude=None):
        width = self.width()
        height = self.height()
        midpoint = height / 2

        if (
            e.y() >= midpoint - self._handle_h and
            e.y() <= midpoint + self._handle_h
        ):
            for n, (stop, color) in enumerate(self._gradient):
                if to_exclude and n in to_exclude:
                    continue
                if (
                    e.x() >= stop * width - self._handle_w and
                    e.x() <= stop * width + self._handle_w
                ):
                    return n

    def mousePressEvent(self, e):
        if e.button() == Qt.RightButton:
            n = self._find_stop_handle_for_event(e)
            if n is not None:
                _, color = self._gradient[n]
                self.chooseColorAtPosition(n, color)

            elif e.button() == Qt.LeftButton:
                n = self._find_stop_handle_for_event(e, to_exclude=self._end_stops)
                if n is not None:
                    self._drag_position = n

    def mouseReleaseEvent(self, e):
        self._drag_position = None
        self._sort_gradient()

    def mouseMoveEvent(self, e):
        if self._drag_position:
            stop = e.x() / self.width()
            _, color = self._gradient[self._drag_position]
            self._gradient[self._drag_position] = stop, color
            self._constrain_gradient()
            self.update()

    def mouseDoubleClickEvent(self, e):
        n = self._find_stop_handle_for_event(e)
        if n:
            self._sort_gradient()
            if n > 0 and n < len(self._gradient) - 1:
                self.removeStopAtPosition(n)

        else:
            stop = e.x() / self.width()
            self.addStop(stop)


if __name__ == "__main__":
    class Window(QMainWindow):
        def __init__(self, parent=None):
            super(Window, self).__init__(parent)

            gradient = Gradient()
            gradient.setGradient([(0, "black"), (1, "green"), (0.5, "red")])
            self.setCentralWidget(gradient)

    app = QApplication(sys.argv)
    w = Window()
    w.show()
    app.exec_()