#!/usr/bin/env python3
# -*- coding: utf-8 -*-
'''
自动化测试用例
'''

import sys
import time
import unittest
# import HTMLTestRunner
from PyQt5.QtWidgets import *
from PyQt5.QtTest import QTest
from PyQt5.QtCore import Qt, QThread, pyqtSignal
from CallMatrixWinUi import CallMatrixWinUi

class BackWorkThread(QThread):
    finishSignal = pyqtSignal(str)

    def __init__(self, sleetTime, parent=None):
        super(BackWorkThread, self).__init__(parent)
        self.sleepTime = sleetTime

    def run(self):
        time.sleep(self.sleepTime)
        # 休眠结束，发送信号告诉主线程窗口
        self.finishSignal.emit("ok, begin to close Window")

class MatrixWinTest(unittest.TestCase):
    '''初始化工作'''
    def setUp(self):
        print("*** setUp ***")
        self.app = QApplication(sys.argv)
        self.form = CallMatrixWinUi()
        self.form.show()

        # 新建对象，传入参数，每5秒执行一个测试用例 TestCase
        self.bkThread = BackWorkThread(int(5))
        # 连接子进程的信号和槽函数
        self.bkThread.finishSignal.connect(self.closeWindow)
        self.bkThread.start() # 启动线程

    '''退出清理工作'''
    def tearDown(self):
        print("*** tearDown ***")
        self.app.exec_()

    '''设置窗口中所有部件的值为0，状态为初始状态'''
    def setFormToZero(self):
        print("* setFormToZero *")
        self.form.ui.tequilaScrollBar.setValue(0)
        self.form.ui.tripleSecSpinBox.setValue(0)
        self.form.ui.limeJuiceLineEdit.setText("0.0")
        self.form.ui.iceHorizontalSlider.setValue(0)

        self.form.ui.selScrollBarLbl.setText("0")
        self.form.ui.selIceSliderLBL.setText("0")

    '''关闭窗口'''
    def closeWindow(self):
        print("* 关闭窗口")
        self.app.quit()

    '''测试用例-在默认状态下测试GUI'''
    def test_defaults(self):
        print("*** testCase test_defaults begin ***")
        self.form.setWindowTitle("开始测试用例 test_defaults")

        self.assertEqual(self.form.ui.tequilaScrollBar.value(), 8)
        self.assertEqual(self.form.ui.tripleSecSpinBox.value(), 4)
        self.assertEqual(self.form.ui.limeJuiceLineEdit.text(), "12.0")
        self.assertEqual(self.form.ui.iceHorizontalSlider.value(), 12)
        self.assertEqual(self.form.ui.speedButtonGroup.checkedButton().text(), 
            "Karate Chop")
        print("*** speedName=" + self.form.getSpeedName())

        # 用鼠标左键按OK
        okWidget = self.form.ui.okBtn
        QTest.mouseClick(okWidget, Qt.LeftButton)

        # 即使没有按OK，Class也处于默认状态
        self.assertEqual(self.form.getJiggers(), 36.0)
        self.assertEqual(self.form.getSpeedName(), "Karate Chop")
        print("*** testCase test_defaults end ***")

    '''测试用例-测试滚动条'''
    def test_moveScrollBar(self):
        print("*** testCase test_moveScrollBar begin ***")
        self.form.setWindowTitle("开始测试用例 test_moveScrollBar")
        self.setFormToZero()

        # 测试将龙舌兰酒的滚动条的值设定为12， ui中最大值为11
        self.form.ui.tequilaScrollBar.setValue(12)
        print("* 当执行self.form.ui.tequilaScrollBar.setValue(12)后，"
            "ui.tequilaScrollBar.value() => " + str(self.form.ui.tequilaScrollBar.value()))
        self.assertEqual(self.form.ui.tequilaScrollBar.value(), 11)

        # 测试将龙舌兰酒的滚动条的值设定为-1， ui中最小值为0
        self.form.ui.tequilaScrollBar.setValue(-1)
        print("* 当执行self.form.ui.tequilaScrollBar.setValue(-1)后，"
            "ui.tequilaScrollBar.value() => " + str(self.form.ui.tequilaScrollBar.value()))
        self.assertEqual(self.form.ui.tequilaScrollBar.value(), 0)

        # 重新将龙舌兰酒的滚动条的值设为5
        self.form.ui.tequilaScrollBar.setValue(5)

        # 用鼠标左键按OK
        okWidget = self.form.ui.okBtn
        QTest.mouseClick(okWidget, Qt.LeftButton)

        self.assertEqual(self.form.getJiggers(), 5)
        print("*** testCase test_moveScrollBar end ***")

    '''测试用例-测试SpinBox'''
    def test_tripleSecSpinBox(self):
        '''测试修改spinBox部件的最大最小值'''
        print("*** testCase test_tripleSecSpinBox begin ***")
        self.form.setWindowTitle("开始测试用例 test_moveScrollBar")
        self.setFormToZero()

        # tripleSecSpinBox 的取值为0到11，设置为12 和 -1 看看是否正常
        self.form.ui.tripleSecSpinBox.setValue(12)
        print("* 当执行self.form.ui.tripleSecSpinBox.setValue(12)后，"
            "ui.tripleSecSpinBox.value() => " + str(self.form.ui.tripleSecSpinBox.value()))
        self.assertEqual(self.form.ui.tripleSecSpinBox.value(), 11)

        self.form.ui.tripleSecSpinBox.setValue(-1)
        print("* 当执行self.form.ui.tripleSecSpinBox.setValue(-1)后，"
            "ui.tripleSecSpinBox.value() => " + str(self.form.ui.tripleSecSpinBox.value()))
        self.assertEqual(self.form.ui.tripleSecSpinBox.value(), 0)

        self.form.ui.tripleSecSpinBox.setValue(2)

        # 用鼠标左键按OK
        okWidget = self.form.ui.okBtn
        QTest.mouseClick(okWidget, Qt.LeftButton)

        self.assertEqual(self.form.getJiggers(), 2)
        print("*** testCase test_tripleSecSpinBox end ***")

    '''测试用例-测试柠檬汁单行文本框'''
    def test_limeJuiceLineEdit(self):
        print("*** testCase test_limeJuiceLineEdit begin ***")
        self.form.setWindowTitle("开始测试用例 test_limeJuiceLineEdit ")
        self.setFormToZero()

        # 清除lineEdit小部件值，然后键入 "3.5"
        self.form.ui.limeJuiceLineEdit.clear()
        QTest.keyClicks(self.form.ui.limeJuiceLineEdit, "3.5")

        # 用鼠标左键按OK
        okWidget = self.form.ui.okBtn
        QTest.mouseClick(okWidget, Qt.LeftButton)

        self.assertEqual(self.form.getJiggers(), 3.5)
        print("*** testCase test_limeJuiceLineEdit end ***")

    '''测试用例-测试iceHorizontalSlider'''
    def test_iceHorizontalSlider(self):
        print("*** testCase test_iceHorizontalSlider begin ***")
        self.form.setWindowTitle("开始测试用例 test_iceHorizontalSlier ")
        self.setFormToZero()

        self.form.ui.iceHorizontalSlider.setValue(4)

        # 用鼠标左键按OK
        okWidget = self.form.ui.okBtn
        QTest.mouseClick(okWidget, Qt.LeftButton)

        self.assertEqual(self.form.getJiggers(), 4)
        print("*** testCase test_iceHorizontalSlider end ***")

    '''测试用例-test_liters'''
    def test_liters(self):
        print("*** testCase test_liters begin ***")
        self.form.setWindowTitle("开始测试用例 test_liters ")
        self.setFormToZero()

        self.assertAlmostEqual(self.form.getLiters(), 0.0)
        self.form.ui.iceHorizontalSlider.setValue(1)
        self.assertAlmostEqual(self.form.getLiters(), 0.0444)
        self.form.ui.iceHorizontalSlider.setValue(2)
        self.assertAlmostEqual(self.form.getLiters(), 0.0444 * 2)
        print("*** testCase test_liters end ***")

    '''测试用例-测试选择搅拌按钮'''
    def test_blenderSpeedButtons(self):
        print("*** testCase test_blenderSpeedButtons begin ***")
        self.form.ui.speedButton1.click()
        self.assertEqual(self.form.getSpeedName(), "Mix")
        self.form.ui.speedButton2.click()
        self.assertEqual(self.form.getSpeedName(), "Whip")
        self.form.ui.speedButton3.click()
        self.assertEqual(self.form.getSpeedName(), "Puree")
        self.form.ui.speedButton4.click()
        self.assertEqual(self.form.getSpeedName(), "Chop")
        self.form.ui.speedButton5.click()
        self.assertEqual(self.form.getSpeedName(), "Karate Chop")
        self.form.ui.speedButton6.click()
        self.assertEqual(self.form.getSpeedName(), "Beat")
        self.form.ui.speedButton7.click()
        self.assertEqual(self.form.getSpeedName(), "Smash")
        self.form.ui.speedButton8.click()
        self.assertEqual(self.form.getSpeedName(), "Liquefy")
        self.form.ui.speedButton9.click()
        self.assertEqual(self.form.getSpeedName(), "Vaporize")
        print("*** testCase test_blenderSpeedButtons end ***")


'''默认测试所有的测试用例'''
def runUnitTest1():
    unittest.main()

'''按照指定顺序执行测试用例'''
def runUnitTest2():
    suite = unittest.TestSuite()
    suite.addTest(MatrixWinTest("test_defaults"))
    suite.addTest(MatrixWinTest("test_tripleSecSpinBox"))
    suite.addTest(MatrixWinTest("test_limeJuiceLineEdit"))
    suite.addTest(MatrixWinTest("test_iceHorizontalSlider"))
    suite.addTest(MatrixWinTest("test_liters"))
    suite.addTest(MatrixWinTest("test_blenderSpeedButtons"))
    runner = unittest.TextTestRunner()
    runner.run(suite)

if __name__ == "__main__":
    runUnitTest2()