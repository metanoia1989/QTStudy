# coding: utf-8

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

class FontdialogDemo(QWidget):
    def __init__(self, parent=None):
        super(FontdialogDemo, self).__init__(parent)

        layout = QVBoxLayout()
        self.fontButton = QPushButton("choos font")
        self.fontButton.clicked.connect(self.getFont)
        layout.addWidget(self.fontButton)

        self.fontLabel = QLabel("Hello, 测试字体例子")
        layout.addWidget(self.fontLabel)

        self.setLayout(layout)
        self.setWindowTitle("Font Dialog例子")

    def getFont(self):
        font, ok = QFontDialog.getFont()
        if ok:
            self.fontLabel.setFont(font)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    demo = FontdialogDemo()
    demo.show()
    sys.exit(app.exec_())
