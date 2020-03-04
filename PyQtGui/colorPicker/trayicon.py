from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import (QApplication, QMainWindow, QMenu, QSystemTrayIcon)

import os, sys

def getIcon(name):
    curpath = os.path.dirname(__file__)
    iconsPath = os.path.join(curpath, "images")
    return QIcon(os.path.join(iconsPath, name + ".png"))

class App(QMainWindow):
    def __init__(self, parent=None):
        super(App, self).__init__(parent)

        # Load UI from file
        # uic.loadUi("app.ui", self)

        # Or write your entire UI in code
        self.setFixedSize(640, 480)

        # SysTray Icon
        self.tray = QSystemTrayIcon(self)

        # Check if System supports STray icons
        if self.tray.isSystemTrayAvailable():
            self.tray.setIcon(getIcon("color"))

            # Context Menu
            ctmenu = QMenu()
            actionshow = ctmenu.addAction("Show/Hide")
            actionshow.triggered.connect(lambda: self.hide() if self.isVisible() else self.show())
            actionquit = ctmenu.addAction("Quit")
            actionquit.triggered.connect(self.close)

            self.tray.setContextMenu(ctmenu)
            self.tray.show()
        else:
            # Destroy unused var
            self.tray = None

        # Show App
        self.show()

if __name__ == "__main__":
    application = QApplication(sys.argv)
    application.setApplicationName("App Name")
    application.setApplicationVersion("1.1.1.1.1")
    application.setOrganizationName("dev name")

    win = App()
    sys.exit(application.exec_())