#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtSql import QSqlDatabase

class ExecDatabaseDemo(QWidget):
    def __init__(self, parent=None):
        super(ExecDatabaseDemo, self).__init__(parent)

        self.db = QSqlDatabase.addDatabase("QSQLITE")
        self.db.setDatabaseName("./db/database.db")
        self.db.open()

    def closeEvent(self, event):
        self.db.close()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = ExecDatabaseDemo()
    win.show()
    sys.exit(app.exec_())
