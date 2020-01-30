# coding: utf-8

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

class SliderDemo(QWidget):
    def __init__(self, parent=None):
        super(SliderDemo, self).__init__(parent)
        self.setWindowTitle("QSlider 例子")
        self.resize(300, 100)

        layout = QVBoxLayout()
        self.l1 = QLabel("Hello PyQt5")
        self.l1.setAlignment(Qt.AlignCenter)
        layout.addWidget(self.l1)

        self.s1 = QSlider(Qt.Horizontal) # 水平方向
        self.s1.setMinimum(10)  # 设置最小值
        self.s1.setMaximum(50) # 设置最大值
        self.s1.setSingleStep(3) # 步长
        self.s1.setValue(20) # 设置当前值
        self.s1.setTickInterval(5) # 设置刻度间隔
        self.s1.valueChanged.connect(self.valuechange)
        layout.addWidget(self.s1)

        self.setLayout(layout)

    def valuechange(self):
        print("current slider value=%s" % self.s1.value())
        size = self.s1.value()
        self.l1.setFont(QFont("Arial", size))

if __name__ == "__main__":
    app = QApplication(sys.argv)
    demo = SliderDemo()
    demo.show()
    sys.exit(app.exec_())
