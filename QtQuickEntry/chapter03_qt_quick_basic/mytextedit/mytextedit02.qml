import QtQuick 2.2
Flickable {
    id: flick
    width: 300; height: 200
    contentWidth: edit.paintedWidth
    contentHeight: edit.paintedHeight
    clip: true

    function ensureVisible(r) {
        if (contentX >= r.x) {
            contentX = r.x;
        } else if (contentX + width <= r.x + r.width) {
            contentX = r.x + r.width - width;
        }
        if (contentY >= r.y) {
            contentY = r.y;
        } else if (contentY + height <= r.y + r.height) {
            contentY = r.y + r.height - height;
        }
    }

    TextEdit {
        id: edit
        width: flick.width
        height: flick.height
        focus: true
        wrapMode: TextEdit.Wrap
        onCursorRectangleChanged:
            flick.ensureVisible(cursorRectangle)
    }

    
    Rectangle {
        id: scrollbar
        anchors.fill: flick.right
        y: flick.visibleArea.yPosition * flick.height 
        width: 10
        height: flick.visibleArea.heightRatio * flick.height
        color: "lightgrey"
    }
    
}