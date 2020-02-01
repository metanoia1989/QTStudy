#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import QApplication, QWidget
from PyQt5.QtGui import QPainter, QPixmap, QBitmap, QCursor
from PyQt5.QtCore import Qt, QTimer

class Winform(QWidget):
    def __init__(self, parent=None):
        super(Winform, self).__init__(parent)
        self.setWindowTitle("可拖动的不规则窗体动画效果")
        self.i = 1
        self.showPix()
        self.timer = QTimer()
        self.timer.setInterval(500)
        self.timer.timeout.connect(self.timeChange)
        self.timer.start()
        

    def showPix(self):
        self.update()
        if self.i == 5:
            self.i = 1
        self.mypic = {
            1: "./images/left.png",
            2: "./images/up.png",
            3: "./images/right.png",
            4: "./images/down.png",
        }
        self.pix = QPixmap(
            self.mypic[self.i], "0", 
            Qt.AvoidDither|Qt.ThresholdDither|
            Qt.ThresholdAlphaDither
        )
        self.resize(self.pix.size())
        self.setMask(self.pix.mask())
        self.dragPosition = None

    '''
    重定义鼠标按下事件和鼠标移动事件，使窗体能够响应鼠标随意移动
    '''
    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            self.m_drag = True
            self.m_DragPosition = event.globalPos() - self.pos()
            event.accept()
            self.setCursor(QCursor(Qt.OpenHandCursor))
        if event.button() == Qt.RightButton:
            self.close()
        
    def mouseMoveEvent(self, event):
        if Qt.LeftButton and self.m_drag:
            # 当左键移动窗体修改偏移值
            self.move(event.globalPos() - self.m_DragPosition)
            event.accept()

    def mouseReleaseEvent(self, event):
        self.m_drag = False
        self.setCursor(QCursor(Qt.ArrowCursor))

    '''
    一般 paintEvent 在窗体首次绘制加载，要重新加载 paintEvent 
    使用 self.update() or self.repaint()
    '''
    def paintEvent(self, event):
        painter = QPainter(self)
        # 指定区域直接绘制窗口背景
        painter.drawPixmap(0, 0, self.pix.width(), self.pix.height(), self.pix)

    '''鼠标双击事件'''
    def mouseDoubleClickEvent(self, event):
        if event.button() == 1:
            self.i += 1
            self.showPix()

    '''每500毫秒修改paint'''
    def timeChange(self):
        self.i += 1
        self.showPix()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = Winform()
    win.show()
    sys.exit(app.exec_())
    
