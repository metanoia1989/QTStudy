# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'f:\WORKSPACE\QT\QTStudy\PyQt\chapter09_extended_application\testCase\MatrixWinUi.ui'
#
# Created by: PyQt5 UI code generator 5.13.0
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MatrixWin(object):
    def setupUi(self, MatrixWin):
        MatrixWin.setObjectName("MatrixWin")
        MatrixWin.resize(837, 583)
        self.groupBox = QtWidgets.QGroupBox(MatrixWin)
        self.groupBox.setGeometry(QtCore.QRect(10, 10, 791, 271))
        self.groupBox.setObjectName("groupBox")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.groupBox)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.label = QtWidgets.QLabel(self.groupBox)
        self.label.setObjectName("label")
        self.gridLayout_2.addWidget(self.label, 0, 0, 1, 1)
        self.tequilaScrollBar = QtWidgets.QScrollBar(self.groupBox)
        self.tequilaScrollBar.setMaximum(11)
        self.tequilaScrollBar.setProperty("value", 8)
        self.tequilaScrollBar.setOrientation(QtCore.Qt.Horizontal)
        self.tequilaScrollBar.setObjectName("tequilaScrollBar")
        self.gridLayout_2.addWidget(self.tequilaScrollBar, 0, 1, 1, 1)
        self.selScrollBarLbl = QtWidgets.QLabel(self.groupBox)
        self.selScrollBarLbl.setMinimumSize(QtCore.QSize(100, 0))
        self.selScrollBarLbl.setText("")
        self.selScrollBarLbl.setObjectName("selScrollBarLbl")
        self.gridLayout_2.addWidget(self.selScrollBarLbl, 0, 2, 1, 1)
        self.label_5 = QtWidgets.QLabel(self.groupBox)
        self.label_5.setObjectName("label_5")
        self.gridLayout_2.addWidget(self.label_5, 0, 3, 1, 1)
        self.label_2 = QtWidgets.QLabel(self.groupBox)
        self.label_2.setObjectName("label_2")
        self.gridLayout_2.addWidget(self.label_2, 1, 0, 1, 1)
        self.tripleSecSpinBox = QtWidgets.QSpinBox(self.groupBox)
        self.tripleSecSpinBox.setMaximum(11)
        self.tripleSecSpinBox.setProperty("value", 4)
        self.tripleSecSpinBox.setObjectName("tripleSecSpinBox")
        self.gridLayout_2.addWidget(self.tripleSecSpinBox, 1, 1, 1, 1)
        self.label_6 = QtWidgets.QLabel(self.groupBox)
        self.label_6.setObjectName("label_6")
        self.gridLayout_2.addWidget(self.label_6, 1, 3, 1, 1)
        self.label_3 = QtWidgets.QLabel(self.groupBox)
        self.label_3.setObjectName("label_3")
        self.gridLayout_2.addWidget(self.label_3, 2, 0, 1, 1)
        self.limeJuiceLineEdit = QtWidgets.QLineEdit(self.groupBox)
        self.limeJuiceLineEdit.setObjectName("limeJuiceLineEdit")
        self.gridLayout_2.addWidget(self.limeJuiceLineEdit, 2, 1, 1, 1)
        self.label_7 = QtWidgets.QLabel(self.groupBox)
        self.label_7.setObjectName("label_7")
        self.gridLayout_2.addWidget(self.label_7, 2, 3, 1, 1)
        self.label_4 = QtWidgets.QLabel(self.groupBox)
        self.label_4.setObjectName("label_4")
        self.gridLayout_2.addWidget(self.label_4, 3, 0, 1, 1)
        self.iceHorizontalSlider = QtWidgets.QSlider(self.groupBox)
        self.iceHorizontalSlider.setMaximum(20)
        self.iceHorizontalSlider.setProperty("value", 12)
        self.iceHorizontalSlider.setOrientation(QtCore.Qt.Horizontal)
        self.iceHorizontalSlider.setObjectName("iceHorizontalSlider")
        self.gridLayout_2.addWidget(self.iceHorizontalSlider, 3, 1, 1, 1)
        self.selIceSliderLBL = QtWidgets.QLabel(self.groupBox)
        self.selIceSliderLBL.setMinimumSize(QtCore.QSize(100, 0))
        self.selIceSliderLBL.setText("")
        self.selIceSliderLBL.setObjectName("selIceSliderLBL")
        self.gridLayout_2.addWidget(self.selIceSliderLBL, 3, 2, 1, 1)
        self.label_8 = QtWidgets.QLabel(self.groupBox)
        self.label_8.setObjectName("label_8")
        self.gridLayout_2.addWidget(self.label_8, 3, 3, 1, 1)
        self.groupBox_2 = QtWidgets.QGroupBox(MatrixWin)
        self.groupBox_2.setGeometry(QtCore.QRect(10, 290, 481, 221))
        self.groupBox_2.setObjectName("groupBox_2")
        self.gridLayout = QtWidgets.QGridLayout(self.groupBox_2)
        self.gridLayout.setObjectName("gridLayout")
        self.speedButton1 = QtWidgets.QRadioButton(self.groupBox_2)
        self.speedButton1.setObjectName("speedButton1")
        self.speedButtonGroup = QtWidgets.QButtonGroup(MatrixWin)
        self.speedButtonGroup.setObjectName("speedButtonGroup")
        self.speedButtonGroup.addButton(self.speedButton1)
        self.gridLayout.addWidget(self.speedButton1, 0, 0, 1, 1)
        self.speedButton2 = QtWidgets.QRadioButton(self.groupBox_2)
        self.speedButton2.setObjectName("speedButton2")
        self.speedButtonGroup.addButton(self.speedButton2)
        self.gridLayout.addWidget(self.speedButton2, 0, 1, 1, 1)
        self.speedButton3 = QtWidgets.QRadioButton(self.groupBox_2)
        self.speedButton3.setObjectName("speedButton3")
        self.speedButtonGroup.addButton(self.speedButton3)
        self.gridLayout.addWidget(self.speedButton3, 0, 2, 1, 1)
        self.speedButton4 = QtWidgets.QRadioButton(self.groupBox_2)
        self.speedButton4.setObjectName("speedButton4")
        self.speedButtonGroup.addButton(self.speedButton4)
        self.gridLayout.addWidget(self.speedButton4, 1, 0, 1, 1)
        self.speedButton5 = QtWidgets.QRadioButton(self.groupBox_2)
        self.speedButton5.setChecked(True)
        self.speedButton5.setObjectName("speedButton5")
        self.speedButtonGroup.addButton(self.speedButton5)
        self.gridLayout.addWidget(self.speedButton5, 1, 1, 1, 1)
        self.speedButton6 = QtWidgets.QRadioButton(self.groupBox_2)
        self.speedButton6.setObjectName("speedButton6")
        self.speedButtonGroup.addButton(self.speedButton6)
        self.gridLayout.addWidget(self.speedButton6, 1, 2, 1, 1)
        self.speedButton7 = QtWidgets.QRadioButton(self.groupBox_2)
        self.speedButton7.setObjectName("speedButton7")
        self.speedButtonGroup.addButton(self.speedButton7)
        self.gridLayout.addWidget(self.speedButton7, 2, 0, 1, 1)
        self.speedButton8 = QtWidgets.QRadioButton(self.groupBox_2)
        self.speedButton8.setObjectName("speedButton8")
        self.speedButtonGroup.addButton(self.speedButton8)
        self.gridLayout.addWidget(self.speedButton8, 2, 1, 1, 1)
        self.speedButton9 = QtWidgets.QRadioButton(self.groupBox_2)
        self.speedButton9.setObjectName("speedButton9")
        self.speedButtonGroup.addButton(self.speedButton9)
        self.gridLayout.addWidget(self.speedButton9, 2, 2, 1, 1)
        self.groupBox_3 = QtWidgets.QGroupBox(MatrixWin)
        self.groupBox_3.setGeometry(QtCore.QRect(500, 290, 321, 221))
        self.groupBox_3.setObjectName("groupBox_3")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.groupBox_3)
        self.verticalLayout.setObjectName("verticalLayout")
        self.resultText = QtWidgets.QTextEdit(self.groupBox_3)
        self.resultText.setObjectName("resultText")
        self.verticalLayout.addWidget(self.resultText)
        self.layoutWidget = QtWidgets.QWidget(MatrixWin)
        self.layoutWidget.setGeometry(QtCore.QRect(20, 530, 391, 41))
        self.layoutWidget.setObjectName("layoutWidget")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.layoutWidget)
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.okBtn = QtWidgets.QPushButton(self.layoutWidget)
        self.okBtn.setObjectName("okBtn")
        self.horizontalLayout.addWidget(self.okBtn)
        self.clearBtn = QtWidgets.QPushButton(self.layoutWidget)
        self.clearBtn.setObjectName("clearBtn")
        self.horizontalLayout.addWidget(self.clearBtn)
        self.cancelBtn = QtWidgets.QPushButton(self.layoutWidget)
        self.cancelBtn.setObjectName("cancelBtn")
        self.horizontalLayout.addWidget(self.cancelBtn)

        self.retranslateUi(MatrixWin)
        self.tequilaScrollBar.valueChanged['int'].connect(MatrixWin.uiScrollBarValueChanged)
        self.okBtn.clicked.connect(MatrixWin.uiAccept)
        self.iceHorizontalSlider.valueChanged['int'].connect(MatrixWin.uiIceSliderValueChanged)
        self.clearBtn.clicked.connect(MatrixWin.uiClear)
        self.cancelBtn.clicked.connect(MatrixWin.uiReject)
        QtCore.QMetaObject.connectSlotsByName(MatrixWin)

    def retranslateUi(self, MatrixWin):
        _translate = QtCore.QCoreApplication.translate
        MatrixWin.setWindowTitle(_translate("MatrixWin", "玛格丽特鸡尾酒*调酒器 抄版"))
        self.groupBox.setTitle(_translate("MatrixWin", "原料"))
        self.label.setText(_translate("MatrixWin", "龙舌兰酒"))
        self.label_5.setText(_translate("MatrixWin", "升"))
        self.label_2.setText(_translate("MatrixWin", "三重蒸馏酒"))
        self.label_6.setText(_translate("MatrixWin", "升"))
        self.label_3.setText(_translate("MatrixWin", "柠檬汁"))
        self.limeJuiceLineEdit.setText(_translate("MatrixWin", "12.0"))
        self.label_7.setText(_translate("MatrixWin", "升"))
        self.label_4.setText(_translate("MatrixWin", "冰块"))
        self.label_8.setText(_translate("MatrixWin", "个"))
        self.groupBox_2.setTitle(_translate("MatrixWin", "9种搅拌速度"))
        self.speedButton1.setText(_translate("MatrixWin", "Mix"))
        self.speedButton2.setText(_translate("MatrixWin", "Whip"))
        self.speedButton3.setText(_translate("MatrixWin", "Puree"))
        self.speedButton4.setText(_translate("MatrixWin", "Chop"))
        self.speedButton5.setText(_translate("MatrixWin", "Karate Chop"))
        self.speedButton6.setText(_translate("MatrixWin", "Beat"))
        self.speedButton7.setText(_translate("MatrixWin", "Smash"))
        self.speedButton8.setText(_translate("MatrixWin", "Liquefy"))
        self.speedButton9.setText(_translate("MatrixWin", "Vaporize"))
        self.groupBox_3.setTitle(_translate("MatrixWin", "操作结果"))
        self.okBtn.setText(_translate("MatrixWin", "OK"))
        self.clearBtn.setText(_translate("MatrixWin", "Clear"))
        self.cancelBtn.setText(_translate("MatrixWin", "Cancel"))
