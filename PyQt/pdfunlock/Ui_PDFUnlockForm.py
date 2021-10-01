# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'e:\WorkSpace\QTStudy\PyQt\pdfunlock\PDFUnlockForm.ui'
#
# Created by: PyQt5 UI code generator 5.15.1
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_PDFUnlockForm(object):
    def setupUi(self, PDFUnlockForm):
        PDFUnlockForm.setObjectName("PDFUnlockForm")
        PDFUnlockForm.resize(400, 300)
        PDFUnlockForm.setStyleSheet("* {\n"
"    font-size: 12px;\n"
"    font-family: 微软雅黑;\n"
"}")
        self.verticalLayout = QtWidgets.QVBoxLayout(PDFUnlockForm)
        self.verticalLayout.setObjectName("verticalLayout")
        self.gridLayout = QtWidgets.QGridLayout()
        self.gridLayout.setObjectName("gridLayout")
        self.label = QtWidgets.QLabel(PDFUnlockForm)
        self.label.setObjectName("label")
        self.gridLayout.addWidget(self.label, 0, 0, 1, 1)
        self.editSourceDir = QtWidgets.QLineEdit(PDFUnlockForm)
        self.editSourceDir.setObjectName("editSourceDir")
        self.gridLayout.addWidget(self.editSourceDir, 0, 1, 1, 1)
        self.btnSelectSource = QtWidgets.QPushButton(PDFUnlockForm)
        self.btnSelectSource.setObjectName("btnSelectSource")
        self.gridLayout.addWidget(self.btnSelectSource, 0, 2, 1, 1)
        self.label_2 = QtWidgets.QLabel(PDFUnlockForm)
        self.label_2.setObjectName("label_2")
        self.gridLayout.addWidget(self.label_2, 1, 0, 1, 1)
        self.editOutputDir = QtWidgets.QLineEdit(PDFUnlockForm)
        self.editOutputDir.setObjectName("editOutputDir")
        self.gridLayout.addWidget(self.editOutputDir, 1, 1, 1, 1)
        self.btnSelectOutput = QtWidgets.QPushButton(PDFUnlockForm)
        self.btnSelectOutput.setObjectName("btnSelectOutput")
        self.gridLayout.addWidget(self.btnSelectOutput, 1, 2, 1, 1)
        self.btnStartConvert = QtWidgets.QPushButton(PDFUnlockForm)
        self.btnStartConvert.setObjectName("btnStartConvert")
        self.gridLayout.addWidget(self.btnStartConvert, 2, 0, 1, 3)
        self.verticalLayout.addLayout(self.gridLayout)
        self.editOutput = QtWidgets.QPlainTextEdit(PDFUnlockForm)
        self.editOutput.setObjectName("editOutput")
        self.verticalLayout.addWidget(self.editOutput)

        self.retranslateUi(PDFUnlockForm)
        QtCore.QMetaObject.connectSlotsByName(PDFUnlockForm)

    def retranslateUi(self, PDFUnlockForm):
        _translate = QtCore.QCoreApplication.translate
        PDFUnlockForm.setWindowTitle(_translate("PDFUnlockForm", "PDF解锁小工具"))
        self.label.setText(_translate("PDFUnlockForm", "PDF源目录"))
        self.btnSelectSource.setText(_translate("PDFUnlockForm", "点击选择"))
        self.label_2.setText(_translate("PDFUnlockForm", "PDF输出目录"))
        self.btnSelectOutput.setText(_translate("PDFUnlockForm", "点击选择"))
        self.btnStartConvert.setText(_translate("PDFUnlockForm", "开始转换"))