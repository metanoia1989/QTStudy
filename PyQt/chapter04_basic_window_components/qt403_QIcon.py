# conding: utf-8
'''
程序图标
'''

import sys
import os 
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QWidget, QApplication

class Icon(QWidget):
    def __init__(self, parent=None):
        super(Icon, self).__init__(parent)
        self.initUI()

    def initUI(self):
        self.setGeometry(300, 300, 250, 150)
        self.setWindowTitle("演示程序图标例子")
        img = os.path.dirname(os.path.realpath(__file__)) +  os.path.sep + "./images/cartoon1.ico"
        self.setWindowIcon(QIcon(img))

if __name__ == "__main__":
    app = QApplication(sys.argv)
    icon = Icon()
    icon.show()
    sys.exit(app.exec_())