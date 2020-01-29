# conding: utf-8
'''
气泡提示
'''
import sys
from PyQt5.QtWidgets import QWidget, QToolTip, QApplication, QPushButton
from PyQt5.QtGui import QFont

class Winform(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        QToolTip.setFont(QFont('SansSerif', 10))
        self.setToolTip("这是一个<p>气泡提示</p>")
        self.setGeometry(200, 300, 400, 400)
        self.setWindowTitle("气泡提示demo")

        btn = QPushButton('按钮', self)
        btn.setToolTip("这是一个<b>按钮</b>组件")
        btn.resize(btn.sizeHint())
        btn.move(50, 50)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = Winform()
    win.show()
    sys.exit(app.exec_())