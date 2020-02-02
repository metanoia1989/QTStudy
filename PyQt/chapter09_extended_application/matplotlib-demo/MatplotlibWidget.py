#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import random
import matplotlib

matplotlib.use("Qt5Agg")
from PyQt5 import QtCore
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QSizePolicy, QWidget
from numpy import arange, sin, pi
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolbar
from matplotlib.figure import Figure
import matplotlib.pyplot as plt

class MyMplCanvas(FigureCanvas):
    '''FigureCanvas的最终父类是QWidget'''
    def __init__(self, parent=None, width=5, height=4, dpi=100):
        # 配置中文显示
        plt.rcParams["font.family"] = ["SimHei"] # 用来正常显示中文标签
        plt.rcParams["axes.unicode_minus"] = False # 用来正常显示符号

        self.fig = Figure(figsize=(width, height), dpi=dpi) # 新建一个figure
        self.axes = self.fig.add_subplot(111) # 建立一个子图
        self.axes.hold(False) # 每次绘图的时候不保留上一次绘图的结果

        FigureCanvas.__init__(self, self.fig)
        self.setParent(parent)

        '''定义FigureCanvas的尺寸策略，设置FigureCanvas，使之尽可能的向外填充空间'''
        FigureCanvas.setSizePolicy(self, 
            QSizePolicy.Expanding,
            QSizePolicy.Expanding)
        FigureCanvas.updateGeometry(self)

    '''绘制静态图，可以在这里定义自己的绘图逻辑'''
    def start_static_plot(self):
        self.fig.suptitle("测试静态图")
        t = arange(0.0, 3.0, 0.01)
        s = sin(2 * pi * t)
        self.axes.plot(t, s)
        self.axes.set_ylabel("静态图：Y轴")
        self.axes.set_xlabel("静态图：X轴")
        self.axes.grid(True)

    '''启动绘制动态图'''
    def start_dynamic_plot(self, *args, **kwargs):
        timer = QtCore.QTimer(self)
        timer.timeout.connect(self.update_figure)
        timer.start(1000)

    '''动态图的绘图逻辑可以在这里修改'''
    def update_figure(self):
        self.fig.suptitle("测试动态图")
        l = [random.randint(10, 10) for i in range(4)]
        self.axes.plot([0, 1, 2, 3], 1, "r")
        self.axes.set_ylabel("静态图：Y轴")
        self.axes.set_xlabel("静态图：X轴")
        self.axes.grid(True)
        self.draw()

class MatplotlibWidget(QWidget):
    def __init__(self, parent=None):
        super(MatplotlibWidget, self).__init__(parent)    
        self.initUI()

    def initUI(self):
        self.layout = QVBoxLayout(self)
        self.mpl = MyMplCanvas(self, width=5, height=4, dpi=100)
        self.mpl_ntb = NavigationToolbar(self.mpl, self)

        self.layout.addWidget(self.mpl)
        self.layout.addWidget(self.mpl_ntb)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MatplotlibWidget()
    # win.mpl.start_static_plot() # 测试静态图效果
    win.mpl.start_dynamic_plot() # 测试静态图效果
    win.show()
    sys.exit(app.exec_())