#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
这个程序有问题，虽然能显示在托盘上，但是右键无法唤出菜单，点击没有效果
应该是没有设置的问题，但是托盘程序我也不熟悉，可能要看一下文档怎么处理。
QMenu.addAction 不能接收一个QAction参数
'''

from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import QObject

import os, sys

def getIcon(name):
    curpath = os.path.dirname(__file__)
    iconsPath = os.path.join(curpath, "images")
    return QIcon(os.path.join(iconsPath, name + ".png"))


class ColorPicker(QObject):
    def __init__(self, *args, **kwargs):
        super(ColorPicker, self).__init__(*args, **kwargs)

        self.clipboard = QApplication.clipboard()
        self.dialog = QColorDialog()

        # 创建菜单
        menu = QMenu()
        action_hex = menu.addAction("HEX")
        action_hex.triggered.connect(self.copy_color_hex)
        menu.addAction(action_hex)

        action_rgb = menu.addAction("RGB")
        action_rgb.triggered.connect(self.copy_color_rgb)

        action_hsv = menu.addAction("HSV")
        action_hsv.triggered.connect(self.copy_color_hsv)

        action_exit = menu.addAction("Exit")
        action_exit.triggered.connect(QApplication.exit)
        menu.addAction(action_exit)

        # 创建托盘图标，并添加菜单
        self.tray = QSystemTrayIcon()
        self.tray.setIcon(QIcon(getIcon("color")))
        self.tray.setContextMenu(menu)
        self.tray.setToolTip("这是颜色采集器")
        self.tray.show()

        self.tray.activated.connect(self.trayClicked)

    def trayClicked(self, reason):
        if (reason == QSystemTrayIcon.Trigger):
            if (self.tray.supportsMessages()):
                self.tray.showMessage("温馨提示", "这个是托盘消息")

    def copy_color_hex(self):
        if self.dialog.exec_():
            color = self.dialog.currentColor()
            self.clipboard.setText(color.name())

    def copy_color_rgb(self):
        if self.dialog.exec_():
            color = self.dialog.currentColor()
            self.clipboard.setText("rgb(%d, %d, %d)" % (
                color.red(), color.green(), color.blue()
            ))

    def copy_color_hsv(self):
        if self.dialog.exec_():
            color = self.dialog.currentColor()
            self.clipboard.setText("hsv(%d, %d, %d)" % (
                color.hue(), color.saturation(), color.value()
            ))

if __name__ == "__main__":
    app = QApplication(sys.argv)
    app.setQuitOnLastWindowClosed(False)
    picker = ColorPicker()
    app.exec_()