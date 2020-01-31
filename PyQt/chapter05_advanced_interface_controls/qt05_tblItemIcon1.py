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
        self.resize(430, 230)
        conLayout = QHBoxLayout()
        tableWidget = QTableWidget()
        tableWidget.setRowCount(4)
        tableWidget.setColumnCount(4)
        conLayout.addWidget(tableWidget)

        tableWidget.setHorizontalHeaderLabels(["姓名", "性别", "体重(kg)", "显示图片"])
        tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)

        newItem = QTableWidgetItem("张三")
        tableWidget.setItem(0, 0, newItem)

        newItem = QTableWidgetItem("男")
        tableWidget.setItem(0, 1, newItem)

        newItem = QTableWidgetItem("160")
        tableWidget.setItem(0, 2, newItem)

        newItem = QTableWidgetItem(QIcon("./images/bao1.png"), "背包")
        tableWidget.setItem(0, 3, newItem)

        self.setLayout(conLayout)
        
if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = Table()
    win.show()
    sys.exit(app.exec_())