# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'e:\WorkSpace\QTStudy\PyQt\webcopy\webcopy.ui'
#
# Created by: PyQt5 UI code generator 5.15.1
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(452, 445)
        Form.setStyleSheet("* {\n"
"    font-family: 微软雅黑;\n"
"}")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(Form)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.splitter = QtWidgets.QSplitter(Form)
        self.splitter.setOrientation(QtCore.Qt.Vertical)
        self.splitter.setObjectName("splitter")
        self.widget = QtWidgets.QWidget(self.splitter)
        self.widget.setObjectName("widget")
        self.gridLayout = QtWidgets.QGridLayout(self.widget)
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.gridLayout.setObjectName("gridLayout")
        self.label = QtWidgets.QLabel(self.widget)
        self.label.setObjectName("label")
        self.gridLayout.addWidget(self.label, 0, 0, 1, 1)
        self.inputUrl = QtWidgets.QLineEdit(self.widget)
        self.inputUrl.setObjectName("inputUrl")
        self.gridLayout.addWidget(self.inputUrl, 0, 1, 1, 1)
        self.label_2 = QtWidgets.QLabel(self.widget)
        self.label_2.setObjectName("label_2")
        self.gridLayout.addWidget(self.label_2, 1, 0, 1, 1)
        self.dirInput = QtWidgets.QLineEdit(self.widget)
        self.dirInput.setObjectName("dirInput")
        self.gridLayout.addWidget(self.dirInput, 1, 1, 1, 1)
        self.browserDirBtn = QtWidgets.QPushButton(self.widget)
        self.browserDirBtn.setObjectName("browserDirBtn")
        self.gridLayout.addWidget(self.browserDirBtn, 1, 2, 1, 1)
        self.startBtn = QtWidgets.QPushButton(self.widget)
        self.startBtn.setObjectName("startBtn")
        self.gridLayout.addWidget(self.startBtn, 2, 1, 1, 1)
        self.widget1 = QtWidgets.QWidget(self.splitter)
        self.widget1.setObjectName("widget1")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.widget1)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.label_3 = QtWidgets.QLabel(self.widget1)
        self.label_3.setObjectName("label_3")
        self.horizontalLayout.addWidget(self.label_3)
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem)
        self.verticalLayout.addLayout(self.horizontalLayout)
        self.outputBoard = QtWidgets.QPlainTextEdit(self.widget1)
        self.outputBoard.setObjectName("outputBoard")
        self.verticalLayout.addWidget(self.outputBoard)
        self.verticalLayout_2.addWidget(self.splitter)

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "网页下载工具"))
        self.label.setText(_translate("Form", "网页地址"))
        self.label_2.setText(_translate("Form", "保存目录"))
        self.browserDirBtn.setText(_translate("Form", "浏览"))
        self.startBtn.setText(_translate("Form", "开始下载"))
        self.label_3.setText(_translate("Form", "输出记录"))
