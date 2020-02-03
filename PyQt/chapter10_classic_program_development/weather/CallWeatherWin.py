#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import requests
from PyQt5.QtWidgets import QApplication, QMainWindow
from Ui_WeatherWin import Ui_Form


class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.ui = Ui_Form()
        self.ui.setupUi(self)

    def queryWeather(self):
        print("* queryWeather  ")
        cityName = self.ui.weatherComboBox.currentText()
        cityCode = self.transCityName(cityName)

        res = requests.get(
            "http://www.weather.com.cn/data/sk/{0}.html".format(cityCode))
        res.encoding = "utf-8"
        result = res.json()
        print(result)
        msg1 = "城市：%s\n" % result["weatherinfo"]["city"]
        msg2 = "风向：%s\n" % result["weatherinfo"]["WD"]
        msg3 = "温度：%s 度\n" % result["weatherinfo"]["temp"]
        msg4 = "风力：%s\n" % result["weatherinfo"]["WS"]
        msg5 = "湿度：%s\n" % result["weatherinfo"]["SD"]
        content = msg1 + msg2 + msg3 + msg4 + msg5
        self.ui.resultText.setText(content)

    def transCityName(self, cityName):
        cityCode = ""
        if cityName == "北京":
            cityCode = "101010100"
        elif cityName == "天津":
            cityCode = "101030100"
        elif cityName == "上海":
            cityCode = "101030101"
        elif cityName == "武汉":
            cityCode = "101200101"

        return cityCode

    def clearResult(self):
        print("* clearResult ")
        self.ui.resultText.clear()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MainWindow()
    win.show()
    sys.exit(app.exec_())
