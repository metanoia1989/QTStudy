#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import sys
import urllib.request
import json
from pathlib import Path

from PySide6.QtQuick import QQuickView
from PySide6.QtCore import QStringListModel, QUrl
from PySide6.QtGui import QGuiApplication


if __name__ == "__main__":

    url = "http://country.io/names.json"
    res = urllib.request.urlopen(url)
    data = json.loads(res.read().decode("utf-8"))

    data_list = list(data.values())
    data_list.sort()
    
    app = QGuiApplication(sys.argv)
    view = QQuickView()
    view.setResizeMode(QQuickView.SizeRootObjectToView)
    
    my_model = QStringListModel()
    my_model.setStringList(data_list)
    view.setInitialProperties({"myModel": my_model})
    
    qml_file = Path(__file__).parent / "view.qml"
    view.setSource(QUrl.fromLocalFile(str(qml_file.resolve())))
    
    if view.status() == QQuickView.Error:
        sys.exit(-1)
        
    view.show()
    
    app.exec()
    del view