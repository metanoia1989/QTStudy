#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
生成自动化测试的报告
'''

import time
import unittest
import HTMLTestRunner
from MatrixWinTest import MatrixWinTest

if __name__ == "__main__":
    now = time.strftime("%Y-%m-%d-%H_%M_%S", time.localtime(time.time()))
    print(now)
    testunit = unittest.TestSuite()
    testunit.addTest(unittest.makeSuite(MatrixWinTest))

    htmlFile = ".\\" +now + "HTMLtemplate.html"
    print("htmlFile" + htmlFile)
    with open(htmlFile, "wb") as fp:
        runner = HTMLTestRunner.HTMLTestRunner(
            stream=fp,
            title="PyQt5测试报告",
            description="用例测试情况"
        )
        runner.run(testunit)