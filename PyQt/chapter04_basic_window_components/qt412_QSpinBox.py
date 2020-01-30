# coding: utf-8

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

class spindemo(QWidget):
    def __init__(self, parent=None):
        super(spindemo, self).__init__(parent)
        self.setWindowTitle("SpinBox例子")
        self.resize(300, 100)

        layout = QVBoxLayout()
        self.l1 = QLabel("current value: ")
        self.l1.setAlignment(Qt.AlignCenter)
        layout.addWidget(self.l1)

        self.sp = QSpinBox()
        self.sp.valueChanged.connect(self.valuechange)
        layout.addWidget(self.sp)
        
        self.setLayout(layout)

    def valuechange(self):
        self.l1.setText("current change: " + str(self.sp.value()))


if __name__ == "__main__":
    app = QApplication(sys.argv)
    sp = spindemo()
    sp.show()
    sys.exit(app.exec_())