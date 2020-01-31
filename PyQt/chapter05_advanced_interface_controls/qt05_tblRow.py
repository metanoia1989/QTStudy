#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
设置单元格高度和宽度
'''

import sys
from PyQt5.QtWidgets import (QWidget, QTableWidget, QHBoxLayout, QApplication, QTableWidgetItem, QAbstractItemView)

class Table(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle("QTableWidget例子")
        self.resize(530, 230)
        conLayout = QHBoxLayout()
        tableWidget = QTableWidget()
        tableWidget.setRowCount(4)
        tableWidget.setColumnCount(3)
        conLayout.addWidget(tableWidget)

        tableWidget.setHorizontalHeaderLabels(["姓名", "性别", "体重(kg)"])
        # 将第一列的单元格，设置成150宽度，
        tableWidget.setColumnWidth(0, 150)
        # 将第一行的单元格，设置成120高度
        tableWidget.setRowHeight(0, 120)

        newItem = QTableWidgetItem("张三")
        tableWidget.setItem(0, 0, newItem)

        newItem = QTableWidgetItem("男")
        tableWidget.setItem(0, 1, newItem)

        newItem = QTableWidgetItem("160")
        tableWidget.setItem(0, 2, newItem)

        self.setLayout(conLayout)
        
if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = Table()
    win.show()
    sys.exit(app.exec_())