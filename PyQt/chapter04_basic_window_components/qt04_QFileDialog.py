# coding: utf-8

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

class filedialogDemo(QWidget):
    def __init__(self, parent=None):
        super(filedialogDemo, self).__init__(parent)

        layout = QVBoxLayout()
        self.btn = QPushButton("加载图片")
        self.btn.clicked.connect(self.getfile)
        layout.addWidget(self.btn)

        self.le = QLabel("")
        layout.addWidget(self.le)

        self.btn1 = QPushButton("加载文本文件")
        self.btn1.clicked.connect(self.getfiles)
        layout.addWidget(self.btn1)

        self.contents = QTextEdit()
        layout.addWidget(self.contents)

        self.setLayout(layout)
        self.setWindowTitle("File Dialog例子")

    def getfile(self):
        fname, _ = QFileDialog.getOpenFileName(self, "Open file", "c:\\", "Image files (*.jpg *.gif)")
        self.le.setPixmap(QPixmap(fname))

    def getfiles(self):
        dlg = QFileDialog()
        dlg.setFileMode(QFileDialog.AnyFile)
        dlg.setFilter(QDir.Files)

        if dlg.exec_():
            filenames = dlg.selectedFiles()
            with open(filenames[0], "r", encoding="utf-8") as f:
                data = f.read()
                self.contents.setText(data)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    demo = filedialogDemo()
    demo.show()
    sys.exit(app.exec_())
