# coding: utf-8

'''
坐标系统显示
'''

from PyQt5.QtWidgets import QApplication, QWidget, QPushButton
import sys

app = QApplication(sys.argv)
widget = QWidget()
btn = QPushButton(widget)
btn.setText("按钮")
# 以QWidget左上角为(0, 0)点
btn.move(20, 20)
widget.resize(300, 200)
# 以屏幕左上角为(0, 0)点
widget.move(250, 200)

widget.setWindowTitle("PyQt坐标系统例子")
widget.show()
print("#1 QWidget")
print("widget.x()=%d" % widget.x())
print("widget.y()=%d" % widget.y())
print("widget.width()=%d" % widget.width())
print("widget.height()=%d" % widget.height())

print("#2 QWidget.geomeetry")
print("widget.geometry().x()=%d" % widget.geometry().x())
print("widget.geometry().y()=%d" % widget.geometry().y())
print("widget.geometry().width()=%d" % widget.geometry().width())
print("widget.geometry().height()=%d" % widget.geometry().height())
print("widget.size().width()=%d" % widget.size().width())
print("widget.size().height()=%d" % widget.size().height())

print("#3 QWidget.frameGeometry")
print("widget.frameGeometry().width()=%d" % widget.frameGeometry().width())
print("widget.frameGeometry().height()=%d" % widget.frameGeometry().height())
print("widget.pos().x()=%d" % widget.pos().x())
print("widget.pos().y()=%d" % widget.pos().y())

sys.exit(app.exec_())
