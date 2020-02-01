#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
信号连接信号
'''

import sys
from PyQt5.QtCore import QObject, pyqtSignal

class CustSignal(QObject):
    signal1 = pyqtSignal()
    signal2 = pyqtSignal(int)

    def __init__(self, parent=None):
        super(CustSignal, self).__init__(parent)

        self.signal1.connect(self.sin1Call)
        self.signal1.connect(self.sin2Call)

        # 信号sin2连接到信号sin1
        self.signal2.connect(self.signal1)

        # 信号发射
        self.signal1.emit()
        self.signal2.emit(1)

        # 断开 sin1、sin2 信号与各槽的连接
        self.signal1.disconnect(self.sin1Call)
        self.signal1.disconnect(self.sin2Call)
        self.signal2.disconnect(self.signal1)

        # 信号 sin1、sin2 连接同一个槽 sin1Call
        self.signal1.connect(self.sin1Call)
        self.signal2.connect(self.sin1Call)

        # 信号再发射
        self.signal1.emit()
        self.signal2.emit(1)


    def sin1Call(self):
        print("signal-1 emit")

    def sin2Call(self):
        print("signal-2 emit")


if __name__ == "__main__":
    custSignal = CustSignal()
    
