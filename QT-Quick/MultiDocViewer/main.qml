import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import org.qtproject.easybooks 1.0

ApplicationWindow {
    id: main
    visible: true
    width: 640
    height: 480
    minimumWidth: 400
    minimumHeight: 300
    title: htmldoc.htmlTitle + "- 多功能文档查看器"
    property color textBackgroundColor: "black"
    property color textColor: "white"

    Action {
        id: htmlOpenAction
        iconSource: "images/filehtml.png"
        iconName: "html-open"
        text: "打开网页"
        onTriggered: htmlDlg.open()
    }

    Action {
        id: txtOpenAction
        iconSource: "images/filetext.png"
        iconName: "text-open"
        text: "打开文本"
        onTriggered: txtDlg.open()
    }

    Action {
        id: imgOpenAction
        iconSource: "images/fileimage.png"
        iconName: "image-open"
        text: "打开图片"
        onTriggered: imgDlg.open()
    }

    Action {
        id: cutAction
        text: "剪切"
        shortcut: "Ctrl+X"
        iconSource: "images/editcut.png"
        iconName: "edit-cut"
        enabled: false
        onTriggered: textArea.cut()
    }

    Action {
        id: copyAction
        text: "赋值"
        shortcut: "Ctrl+C"
        iconSource: "images/editcopy.png"
        iconName: "edit-copy"
        enabled: false
        onTriggered: textArea.copy()
    }

    Action {
        id: pasteAction
        text: "粘贴"
        shortcut: "Ctrl+V"
        iconSource: "images/editpaste.png"
        iconName: "edit-paste"
        enabled: false
        onTriggered: textArea.paste()
    }

    Action {
        id: imgZoominAction
        iconSource: "images/zoomin.png"
        iconName: "image-zoomin"
        text: "放大图片"
        enabled: false
        onTriggered: {
            imageArea.scale += 0.1
            if (imageArea.scale < 3) {
                imageArea.scale = 1;
            }
        }
    }

    Action {
        id: imgZoomoutAction
        iconSource: "images/zoomout.png"
        iconName: "image-zoomout"
        text: "缩小图片"
        enabled: false
        onTriggered: {
            imageArea.scale -= 0.1
            if (imageArea.scale < 0.1) {
                imageArea.scale = 1;
            }
        }
    }

    Action {
        id: imgRotaleftAction
        iconSource: "images/rotaleft.png"
        iconName: "image-rotaleft"
        text: "逆时针旋转"
        enabled: false
        onTriggered: {
            imageArea.rotation -= 45
        }
    }

    Action {
        id: imgRotarightAction
        iconSource: "images/rotaright.png"
        iconName: "image-rotaright"
        text: "顺时针旋转"
        enabled: false
        onTriggered: {
            imageArea.rotation += 45
        }
    }

    menuBar: MenuBar {
        Menu {
            title: "文档"
            MenuItem {
                text: "文本..."
                action: txtOpenAction
            }
            MenuItem {
                text: "网页..."
                action: htmlOpenAction
            }
            MenuItem {
                text: "图片..."
                action: imgOpenAction
            }
            MenuSeparator { }
            MenuItem {
                text: "退出"
                onTriggered: Qt.quit()
            }
        }
        Menu {
            title: "编辑"
            MenuItem { action: copyAction }
            MenuItem { action: cutAction }
            MenuItem { action: pasteAction }
        }
        Menu {
            title: "图像"
            MenuItem {
                text: "放大"
                action: imgZoominAction
            }
            MenuItem {
                text: "缩小"
                action: imgZoomoutAction
            }
            MenuSeparator { }
            MenuItem {
                text: "向左旋转"
                action: imgRotaleftAction
            }
            MenuItem {
                text: "向右旋转"
                action: imgRotarightAction
            }
        }
        Menu {
            title: "帮助"
            MenuItem {
                text: "关于..."
                onTriggered: aboutBox.open()
            }
        }
    }

    toolBar: ToolBar {
        id: mainToolBar
        width: parent.width
        RowLayout {
            anchors.fill: parent
            spacing: 0
            ToolButton { action: htmlOpenAction }

            ToolButton { action: txtOpenAction }
            ToolButton { action: copyAction }
            ToolButton { action: cutAction }
            ToolButton { action: pasteAction }

            ToolButton { action: imgOpenAction }
            ToolButton { action: imgRotaleftAction }
            ToolButton { action: imgRotarightAction }
            ToolButton { action: imgZoominAction }
            ToolButton { action: imgZoomoutAction }

            Item { Layout.fillWidth: true }
        }

    }

    Item {
        id: centralArea
        anchors.fill: parent
        visible: true
        property var current: htmlArea	// 当前显示的区域元素

        BusyIndicator {
            id: busy
            anchors.centerIn: parent
            running: false
            z: 3
        }

        TextArea {	// 主显示区元素
            id: htmlArea
            anchors.fill: parent
            readOnly: true
            frameVisible: false
            baseUrl: "qrc:/"
            text: htmldoc.text
            textFormat: Qt.RichText
        }

        TextArea {	// 主显示区元素
            id: textArea
            anchors.fill: parent
            visible: false
            frameVisible: false
            wrapMode: TextEdit.WordWrap
            font.pointSize: 12
            text: textdoc.text
            style: TextAreaStyle {
                backgroundColor: main.textBackgroundColor
                textColor: main.textColor
                selectedTextColor: "red"
                selectionColor: "aqua"	// 水绿色
            }
            Component.onCompleted: forceActiveFocus()	// 自动获取焦点
        }

        Image {
            id: imageArea
            anchors.fill: parent
            visible: false
            asynchronous: true
            fillMode: Image.PreserveAspectFit
            onStateChanged: {
                if (status === Image.Loading) {	// 正在加载大图片时显现忙等待标志
                busy.running = true;
                } else if (status === Image.Ready ) {	// 载入完成
                busy.running = false;
                } else if (status === Image.Error) {	// 载入图片出错
                busy.running = false;
                mainStatusBar.text = "图片无法显示"
                }
            }
        }
    }

    statusBar: Rectangle {
        id: mainStatusBar
        color: "lightgray"
        implicitHeight: 30
        width: parent.width
        property alias text: status.text
        Text {
            id: status
            anchors.fill: parent
            anchors.margins: 4
            font.pointSize: 12
        }
    }


    FileDialog {
        id: htmlDlg
        title: "打开网页"
        nameFilters: ["网页 (*.htm *html *mht)"]	// 限定只可选择网页格式的文件
        onAccepted: {
            htmldoc.fileUrl = fileUrl;
            var filepath = String(fileUrl);
            mainStatusBar.text = filepath.slice(8);	// 状态栏同步显示当前打开的网页路径
            centralArea.current = htmlArea;	// 设置htmlArea为当前主显示区
            /* 控制各显示区元素的显隐状态 */
            textArea.visible = false;
            imageArea.visible = false;
            htmlArea.visible = true;
            mian.title = htmldoc.htmlTitle + "- 多工能文档查看器";	// 设置主窗口标题
            /* 设置系统各功能项的可用性 */
            copyAction.enabled = false;
            cutAction.enabled = false;
            pasteAction.enabled = false;
            imgRotaleftAction.enabled = false;
            imgRotarightAction.enabled = false
            imgZoominAction.enabled = false;
            imgZoomoutAction.enabled = false;
        }
    }

    FileDialog {
        id: txtDlg
        title: "打开文本"
        nameFilters: ["文本文件 (*.txt)"]	// 限定只可选择文本文件
        onAccepted: {
            htmldoc.fileUrl = fileUrl;
            var filepath = String(fileUrl);
            mainStatusBar.text = filepath.slice(8);	// 状态栏同步显示当前打开的网页路径
            centralArea.current = textArea;	// 设置textArea为当前主显示区
            /* 控制各显示区元素的显隐状态 */
            imageArea.visible = false;
            htmlArea.visible = false;
            textArea.visible = true;
            mian.title = textdoc.textTitle + "- 多工能文档查看器";	// 设置主窗口标题
            /* 设置系统各功能项的可用性 */
            copyAction.enabled = true;
            cutAction.enabled = true;
            pasteAction.enabled = true;
            imgRotaleftAction.enabled = false;
            imgRotarightAction.enabled = false
            imgZoominAction.enabled = false;
            imgZoomoutAction.enabled = false;
        }
    }

    FileDialog {
        id: imgDlg
        title: "打开图片"
        nameFilters: ["图片文件 (*.jpg *.png *.gif *.bmp *.ico)"]
        onAccepted: {
            var filepath = String(fielUrl);
            mainStatusBar.text = filepath.slice(8);
            /* 以下为截图图片文件名的操作 */
            var dot = filepath.lastIndexOf(".");
            var sep = filepath.lastIndexOf("/");
            if (dot > sep) {
                var filename = filepath.substring(sep + 1);
                main.processFile(fileUrl, filename);
            } else {
                mainStatusBar.text = "出错！MultiDocViewer 不支持此格式的图片！";
            }
        }
    }

    MessageDialog {
        id: aboutBox
        title: "关于"
        text: "MultiDocViewer 1.1 \n这是一个多功能文档查看器，可打开文本、网页、图片等多种类型的文档 \n使用 Qt Quick Controls 开发而成。 \nCopyright © 2010 - 2017 easybooks. 版权所有"
        icon: StandardIcon.Information
    }

    HtmlHandler {
        id: htmldoc
        Component.onCompleted: htmldoc.fileUrl = "qrc:/easybooks.htm"
    }

    TextHandler {
        id: textdoc
    }

    /* 对图片的处理操作 */
    function processFile(fileUrl, name) {
        /* 控制各显示区元素的显隐状态 */
        if (centralArea.current !== imageArea) {
            if (centralArea.current !== null) {
                centralArea.current.visible = false;
            }
            imageArea.visible = true;
            centralArea.current = imageArea;
        }
        imageArea.source = fileUrl;
        main.title = name + " - 多功能文档查看器";
        /* 设置系统各功能项的可用性 */
        copyAction.enabled = false
        cutAction.enabled = false;
        pasteAction.enabled = false;
        imgRotaleftAction.enabled = true;
        imgRotarightAction.enabled = true;
        imgZoominAction.enabled = true;
        imgZoomoutAction.enabled = true;
    }
}
