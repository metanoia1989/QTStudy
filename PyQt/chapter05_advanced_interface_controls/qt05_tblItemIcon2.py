#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class Table(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle("QTableWidget例子")
        self.resize(1000, 900)
        conLayout = QHBoxLayout()
        tableWidget = QTableWidget()
        tableWidget.setColumnCount(3)
        tableWidget.setRowCount(5)
        conLayout.addWidget(tableWidget)

        tableWidget.setHorizontalHeaderLabels(["姓名", "性别", "体重(kg)", "显示图片"])
        tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        tableWidget.setEditTriggers(QAbstractItemView.NoEditTriggers)
        tableWidget.setIconSize(QSize(300, 200))

        # 让列宽和图片相同
        for i in range(3):
            tableWidget.setColumnWidth(i, 300)
        # 让行高和图片相同
        for i in range(5):
            tableWidget.setRowHeight(i, 200)
        
        for k in range(15):
            i = k / 3
            j = k % 3
            item = QTableWidgetItem()
            item.setFlags(Qt.ItemIsEnabled)   # 用户点击表格时，图片被选中
            icon = QIcon(r"./images/bao%d.png" % k)
            item.setIcon(QIcon(icon))
            print("e/icons/%d.png i=%d j=%d" % (k, i, j))
            tableWidget.setItem(i, j, item)

        self.setLayout(conLayout)

        
if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = Table()
    win.show()
    sys.exit(app.exec_())