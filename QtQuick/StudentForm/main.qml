import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("学生信息表单")
    width: 500
    height: 320
    visible: true

    MainForm {
        anchors.fill: parent
        submit.onClicked: { 	// 单击提交按钮执行的事件
            var hobbyText = "";	// 存放学生兴趣爱好的内容
            for(var i=0; i<7; i++) {
                // 生成学生兴趣爱好的文本
                var child = hobby.children[i]
                hobbyText += child.checked?(child.text + "、"):"";
            }
            if (hobby.children[7].checked) { // 其他复选框被选中
                hobbyText += "...";
            }
            // 最终生成的完整学生信息
            details.text = "我的名字叫" + name.text + ", 是个" + age.text + "岁" + sex.current.text + "生，所学专业是" + spec.currentText + "，业务喜欢" + hobbyText;
        }
    }
}
