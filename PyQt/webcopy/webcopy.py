#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import sys
import os

from PyQt5.QtWidgets import (
    QApplication, QWidget, 
    QMessageBox, QFileDialog
)
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import QProcess

from Ui_webcopy import Ui_Form
from utils import *

curr_dir = os.path.dirname(os.path.realpath(__file__))

class WebCopy(QWidget):

    def __init__(self, parent=None):
        super().__init__(parent)
        
        # 初始化UI
        self.ui = Ui_Form()
        self.ui.setupUi(self)

        # 类的属性
        self.copyUrl = ""
        self.savePath = ""

        self.process = QProcess()
        self.process.setProcessChannelMode(QProcess.MergedChannels)

        # 连接信号
        self.ui.browserDirBtn.clicked.connect(self.browserDir)
        self.ui.startBtn.clicked.connect(self.startCopy)
        self.ui.inputUrl.textChanged.connect(self.assignCopyUrl)
        self.ui.dirInput.textChanged.connect(self.assignSavePath)

        self.process.started.connect(lambda : self.appendInfo("========页面克隆开始========\n"))
        self.process.finished.connect(lambda : self.appendInfo("\n========页面克隆结束！=========="))
        self.process.readyReadStandardOutput.connect(self.readProcessOutput)

    def assignCopyUrl(self, text):
        self.copyUrl = text

    def assignSavePath(self, text):
        self.savePath = text
        
    def browserDir(self):
        """
        浏览目录
        """
        self.ui.dirInput.setText(QFileDialog.getExistingDirectory()) 
    
    def startCopy(self):
        """
        开始下载
        """
        if len(self.savePath) == 0:
            return self.showError("保存目录不能为空")

        if not os.path.exists(self.savePath):
            return self.showError("保存目录不存在！")

        if len(self.copyUrl) == 0 or not check_url_valid(self.copyUrl):
            return self.showError("无效的URL！")
        
        os.chdir(self.savePath)
        
        self.process.start(curr_dir + "/bin/wget.exe", [
            "-E", "-H", "-k", "-K", "-p", self.copyUrl 
        ])
        
    def showError(self, msg):
        """
        显示错误信息
        :msg string 
        """
        msgBox = QMessageBox(self)
        msgBox.setWindowTitle("错误提示")
        msgBox.setIcon(QMessageBox.Critical)
        msgBox.setText(msg)
        msgBox.exec_()
        
    def readProcessOutput(self):
        output = str(self.process.readAll(), "utf-8") 
        self.appendInfo(output)
        
    def appendInfo(self, text):
        self.ui.outputBoard.appendPlainText(text)

        
if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = WebCopy()
    win.show()
    app.setWindowIcon(QIcon('copy.png'))
    win.setWindowIcon(QIcon('copy.png'))
    sys.exit(app.exec_())
    