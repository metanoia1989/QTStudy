#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from PyQt5 import QtNetwork
from PyQt5.QtCore import QCoreApplication, QUrl
import sys

class Example:

    def __init__(self):

        self.doRequest()


    def doRequest(self):

        url = 'http://webcode.me'
        req = QtNetwork.QNetworkRequest(QUrl(url))

        self.nam = QtNetwork.QNetworkAccessManager()
        self.nam.finished.connect(self.handleResponse)
        self.nam.get(req)


    def handleResponse(self, reply):

        er = reply.error()

        if er == QtNetwork.QNetworkReply.NoError:

            bytes_string = reply.readAll()
            print(str(bytes_string, 'utf-8'))

        else:
            print("Error occured: ", er)
            print(reply.errorString())

        QCoreApplication.quit()


def main():

    app = QCoreApplication([])
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()