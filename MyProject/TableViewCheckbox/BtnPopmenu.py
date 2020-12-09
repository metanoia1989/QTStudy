import sys
# from PyQt5.QtCore import 
from PyQt5.QtWidgets import QApplication, QMenu, QMainWindow, QPushButton


class Main(QMainWindow):
    def __init__(self, parent=None):
        super(Main, self).__init__(parent)
        pushbutton = QPushButton('Popup Button')
        menu = QMenu()
        menu.addAction('This is Action 1', self.Action1)
        menu.addAction('This is Action 2', self.Action2)
        pushbutton.setMenu(menu)
        self.setCentralWidget(pushbutton)

    def Action1(self):
        print('You selected Action 1')

    def Action2(self):
        print('You selected Action 2')


if __name__ == '__main__':

    app = QApplication(sys.argv)
    main = Main()
    main.show()
    app.exec_()