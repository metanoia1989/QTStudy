#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from PyQt5 import QtNetwork
from PyQt5.QtNetwork import QNetworkAccessManager, QNetworkRequest
from PyQt5.QtCore import QCoreApplication, QUrl, QByteArray
import sys

class Example:

    def __init__(self):

        self.doRequest()


    def doRequest(self):
        mobile = "13593871052"
        url = "http://azxfsite.test/extra_query.php"
        request = QNetworkRequest(QUrl(url))
        request.setHeader(QNetworkRequest.ContentTypeHeader, "application/x-www-form-urlencoded")
        data = QByteArray() 
        data.append("action=student_info")
        data.append("&mobile={0}".format(mobile))

        self.manager = QNetworkAccessManager()
        self.manager.finished.connect(self.handleResponse)
        self.manager.post(request, data)


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