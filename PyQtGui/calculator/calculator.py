#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *

import operator, sys

from Ui_mainwindow import Ui_MainWindow

# Calculator state
READY = 0
INPUT = 1

class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, *args, **kwargs):
        super(MainWindow, self).__init__(*args, **kwargs)
        self.setupUi(self)


        # Setup numbers
        for n in range(0, 10):
            getattr(self, "pushButton_n%s" % n).pressed.connect(
                lambda v=n: self.input_number(v)
            )   
        
        # Setup operations
        self.pushButton_add.pressed.connect(lambda: self.operation(operator.add))
        self.pushButton_sub.pressed.connect(lambda: self.operation(operator.sub))
        self.pushButton_mul.pressed.connect(lambda: self.operation(operator.mul))
        self.pushButton_div.pressed.connect(lambda: self.operation(operator.truediv))

        self.pushButton_pc.pressed.connect(self.operation_pc)
        self.pushButton_eq.pressed.connect(self.equals)

        # Setup actions
        self.actionReset.triggered.connect(self.reset)
        self.pushButton_ac.pressed.connect(self.reset)

        self.actionExit.triggered.connect(self.close)

        self.pushButton_m.pressed.connect(self.memory_store)
        self.pushButton_mr.pressed.connect(self.memory_recall)

        self.memory = 0
        self.reset()

        self.show()

    def display(self):
        self.lcdNumber.display(self.stack[-1])

    def reset(self):
        self.state = READY
        self.stack = [0]
        self.last_operation = None
        self.current_op = None
        self.display()

    def memory_store(self):
        self.memory = self.lcdNumber.value()

    def memory_recall(self):
        self.state = INPUT
        self.stack[-1] = self.memory
        self.display()

    def input_number(self, v):
        prevValue = self.stack[-1]
        if self.state == READY:
            self.state = INPUT
            self.stack[-1] = v
        else:
            self.stack[-1] = self.stack[-1] * 10 + v

        try:
            self.display()
        except OverflowError:
            self.stack[-1] = prevValue
            self.display()

    def operation(self, op):
        if self.current_op:
            self.equals()

        self.stack.append(0)
        self.state = INPUT
        self.current_op = op
        print(self.stack)

    def operation_pc(self):
        self.state = INPUT
        self.stack[-1] *= 0.01
        self.display()

    def equals(self):
        # if self.state == READY and self.last_operation:
        #     s, self.current_op = self.last_operation
        #     self.stack.append(s)

        if self.current_op:
            self.last_operation = self.stack[-1], self.current_op

            try:
                self.stack = [self.current_op(*self.stack)]
            except Exception:
                self.lcdNumber.display("Err")
                self.stack = [0]
            else:
                self.current_op = None
                self.state = READY
                self.display()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    app.setApplicationName("Calculon")
    win = MainWindow()
    app.exec_()