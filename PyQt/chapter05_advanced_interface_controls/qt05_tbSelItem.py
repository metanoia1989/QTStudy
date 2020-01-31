#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
在表格中快速定位到指定行
'''

import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import QColor, QBrush
from PyQt5.QtCore import Qt

class Table(QWidget):
    def __init__(self, arg=None):
        super(Table, self).__init__(arg)
        self.initUI()

    def initUI(self):
        self.setWindowTitle("QTableView表格视图控件的例子")
        self.resize(600, 800)
        conLayout = QHBoxLayout()
        tableWidget = QTableWidget()
        tableWidget.setRowCount(30)
        tableWidget.setColumnCount(4)
        conLayout.addWidget(tableWidget)

        for i in range(30):
            for j in range(4):
                itemContent = '(%d, %d)' % (i, j)
                tableWidget.setItem(i, j, QTableWidgetItem(itemContent))
        self.setLayout(conLayout)

        # 遍历表查找对应的item
        text = "(23, 1)"
        items = tableWidget.findItems(text, Qt.MatchExactly)
        item = items[0]
        # 选中单元格
        item.setSelected(True)
        # 设置单元格的背景颜色为红色
        item.setBackground(QBrush(QColor(255, 0, 0)))
        row = item.row()
        # 滚轮定位过去，快速定位到第17行
        tableWidget.verticalScrollBar().setSliderPosition(row)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    table = Table()
    table.show()
    sys.exit(app.exec_())
