#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from PyQt5.QtCore import pyqtSlot
from PyQt5.QtWidgets import QMainWindow, QApplication
from Ui_pandas_pyqt import Ui_MainWindow
from qtpandas.models.DataFrameModel import DataFrameModel
import pandas as pd
import sys

class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)

        '''初始化pandasqt'''
        widget = self.pandastablewidget
        widget.resize(600, 500)

        self.model = DataFrameModel() # 设置新的模型
        widget.setViewModel(self.model)

        self.df = pd.read_execl("../data/fund_data.xlsx", encoding="gbk")
        self.df_original = self.df.copy() # 备份原始数据
        self.model.setDataFrame(self.df)

    @pyqtSlot()
    def on_pushButton_clicked(self):
        '''
        初始化pandas
        '''
        self.model.setDataFrame(self.df_original)

    @pyqtSlot()
    def on_pushButton_2_clicked(self):
        '''
        保存数据
        '''
        self.df.to_excel("../data/fund_data_new2.xlsx")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    ui = MainWindow()
    ui.show()
    sys.exit(app.exec_())