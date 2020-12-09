# -*- encoding: utf-8 -*-
'''
@Contact :   obj2008@foxmail.com
2020/5/13 12:48 PM   obj2008      1.0         None
--------------------------------------------------------
'''
import sys

from PyQt5.QtWidgets import QApplication, QWidget,  QVBoxLayout,  QTableWidget, QCheckBox, QHeaderView, QStyle, QStyleOptionButton, QTableWidgetItem
from PyQt5.QtCore import Qt, pyqtSignal, QRect

# 表头字段，全局变量
header_field = ['全选', '姓名', '年龄', '籍贯']
# 用来装行表头所有复选框 全局变量
all_header_combobox = []


class CheckBoxHeader(QHeaderView):
    """自定义表头类"""

    # 自定义 复选框全选信号
    select_all_clicked = pyqtSignal(bool)
    # 这4个变量控制列头复选框的样式，位置以及大小
    _x_offset = 0
    _y_offset = 0
    _width = 20
    _height = 20

    def __init__(self, orientation=Qt.Horizontal, parent=None):
        super(CheckBoxHeader, self).__init__(orientation, parent)
        self.isOn = False

    def paintSection(self, painter, rect, logicalIndex):
        painter.save()
        super(CheckBoxHeader, self).paintSection(painter, rect, logicalIndex)
        painter.restore()

        self._y_offset = int((rect.height() - self._width) / 2.)

        if logicalIndex == 0:
            option = QStyleOptionButton()
            option.rect = QRect(rect.x() + self._x_offset, rect.y() + self._y_offset, self._width, self._height)
            option.state = QStyle.State_Enabled | QStyle.State_Active
            if self.isOn:
                option.state |= QStyle.State_On
            else:
                option.state |= QStyle.State_Off
            self.style().drawControl(QStyle.CE_CheckBox, option, painter)

    def mousePressEvent(self, event):
        index = self.logicalIndexAt(event.pos())
        if 0 == index:
            x = self.sectionPosition(index)
            if x + self._x_offset < event.pos().x() < x + self._x_offset + self._width and self._y_offset < event.pos().y() < self._y_offset + self._height:
                if self.isOn:
                    self.isOn = False
                else:
                    self.isOn = True
                    # 当用户点击了行表头复选框，发射 自定义信号 select_all_clicked()
                self.select_all_clicked.emit(self.isOn)

                self.updateSection(0)
        super(CheckBoxHeader, self).mousePressEvent(event)

    # 自定义信号 select_all_clicked 的槽方法
    def change_state(self, isOn):
        # 如果行表头复选框为勾选状态
        if isOn:
            # 将所有的复选框都设为勾选状态
            for i in all_header_combobox:
                i.setCheckState(Qt.Checked)
        else:
            for i in all_header_combobox:
                i.setCheckState(Qt.Unchecked)


class TableDemo(QWidget):
    """窗口类"""

    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('这是QTableWidget类行表头添加复选框全选功能')
        self.resize(400, 300)

        # 垂直布局
        self.vlayout = QVBoxLayout(self)
        self.vlayout.setAlignment(Qt.AlignTop)  # 设置 垂直布局 的对齐方式
        self.setTableWidget()  # 设置表格

        self.show()

    # 设置表格
    def setTableWidget(self):
        # 表格控件
        self.tablewidget = QTableWidget(3,4)        # 3行4列
        self.tablewidget.setFixedWidth(300)         # 表格宽度
        self.setTableHeaderField()               # 设置表格行表头字段
        self.tablewidget.setAlternatingRowColors(True)      # 交替行颜色
        self.vlayout.addWidget(self.tablewidget)

    # 设置行表头字段
    def setTableHeaderField(self):

        self.tablewidget.setColumnCount(len(header_field))   # 设置列数
        for i in range(len(header_field)-1):
            header_item = QTableWidgetItem(header_field[i])

            checkbox = QCheckBox()
            # 将所有的复选框都添加到 全局变量 all_header_combobox 中
            all_header_combobox.append(checkbox)
            # 为每一行添加复选框
            self.tablewidget.setCellWidget(i,0,checkbox)

        header = CheckBoxHeader()               # 实例化自定义表头
        self.tablewidget.setHorizontalHeader(header)            # 设置表头
        self.tablewidget.setHorizontalHeaderLabels(header_field)        # 设置行表头字段
        self.tablewidget.setColumnWidth(0,60)       # 设置第0列宽度
        header.select_all_clicked.connect(header.change_state)        # 行表头复选框单击信号与槽

    # 设置表格内容，根据实际情况设置即可
    def setTableContents(self):
        pass


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ta = TableDemo()
    sys.exit(app.exec_())