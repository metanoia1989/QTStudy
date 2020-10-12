#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import json
from PyQt5.QtWidgets import (
    QApplication, QWidget, 
    QMessageBox, QTableWidget,
    QTableWidgetItem, QHeaderView,
    QAbstractScrollArea,
    QLineEdit, QPushButton,
    QHBoxLayout, QVBoxLayout,
    QAbstractItemView, QMessageBox
)
from PyQt5.QtGui import QIcon, QFont, QBrush, QColor
from PyQt5.QtCore import QUrl, QByteArray, QThread, pyqtSignal, Qt
from PyQt5.QtNetwork import QNetworkRequest, QNetworkAccessManager, QNetworkReply
from resource import *

class StudentQuery(QWidget):

    def __init__(self, parent=None):
        super().__init__(parent)
        self.initUI()
        self.prev_mobile = ""

    def initUI(self):
        self.setWindowTitle("学员手机号查询")
        self.setWindowFlags(QtCore.Qt.WindowMinimizeButtonHint |   # 使能最小化按钮
                            QtCore.Qt.WindowCloseButtonHint |      # 使能关闭按钮
                            QtCore.Qt.WindowStaysOnTopHint)        # 窗体总在最前端

        self.resize(300, 100)
        self.center()

        vbox = QVBoxLayout()
        hbox = QHBoxLayout()
        self.textInput = QLineEdit()
        self.queryBtn =  QPushButton(icon=QIcon(":/assets/icons/search.png"))
        hbox.addWidget(self.textInput)
        hbox.addWidget(self.queryBtn)
        
        self.table = QTableWidget()
        self.table.setColumnCount(4)
        self.table.setHorizontalHeaderLabels(["姓名", "手机号", "班次", "注册时间"])
        font = QFont('微软雅黑', 12)
        font.setBold(True)
        self.table.horizontalHeader().setFont(font)
        # self.table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.table.setEditTriggers(QAbstractItemView.NoEditTriggers) # 禁止编辑
        self.table.setSelectionBehavior(QAbstractItemView.SelectRows) # 整行选择
        # 将行和列的大小设为与内容相匹配
        self.table.resizeColumnsToContents() 
        self.table.resizeRowsToContents()
        # self.table.
        
        vbox.addLayout(hbox)
        vbox.addWidget(self.table)
        self.setLayout(vbox)
        
        self.queryBtn.clicked.connect(self.queryStudent)
        
    def center(self):
        """
        窗口居中显示
        """ 
        frameGm = self.frameGeometry()
        screen = QApplication.desktop().screenNumber(QApplication.desktop().cursor().pos())
        centerPoint = QApplication.desktop().screenGeometry(screen).center()
        frameGm.moveCenter(centerPoint)
        self.move(frameGm.topLeft())
        
    def addTableRow(self, row_data):
        """
        为QTableWidget动态添加数据
        """
        row = self.table.rowCount()
        self.table.setRowCount(row + 1)
        col = 0
        for item in row_data:
            cell = QTableWidgetItem(str(item))
            cell.setBackground(QBrush(QColor(255, 160, 122)))
            self.table.setItem(row, col, cell)
            col += 1
        self.table.setSizeAdjustPolicy(QAbstractScrollArea.AdjustToContents)
        self.table.resizeColumnsToContents()
        self.resize(self.sizeHint())

        
    def queryStudent(self):
        """
        查询学员信息
        """ 
        if self.queryBtn.isEnabled():
            mobile = self.textInput.text().strip()
            if mobile == "":
                self.showError("手机号不能为空")
                return
            if self.prev_mobile == mobile:
                self.showError("手机号没有变动")
                return

            self.prev_mobile = mobile 

            self.table.setRowCount(0)
            url = "http://www.anzhuoxfpx.com/extra_query.php"
            request = QNetworkRequest(QUrl(url))
            request.setHeader(QNetworkRequest.ContentTypeHeader, "application/x-www-form-urlencoded")
            data = QByteArray() 
            data.append("action=student_info")
            data.append("&mobile={0}".format(mobile))

            self.manager = QNetworkAccessManager()
            self.manager.finished.connect(self.handleResponse)
            self.manager.post(request, data)

    def handleResponse(self, reply):
        error = reply.error()
        if (error == QNetworkReply.NoError):
            bytesString = reply.readAll()
            json_arr = json.loads(str(bytesString, "utf-8"))
            if json_arr["code"] == 0:
                self.queryBtn.setEnabled(True)
                for user in json_arr["data"]:
                    rowData = [user['usertruename'], user['username'], user['groupname'], user['regtime']]
                    self.addTableRow(rowData)
            else:
                self.showError(json_arr["msg"])
        else: 
            print("Error occurred: ", error)
            self.data_error_reply.emit(reply.errorString())
        
    def showError(self, msg):
        self.queryBtn.setEnabled(True)
        msgBox = QMessageBox(self)
        msgBox.setWindowTitle("请求出错")
        msgBox.setIcon(QMessageBox.Critical)
        msgBox.setText(msg)
        msgBox.exec_()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = StudentQuery()
    win.show()
    app.setWindowIcon(QIcon('app.ico'))
    win.setWindowIcon(QIcon('app.ico'))
    sys.exit(app.exec_())
    