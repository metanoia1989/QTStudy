#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtWebEngineWidgets import *
from PyQt5.QtPrintSupport import *

import os, sys
from os.path import join, dirname

icons_path = join(dirname(__file__), "icons") 


class AboutDialog(QDialog):
    def __init__(self, *args, **kwargs):
        super(AboutDialog, self).__init__(*args, **kwargs)

        QBtn = QDialogButtonBox.Ok
        self.buttonBox = QDialogButtonBox(QBtn)
        self.buttonBox.accepted.connect(self.accept)
        self.buttonBox.rejected.connect(self.reject)

        layout = QVBoxLayout()

        title = QLabel("Mozarella Ashbadger")
        font = title.font()
        font.setPointSize(20)
        title.setFont(font)

        layout.addWidget(title)

        logo = QLabel()
        logo.setPixmap(QPixmap(join(icons_path, "ma-icon-128.png")))
        layout.addWidget(logo)

        layout.addWidget(QLabel("Version 23.25.211.233232"))
        layout.addWidget(QLabel("Copyright 2015 Mozarella Inc."))

        for i in range(0, layout.count()):
            layout.itemAt(i).setAlignment(Qt.AlignHCenter)
        
        layout.addWidget(self.buttonBox)

        self.setLayout(layout)

class MainWindow(QMainWindow):
    def __init__(self, *args, **kwargs):
        super(MainWindow, self).__init__(*args, **kwargs)

        self.browser = QWebEngineView()
        self.browser.setUrl(QUrl("https://www.baidu.com"))
        self.setCentralWidget(self.browser)

        # tag::navigationSignals[]
        self.browser.urlChanged.connect(self.update_urlbar)
        self.browser.loadFinished.connect(self.update_title)
        # end::navigationSignals[]

        # tag::navigation1[]
        navtb = QToolBar("Navigation")
        navtb.setIconSize(QSize(16, 16))
        self.addToolBar(navtb)

        back_btn = QAction(QIcon(join(icons_path, "arrow-180.png")), "Back", self)
        back_btn.setStatusTip("Back to previous page")
        back_btn.triggered.connect(self.browser.back)
        navtb.addAction(back_btn)
        # end::navigation1[]

        # tag::navigation2[]
        next_btn = QAction(QIcon(join(icons_path, "arrow-000.png")), "Forward", self)
        next_btn.setStatusTip("Forward to next page")
        next_btn.triggered.connect(self.browser.forward)
        navtb.addAction(next_btn)

        reload_btn = QAction(QIcon(join(icons_path, "arrow-circle-315.png")), "Reload", self)
        reload_btn.setStatusTip("Reload page")
        reload_btn.triggered.connect(self.browser.reload)
        navtb.addAction(reload_btn)

        home_btn = QAction(QIcon(join(icons_path, "home.png")), "Home", self)
        home_btn.setStatusTip("Go home")
        home_btn.triggered.connect(self.navigate_home)
        navtb.addAction(home_btn)
        # end::navigation2[]

        navtb.addSeparator()

        # tag::navigation3[]
        self.httpsicon = QLabel()
        self.httpsicon.setPixmap(QPixmap(join(icons_path, "lock-nossl.png")))
        navtb.addWidget(self.httpsicon)

        self.urlbar = QLineEdit()
        self.urlbar.returnPressed.connect(self.navigate_to_url)
        navtb.addWidget(self.urlbar)

        stop_btn = QAction(QIcon(join(icons_path, "cross-circle.png")), "Stop", self)
        stop_btn.setStatusTip("Stop loading current page")
        stop_btn.triggered.connect(self.browser.stop)
        navtb.addAction(stop_btn)
        # end::navigation3[]

        self.menuBar().setNativeMenuBar(False)
        self.statusBar()

        # tag::menuFile[]
        file_menu = self.menuBar().addMenu("&File")

        open_file_action = QAction(QIcon(join(icons_path, "disk--arrow.png")), "Open file...", self)
        open_file_action.setStatusTip("Open from file")
        open_file_action.triggered.connect(self.open_file)
        file_menu.addAction(open_file_action)

        save_file_action = QAction(QIcon(join(icons_path, "disk--pencil.png")), "Save Page As...", self)
        save_file_action.setStatusTip("Save current page to file")
        save_file_action.triggered.connect(self.save_file)
        file_menu.addAction(save_file_action)
        # end::menuFile[]

        # tag::menuPrint[]
        print_action = QAction(QIcon(join(icons_path, "printer.png")), "Print...", self)
        print_action.setStatusTip("Print current page")
        print_action.triggered.connect(self.print_page)
        file_menu.addAction(print_action)
        # end::menuPrint[]

        # tag::menuHelp[]
        help_menu = self.menuBar().addMenu("&Help")

        about_action = QAction(QIcon(join(icons_path, "question.png")), "About Mozarella Ashbadger", self)
        about_action.setStatusTip("Find out more about Mozarella Ashbadger")
        about_action.triggered.connect(self.about)
        help_menu.addAction(about_action)

        navigate_mozarella_action = QAction(QIcon(join(icons_path, "lifebuoy.png")), "Mozarella Ashbadger Homepage", self)
        navigate_mozarella_action.setStatusTip("Go to Mozarella Ashbadger")
        navigate_mozarella_action.triggered.connect(self.navigate_mozarella)
        help_menu.addAction(navigate_mozarella_action)
        # end::menuHelp[]

        # tag::tabWidget[]
        # end::tabWidget[]

        self.show()
        self.setWindowIcon(QIcon(join(icons_path, "ma-icon-64.png")))

    # tag::navigationTitle[]
    def update_title(self):
        title = self.browser.page().title()
        self.setWindowTitle("%s - Mozarella Ashbadger" % title)
    # end::navigationTitle[]

    # tag::menuHelpfn[]
    def navigate_mozarella(self):
        self.browser.setUrl(QUrl("https://www.udemy.com/522076"))

    def about(self):
        dlg = AboutDialog()
        dlg.exec_()
    # add::menuHelpfn[]

    # tag::menuFilefnOpen[]
    def open_file(self):
        filename, _ = QFileDialog.getOpenFileName(self, "Open file", "",
                        "Hypertext Markup Language (*.htm *.html);;"
                        "All files (*.*)")
        if filename:
            with open(filename, "r", encoding="utf-8") as f:
                html = f.read()
            self.browser.setHtml(html)
            self.urlbar.setText(filename)
    # end::menuFilefnOpen[]

    # tag::menuFilefnSave[]
    def save_file(self):
        filename, _ = QFileDialog.getSaveFileName(self, "Save Page As", "",
                        "Hypertext Markup Language (*.htm *.html);;"
                        "All files (*.*)")
        if filename:
            def callback(html):
                with open(filename, "w", encoding="utf-8") as f:
                    f.write(html)

            self.browser.page().toHtml(callback)

    # end::menuFilefnSave[]

    # tag::menuPrintfn[]
    def print_page(self):
        printer = QPrinter()
        dlg = QPrintPreviewDialog(printer, self.browser)
        dlg.paintRequested.connect(self.print_document)
        dlg.exec_()

    def print_document(self):
        pass

    # end::menuPrintfn[]

    # tag::navigationHome[]
    def navigate_home(self):
        self.browser.setUrl(QUrl("https://www.baidu.com"))
    # end::navigationHome[]

    # tag::navigationUrl[]
    def navigate_to_url(self):
        q = QUrl(self.urlbar.text())
        if q.scheme() == "":
            q.setScheme("http")
        self.browser.setUrl(q)
    # end::navigationUrl[]

    # tag::navigationUrlBar[]
    def update_urlbar(self, q):
        if q.scheme() == "https":
            self.httpsicon.setPixmap(QPixmap(join(icons_path, "lock-ssl.png")))
        else:
            self.httpsicon.setPixmap(QPixmap(join(icons_path, "lock-nossl.png")))
        self.urlbar.setText(q.toString())
        self.urlbar.setCursorPosition(0)
    # end::navigationUrlBar[]

if __name__ == "__main__":
    app = QApplication(sys.argv)
    app.setApplicationName("Mozarella Ashbadger")
    app.setOrganizationName("Mozarella")
    app.setOrganizationDomain("mozaralla.org")
    win = MainWindow()
    app.exec_()