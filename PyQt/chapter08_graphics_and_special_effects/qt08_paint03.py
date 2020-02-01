#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import QApplication, QWidget
from PyQt5.QtGui import QPainter, QPixmap, QBitmap, QCursor
from PyQt5.QtCore import Qt

class Winform(QWidget):
    def __init__(self, parent=None):
        super(Winform, self).__init__(parent)
        self.setWindowTitle("可拖动的不规则窗体")
        self.showPix()

    def showPix(self):
        self.pix = QBitmap("./images/mask.png")
        self.resize(self.pix.size())
        self.setMask(self.pix)
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
        painter.drawPixmap(0, 0, self.pix.width(), self.pix.height(), 
            QPixmap(r"./images/boy.png"))

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = Winform()
    win.show()
    sys.exit(app.exec_())
    
