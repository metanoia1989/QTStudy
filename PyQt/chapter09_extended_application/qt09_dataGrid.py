#!/usr/bin/env python3
# -*- coding: utf-8 -*-
'''
分页控件
'''

import re
import sys
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import (
    QWidget, QHBoxLayout, QVBoxLayout, QApplication, 
    QPushButton, QLineEdit, QLabel, QSplitter,
    QTableView, QHeaderView, QMessageBox
)
from PyQt5.QtSql import QSqlDatabase, QSqlQueryModel, QSqlQuery

class DataGrid(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("分页查询例子")
        self.resize(750, 300)

        self.queryModel = None # 查询模型
        self.tableView = None # 数据表
        self.totalPageLabel = None # 总数页文本
        self.currentPageLabel = None # 当前页文本
        self.switchPageLineEdit = None # 转到页输入框
        self.prevButton = None # 前一页按钮
        self.nextButton = None # 后一页按钮
        self.switchPageButton = None # 转到页按钮
        self.currentPage = 0 # 当前页
        self.totalPage = 0 # 总页数
        self.totalRecordCount = 0 # 总记录数
        self.PageRecordCount = 5 # 每页显示记录数
        self.totalRecordLabel = None

        self.db = None
        self.initUI()

    def initUI(self):
        # 创建窗口
        self.createWindow()
        # 设置表格
        self.setTableView()

        # 信号槽连接
        self.prevButton.clicked.connect(self.onPrevButtonClick)
        self.nextButton.clicked.connect(self.onNextButtonClick)
        self.switchPageButton.clicked.connect(self.onSwitchPageButtonClick)

    def closeEvent(self, event):
        '''关闭窗口时，关闭数据库连接'''
        self.db.close()

    '''创建窗口'''
    def createWindow(self):
        # 操作布局
        operatorLayout = QHBoxLayout()
        self.prevButton = QPushButton("前一页")
        self.nextButton = QPushButton("后一页")
        self.switchPageButton = QPushButton("Go")
        self.switchPageLineEdit = QLineEdit()
        self.switchPageLineEdit.setFixedWidth(40) 

        switchPage = QLabel("转到第")
        page = QLabel("页")
        operatorLayout.addWidget(self.prevButton)
        operatorLayout.addWidget(self.nextButton)
        operatorLayout.addWidget(switchPage)
        operatorLayout.addWidget(self.switchPageLineEdit)
        operatorLayout.addWidget(page)
        operatorLayout.addWidget(self.switchPageButton)
        operatorLayout.addWidget(QSplitter())

        # 状态布局
        statusLayout = QHBoxLayout()
        self.totalPageLabel = QLabel()
        self.totalPageLabel.setFixedWidth(70)
        self.currentPageLabel = QLabel()
        self.currentPageLabel.setFixedWidth(70)

        self.totalRecordLabel = QLabel()
        self.totalRecordLabel.setFixedWidth(70)

        statusLayout.addWidget(self.totalPageLabel)
        statusLayout.addWidget(self.currentPageLabel)
        statusLayout.addWidget(QSplitter())
        statusLayout.addWidget(self.totalRecordLabel)

        # 设置表格属性
        self.tableView = QTableView()
        # 表格宽度的自适应调整
        self.tableView.horizontalHeader().setStretchLastSection(True)
        self.tableView.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)

        # 创建界面
        mainLayout = QVBoxLayout(self)
        mainLayout.addLayout(operatorLayout)
        mainLayout.addWidget(self.tableView)
        mainLayout.addLayout(statusLayout)
        self.setLayout(mainLayout)

    '''设置表格'''
    def setTableView(self):
        print("*** step2 SetTableView ***")
        self.db = QSqlDatabase.addDatabase("QSQLITE")
        self.db.setDatabaseName("./db/database.db")
        self.db.open()
        # 声明查询模型，可读可写，同步数据库
        self.queryModel = QSqlQueryModel(self)
        # 设置当前页
        self.currentPage = 1
        # 得到总记录数
        self.totalRecordCount = self.getTotalRecordCount()
        # 得到总页数
        self.totalPage = self.getPageCount()
        # 刷新状态
        self.updateStatus()
        # 设置总页数文本
        self.setTotalPageLabel()
        # 设置总记录数
        self.setTotalRecordLabel()
        # 记录查询
        self.recordQuery(0)
        # 设置模型
        self.tableView.setModel(self.queryModel)

        print("totalRecordCount=" + str(self.totalRecordCount))
        print('totalPage=' + str(self.totalPage))

        # 设置表格表头
        self.queryModel.setHeaderData(0, Qt.Horizontal, "编号")
        self.queryModel.setHeaderData(1, Qt.Horizontal, "姓名")
        self.queryModel.setHeaderData(2, Qt.Horizontal, "性别")
        self.queryModel.setHeaderData(3, Qt.Horizontal, "年龄")
        self.queryModel.setHeaderData(4, Qt.Horizontal, "院系")

    '''得到记录数'''
    def getTotalRecordCount(self):
        self.queryModel.setQuery("select * from student")
        rowCount = self.queryModel.rowCount()
        print("rowCount=" + str(rowCount))
        return rowCount

    '''得到页数'''
    def getPageCount(self):
        if self.totalRecordCount % self.PageRecordCount == 0:
            return (self.totalRecordCount / self.PageRecordCount)
        else:
            return (self.totalRecordCount / self.PageRecordCount + 1)

    '''记录查询'''
    def recordQuery(self, limitIndex):
        szQuery = ("select * from student limit %d, %d" % (limitIndex, self.PageRecordCount))
        print("query sql=" + szQuery)
        self.queryModel.setQuery(szQuery)

    '''刷新状态'''
    def updateStatus(self):
        szCurrentText = ("当前第%d页" % self.currentPage)
        self.currentPageLabel.setText(szCurrentText)

        print("当前页：%d, 总页数：%d" % (self.currentPage, self.totalPage))
        print("self.currentPage >= self.totalPage: " + repr(self.currentPage >= self.totalPage))

        # 设置按钮是否可用
        if self.currentPage <= 1:
            self.prevButton.setEnabled(False)
            self.nextButton.setEnabled(True)
        elif self.currentPage >= self.totalPage :
            self.prevButton.setEnabled(True)
            self.nextButton.setEnabled(False)
        else:
            self.prevButton.setEnabled(True)
            self.nextButton.setEnabled(True)

    '''设置总页数文本'''
    def setTotalPageLabel(self):
        szPageCountText = ("总共%d页" % self.totalPage)        
        self.totalPageLabel.setText(szPageCountText)

    '''设置总记录数'''
    def setTotalRecordLabel(self):
        szTotalRecordText = ("共%d条" % self.totalRecordCount)
        print("*** setTotalRecordLabel szTotalRecordText=" + szTotalRecordText)
        self.totalRecordLabel.setText(szTotalRecordText)

    '''前一页按钮被按下'''
    def onPrevButtonClick(self):
        print("*** onPrevButtonClick")
        limitIndex = (self.currentPage - 2) * self.PageRecordCount
        self.recordQuery(limitIndex)
        self.currentPage -= 1
        self.updateStatus()

    '''后一页按钮按下'''
    def onNextButtonClick(self):
        print("*** onNextButtonClick ")
        limitIndex = self.currentPage * self.PageRecordCount
        self.recordQuery(limitIndex)
        self.currentPage += 1
        self.updateStatus()

    '''转到页按钮按下'''
    def onSwitchPageButtonClick(self):
        # 得到输入字符串
        szText = self.switchPageLineEdit.text()
        # 数字正则表达式
        pattern = re.compile(r"^[-+]?[0-9]+$")
        match = pattern.match(szText)

        # 判断是否为数字
        if not match:
            QMessageBox.information(self, "提示", "请输入数字")
            return

        # 是否为空
        if szText == "":
            QMessageBox.information(self, "提示", "请输入跳转页面")
            return

        # 得到页数
        pageIndex = int(szText)
        # 判断是否有指定页
        if pageIndex > self.totalPage or pageIndex < 1:
            QMessageBox.information(self, "提示", "没有指定的页面，请重新输入。")
            return

        # 得到查询起始行号
        limitIndex = (pageIndex - 1) * self.PageRecordCount

        # 记录查询
        self.recordQuery(limitIndex)
        # 设置当前页
        self.currentPage = pageIndex
        # 刷新状态
        self.updateStatus()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = DataGrid()
    win.show()
    sys.exit(app.exec_())

        
