#!/usr/bin/env python3
# -*- coding: utf-8 -*-
'''
QTreeView系统定制样式
'''

import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *

if __name__ == "__main__":
    app = QApplication(sys.argv)
    # Windows 系统提供的模式
    model = QDirModel()
    # 创建一个QTreeView部件
    tree = QTreeView()
    # 为部件添加模式
    tree.setModel(model)
    tree.setWindowTitle("QTreeView例子")
    tree.resize(640, 480)
    tree.show()
    sys.exit(app.exec_())