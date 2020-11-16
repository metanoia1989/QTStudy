#!/usr/bin/env python

from PyQt5 import QtWidgets, QtGui

class MyWidget(QtWidgets.QWidget):

    def __init__(self, parent=None):
        super().__init__(parent=parent)

        self.tableModel = QtGui.QStandardItemModel(self)
        self.tableModel.itemChanged.connect(self.itemChanged)

        item = QtGui.QStandardItem("Click me")
        item.setCheckable(True)
        self.tableModel.appendRow(item)

        self.mainLayout = QtWidgets.QVBoxLayout()
        self.setLayout(self.mainLayout)

        self.tableView = QtWidgets.QTableView()
        self.tableView.setModel(self.tableModel)
        self.mainLayout.addWidget(self.tableView)

    def itemChanged(self, item):
        print("Item {!r} checkState: {}".format(item.text(), item.checkState()))


if __name__ == "__main__":
    app = QtWidgets.QApplication([])

    win = MyWidget()
    win.show()
    win.raise_()
    app.exec_()
    