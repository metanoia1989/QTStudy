#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
右键菜单
'''

import sys
from PyQt5.QtWidgets import (
    QMenu, QPushButton, QWidget, QTableWidget, QHBoxLayout,
    QApplication, QTableWidgetItem, QHeaderView
)
from PyQt5.QtCore import QObject, Qt

class Table(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle("QTableWidget例子")
        self.resize(500, 300)
        conLayout = QHBoxLayout()
        self.tableWidget = QTableWidget()
        self.tableWidget.setRowCount(5)
        self.tableWidget.setColumnCount(3)
        conLayout.addWidget(self.tableWidget)

        self.tableWidget.setHorizontalHeaderLabels(["姓名", "性别", "体重(kg)"])
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        # 右键菜单设置
        self.tableWidget.setContextMenuPolicy(Qt.CustomContextMenu)
        self.tableWidget.customContextMenuRequested.connect(self.generateMenu) # 右键菜单事件

        newItem = QTableWidgetItem("张三")
        self.tableWidget.setItem(0, 0, newItem)

        newItem = QTableWidgetItem("男")
        self.tableWidget.setItem(0, 1, newItem)

        newItem = QTableWidgetItem("160")
        self.tableWidget.setItem(0, 2, newItem)

        newItem = QTableWidgetItem("李四")
        self.tableWidget.setItem(1, 0, newItem)

        newItem = QTableWidgetItem("女")
        self.tableWidget.setItem(1, 1, newItem)

        newItem = QTableWidgetItem("170")
        self.tableWidget.setItem(1, 2, newItem)

        self.setLayout(conLayout)

    def generateMenu(self, pos):
        row_num = 1
        for i in self.tableWidget.selectionModel().selection().indexes():
            row_num = i.row()

        # 表格只有两行数据，只在前两行支持右键弹出菜单
        if row_num < 2:
            menu = QMenu()
            item1 = menu.addAction(u"选项一")
            item2 = menu.addAction(u"选项二")
            item3 = menu.addAction(u"选项三")
            action = menu.exec_(self.tableWidget.mapToGlobal(pos))
            text0 = self.tableWidget.item(row_num, 0).text()
            text1 = self.tableWidget.item(row_num, 1).text()
            text2 = self.tableWidget.item(row_num, 2).text()
            if action == item1:
                print("您选了选项一，当前行文字内容是：", text0, text1, text2)
            elif action == item2:
                print("您选了选项二，当前行文字内容是：", text0, text1, text2)
            elif action == item3:
                print("您选了选项三，当前行文字内容是：", text0, text1, text2)
            else:
              return


        
if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = Table()
    win.show()
    sys.exit(app.exec_())