#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton
from PyQt5.QtWebEngineWidgets import QWebEngineView

app = QApplication(sys.argv)
win = QWidget()
win.setWindowTitle("Web页面中的JavaScript与QWebEngineView交互例子")

layout = QVBoxLayout()
win.setLayout(layout)

view = QWebEngineView()
view.setHtml('''
  <html>
    <head>
      <title>A Demo Page</title>

      <script language="javascript">
        // Completes the full-name control and
        // shows the submit button
        function completeAndReturnName() {
          var fname = document.getElementById('fname').value;
          var lname = document.getElementById('lname').value;
          var full = fname + ' ' + lname;

          document.getElementById('fullname').value = full;
          document.getElementById('submit-btn').style.display = 'block';

          return full;
        }
      </script>
    </head>

    <body>
      <form>
        <label for="fname">First name:</label>
        <input type="text" name="fname" id="fname"></input>
        <br />
        <label for="lname">Last name:</label>
        <input type="text" name="lname" id="lname"></input>
        <br />
        <label for="fullname">Full name:</label>
        <input disabled type="text" name="fullname" id="fullname"></input>
        <br />
        <input style="display: none;" type="submit" id="submit-btn"></input>
      </form>
    </body>
  </html>
''')

# 创建一个按钮去调用JavaScript代码
button = QPushButton("设置全名")

def js_callback(result):
    print(result)

def complete_name():
    view.page().runJavaScript('completeAndReturnName();', js_callback)

# 按钮连接 'complete_name' 槽，当点击按钮是会触发信号
button.clicked.connect(complete_name)

layout.addWidget(view)
layout.addWidget(button)

win.show()
sys.exit(app.exec_())