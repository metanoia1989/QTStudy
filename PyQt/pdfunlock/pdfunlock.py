#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import sys
import os
import subprocess
from pathlib import Path

import pikepdf
from pikepdf import _cpphelpers

from PyQt5.QtWidgets import (
    QApplication, QWidget, 
    QMessageBox, QFileDialog
)
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import QProcess

from Ui_PDFUnlockForm import Ui_PDFUnlockForm
from utils import *

curr_dir = os.path.dirname(os.path.realpath(__file__))

class WebCopy(QWidget):

    def __init__(self, parent=None):
        super().__init__(parent)
        
        # 初始化UI
        self.ui = Ui_PDFUnlockForm()
        self.ui.setupUi(self)

        # 设置QPlainTextEdit只读

        # 连接信号
        self.ui.btnStartConvert.clicked.connect(self.startUnlock)
        self.ui.btnSelectSource.clicked.connect(self.browserSourceDir)
        self.ui.btnSelectOutput.clicked.connect(self.browserOutputDir)

    def browserSourceDir(self):
        """
        浏览PDF源目录
        """
        self.ui.editSourceDir.setText(QFileDialog.getExistingDirectory()) 

    def browserOutputDir(self):
        """
        浏览PDF输出目录
        """
        self.ui.editOutputDir.setText(QFileDialog.getExistingDirectory()) 
    
    def startUnlock(self):
        """
        开始解锁PDF
        """
        source_dir = self.ui.editSourceDir.text().strip() 
        output_dir = self.ui.editOutputDir.text().strip()
        
        if source_dir == "" or output_dir == "":
            return self.showError("PDF源目录和PDF输出目录均不能为空！")
        
        source_dir = Path(source_dir)
        output_dir = Path(output_dir)


        if not source_dir.exists():
            return self.showError("PDF源目录不存在！")

        if not output_dir.exists():
            return self.showError("PDF输出目录不存在！")

        self.appendInfo("PDF源目录：{0}".format(str(source_dir)))
        self.appendInfo("PDF输出目录：{0}".format(str(output_dir)))

        os.chdir(str(output_dir)) 
        pdfs = [ x.absolute() for x in source_dir.iterdir() if x.is_file()]
        if len(pdfs) == 0:
            return 
        
        try:
            for path in pdfs:
                if path.name.endswith(".pdf"):
                    with pikepdf.open(path) as f:
                        new_name = path.stem + "_unlock" + path.suffix

                        f.save(new_name)
                        self.appendInfo("{0} 解锁完毕!".format(path.name))

            self.appendInfo("所有文件都解锁完了，快去看看！")
            subprocess.Popen("explorer {0}".format(str(output_dir)))
        except Exception as e:
            self.appendInfo("解锁出错：")
            self.appendInfo(str(e))
        
        
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
        
        
    def appendInfo(self, text):
        self.ui.editOutput.appendPlainText(text)

        
if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = WebCopy()
    win.show()
    app.setWindowIcon(QIcon('pdfunlock.png'))
    win.setWindowIcon(QIcon('pdfunlock.png'))
    sys.exit(app.exec_())
    