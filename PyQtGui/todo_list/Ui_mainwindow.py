# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'd:\WorkSpace\QT\QTStudy\PyQtGui\todo_list\mainwindow.ui'
#
# Created by: PyQt5 UI code generator 5.13.0
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(289, 365)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.centralwidget)
        self.verticalLayout.setObjectName("verticalLayout")
        self.todoView = QtWidgets.QListView(self.centralwidget)
        self.todoView.setObjectName("todoView")
        self.verticalLayout.addWidget(self.todoView)
        self.widget = QtWidgets.QWidget(self.centralwidget)
        self.widget.setObjectName("widget")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.widget)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.deleteButton = QtWidgets.QPushButton(self.widget)
        font = QtGui.QFont()
        font.setPointSize(11)
        self.deleteButton.setFont(font)
        self.deleteButton.setObjectName("deleteButton")
        self.horizontalLayout.addWidget(self.deleteButton)
        self.completeButton = QtWidgets.QPushButton(self.widget)
        font = QtGui.QFont()
        font.setPointSize(11)
        self.completeButton.setFont(font)
        self.completeButton.setObjectName("completeButton")
        self.horizontalLayout.addWidget(self.completeButton)
        self.verticalLayout.addWidget(self.widget)
        self.todoEdit = QtWidgets.QLineEdit(self.centralwidget)
        self.todoEdit.setMinimumSize(QtCore.QSize(0, 26))
        self.todoEdit.setObjectName("todoEdit")
        self.verticalLayout.addWidget(self.todoEdit)
        self.addButton = QtWidgets.QPushButton(self.centralwidget)
        font = QtGui.QFont()
        font.setPointSize(11)
        self.addButton.setFont(font)
        self.addButton.setObjectName("addButton")
        self.verticalLayout.addWidget(self.addButton)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 289, 26))
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
        self.deleteButton.setText(_translate("MainWindow", "Delete"))
        self.completeButton.setText(_translate("MainWindow", "Complete"))
        self.addButton.setText(_translate("MainWindow", "Add Todo"))
