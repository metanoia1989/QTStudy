# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'f:\WORKSPACE\QT\QTStudy\PyQt\chapter09_extended_application\pyqtgraph-demo\pyqtgraph_pyqt.ui'
#
# Created by: PyQt5 UI code generator 5.13.0
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(761, 723)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.pyqtgraph1 = GraphicsLayoutWidget(self.centralwidget)
        self.pyqtgraph1.setGeometry(QtCore.QRect(40, 20, 531, 191))
        self.pyqtgraph1.setObjectName("pyqtgraph1")
        self.pyqtgraph2 = GraphicsLayoutWidget(self.centralwidget)
        self.pyqtgraph2.setGeometry(QtCore.QRect(50, 250, 281, 401))
        self.pyqtgraph2.setObjectName("pyqtgraph2")
        self.pushButton = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton.setGeometry(QtCore.QRect(610, 90, 93, 28))
        self.pushButton.setObjectName("pushButton")
        self.pushButton_2 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_2.setGeometry(QtCore.QRect(380, 260, 93, 28))
        self.pushButton_2.setObjectName("pushButton_2")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 761, 26))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.pushButton.setText(_translate("MainWindow", "水平绘图"))
        self.pushButton_2.setText(_translate("MainWindow", "垂直绘图"))
from pyqtgraph import GraphicsLayoutWidget
