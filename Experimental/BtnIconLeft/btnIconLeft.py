import sys
from PyQt5 import QtCore, QtGui, QtWidgets


class ProxyStyle(QtWidgets.QProxyStyle):
    def drawControl(self, element, option, painter, widget=None):
        if element == QtWidgets.QStyle.CE_PushButtonLabel:
            icon = QtGui.QIcon(option.icon)
            option.icon = QtGui.QIcon()
        super(ProxyStyle, self).drawControl(element, option, painter, widget)
        if element == QtWidgets.QStyle.CE_PushButtonLabel:
            if not icon.isNull():
                iconSpacing = 4
                mode = (
                    QtGui.QIcon.Normal
                    if option.state & QtWidgets.QStyle.State_Enabled
                    else QtGui.QIcon.Disabled
                )
                if (
                    mode == QtGui.QIcon.Normal
                    and option.state & QtWidgets.QStyle.State_HasFocus
                ):
                    mode = QtGui.QIcon.Active
                state = QtGui.QIcon.Off
                if option.state & QtWidgets.QStyle.State_On:
                    state = QtGui.QIcon.On
                window = widget.window().windowHandle() if widget is not None else None
                pixmap = icon.pixmap(window, option.iconSize, mode, state)
                pixmapWidth = pixmap.width() / pixmap.devicePixelRatio()
                pixmapHeight = pixmap.height() / pixmap.devicePixelRatio()
                iconRect = QtCore.QRect(
                    QtCore.QPoint(), QtCore.QSize(pixmapWidth, pixmapHeight)
                )
                iconRect.moveCenter(option.rect.center())
                iconRect.moveLeft(option.rect.left() + iconSpacing)
                iconRect = self.visualRect(option.direction, option.rect, iconRect)
                iconRect.translate(
                    self.proxy().pixelMetric(
                        QtWidgets.QStyle.PM_ButtonShiftHorizontal, option, widget
                    ),
                    self.proxy().pixelMetric(
                        QtWidgets.QStyle.PM_ButtonShiftVertical, option, widget
                    ),
                )
                painter.drawPixmap(iconRect, pixmap)


if __name__ == "__main__":

    app = QtWidgets.QApplication(sys.argv)
    app.setStyle('fusion')
    proxy_style = ProxyStyle(app.style())
    app.setStyle(proxy_style)

    w = QtWidgets.QWidget()
    lay = QtWidgets.QVBoxLayout(w)
    icons = [
        app.style().standardIcon(standardIcon)
        for standardIcon in (
            QtWidgets.QStyle.SP_MediaPlay,
            QtWidgets.QStyle.SP_MediaPause,
            QtWidgets.QStyle.SP_MediaSeekBackward,
            QtWidgets.QStyle.SP_MediaSeekForward,
        )
    ]
    for text, icon in zip("Play Pause Backward Forward".split(), (icons)):
        button = QtWidgets.QPushButton(text)
        button.setIcon(icon)
        lay.addWidget(button)
    w.show()
    sys.exit(app.exec_())