#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
双缓冲绘图
'''

import sys
from PyQt5.QtWidgets import QApplication, QWidget
from PyQt5.QtGui import QPainter, QPixmap
from PyQt5.QtCore import Qt, QPoint

class Winform(QWidget):
    def __init__(self, parent=None):
        super(Winform, self).__init__(parent)
        self.setWindowTitle("双缓冲绘图")
        self.pix = QPixmap()
        self.lastPoint = QPoint()
        self.endPoint = QPoint()
        # 辅助画布
        self.tempPix = QPixmap()
        # 标志是否正在绘图
        self.isDrawing = False

        self.initUI()


    def initUI(self):
        self.resize(600, 500)
        self.pix = QPixmap(400, 400)
        self.pix.fill(Qt.white)

    def paintEvent(self, event):
        painter = QPainter(self)
        x = self.lastPoint.x()
        y = self.lastPoint.y()
        w = self.endPoint.x() - x
        h = self.endPoint.y() - y

        # 如果正在绘图，就在辅助画布上绘制
        if self.isDrawing:
            # 将以前pix中的内容复制到tempPix中，保证以前的内容不消失
            self.tempPix = self.pix
            pp = QPainter(self.pix)
            pp.drawRect(x, y, w, h)
            painter.drawPixmap(0, 0, self.pix)
        else:
            pp = QPainter(self.pix)
            pp.drawRect(x, y, w, h)
            painter.drawPixmap(0, 0, self.pix)

    def mousePressEvent(self, event):
        # 鼠标左键按下
        if event.button() == Qt.LeftButton:
            self.lastPoint = event.pos()
            self.endPoint = self.lastPoint
            self.isDrawing = True

    # def mouseMoveEvent(self, event):
    #     # 鼠标左键按下的同时移动鼠标
    #     if event.buttons() and Qt.LeftButton:
    #         self.endPoint = event.pos()
    #         # 进行重新绘制
    #         self.update()

    def mouseReleaseEvent(self, event):
        # 鼠标左键释放
        if event.button() == Qt.LeftButton:
            self.endPoint = event.pos()
            # 进行重新绘制
            self.update()
            self.isDrawing = False

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = Winform()
    win.show()
    sys.exit(app.exec_())
