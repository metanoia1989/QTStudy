# coding:utf-8
'''
窗口居中
'''

from PyQt5.QtWidgets import  QDesktopWidget, QApplication, QMainWindow
import sys

class Winform(QMainWindow):
    def __init__(self, parent=None):
        super(Winform, self).__init__(parent)

        self.setWindowTitle("窗口于屏幕居中")
        self.resize(370, 250)
        self.center()

    def center(self):
        '''
        获取中间坐标，然后移动
        '''
        screen = QDesktopWidget().screenGeometry()
        size = self.geometry()
        self.move((screen.width() - size.width())/2, (screen.height() - size.height())/2)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = Winform()
    win.show()
    sys.exit(app.exec_())