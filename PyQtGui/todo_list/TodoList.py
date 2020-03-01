#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys, json, os
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5.QtGui import QImage
from PyQt5.QtCore import Qt, QAbstractListModel
from Ui_mainwindow import Ui_MainWindow


curPath = os.path.dirname(__file__)
curData = os.path.join(curPath, "data.json")
icon = os.path.join(curPath, "tick.png")
tick = QImage(icon)

class TodoModel(QAbstractListModel):
    def __init__(self, todos=None, parent=None):
        super(TodoModel, self).__init__(parent)
        self.todos = todos or []

    def data(self, index, role):
        if role == Qt.DisplayRole:
            _, text = self.todos[index.row()]
            return text

        if role == Qt.DecorationRole:
            status, _ = self.todos[index.row()]
            if status:
                return tick

    def rowCount(self, index):
        return len(self.todos)

class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self):
        QMainWindow.__init__(self)
        Ui_MainWindow.__init__(self)
        self.setupUi(self)
        self.model = TodoModel()
        self.load()
        self.todoView.setModel(self.model)
        self.addButton.pressed.connect(self.add)
        self.deleteButton.pressed.connect(self.delete)
        self.completeButton.pressed.connect(self.complete)

    def add(self):
        '''
        Add an item to todo list, getting the text from the QLineEdit
        toto Edit and the clearing it.
        '''
        text = self.todoEdit.text()
        if text:
            self.model.todos.append((False, text))
            self.model.layoutChanged.emit()
            self.todoEdit.clear()
            self.save()

    def delete(self):
        indexes = self.todoView.selectedIndexes()
        if indexes:
            index = indexes[0]
            del self.model.todos[index.row()]
            self.model.layoutChanged.emit()
            self.todoView.clearSelection()
            self.save()

    def complete(self):
        indexes = self.todoView.selectedIndexes()
        if indexes:
            index = indexes[0]
            row = index.row()
            status, text = self.model.todos[row]
            self.model.todos[row] = (True, text)
            self.model.dataChanged.emit(index, index)
            self.todoView.clearSelection()
            self.save()

    def load(self):
        try:
            with open(curData, "r") as f:
                self.model.todos = json.load(f)
        except Exception:
            pass
        

    def save(self):
        with open(curData, "w") as f:
            json.dump(self.model.todos, f)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MainWindow()
    win.show()
    app.exec_()


