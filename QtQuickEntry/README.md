# 说明
这个目录下的代码主要是来自 Qt5 编程入门的示例

## TextField
TextField是一个单行的文本输入框，允许用户输入和编辑单行的文本，对应C++中的QLineEdit。 

TextField继承自TextInput，增加了占位符以及外观的修饰等。 TextField有很多来自 TextInput的函数。比如，可以使用`cut()`、`copy()`和`paste()`这3个函数实现剪贴板的剪贴、复制和粘贴等操作。粘贴之前，可以使用`canPaste`测试是否允许粘贴操作。

与QLineEdit类似，TextField有4种显示模式，使用`echoMode`属性进行设置；其值是一个 enumeration类型，允许的值包括:
* TextInput.Normal: 正常显示输入的内容，为属性默认值；
* TextInput.Password: 密码样式，以黑点或星号显示；
* TextInput.NoEcho: 不显示任何输入；
* TextInput.PasswordEchoOnEdit: 编辑时显示为正常输入的内容，其余情况下则显示为密码样式。

TextField支持输入掩码限制输入的内容。输入掩码使用`inputMask`属性设置，可以利用一些特殊字符指定输入的格式和内容。也可以使用`validator`属性给TextField设置验证器。

TextField使用`placeholderText`属性设置了占位符文本，即当输入内容为空时显示的提示性文本；

TextField包含一个可视项目: background。通过定义这个项目，可以改变TextField的外观。

TextField提供了3个信号: `pressAndHold(mouseEvent event)`、`pressed(MouseEvent event)`以及`released(MouseEvent event)`，分别在鼠标长时间按下鼠标按下以及鼠标释放时发射。
```js
TextField {
    y: 10; width: 200
    placeholderText: qsTr("Please enter a password")
    echoMode: TextInput.PasswordEchoOnEdit
    validator: IntValidator { bottom: 11; top: 20 }
    onAccepted: console.debug(text)
}

TextField {
    id: control
    placeholderText: qsTr("Enter description")
    background: Rectangle {
        implicitWidth: 200; implicitHeight: 40
        color: control.enabled ? "transparent" : "#353637"
        border.color: control.enabled ? "#21be2b" : "transparent"
    }
}
```

## TextArea
TextArea是一个多行的文本输入框，它对应C++中的QTextEdit。

* 与TextField的纯文本不同，TextArea支持富文本显示：通过`textFormat`属性可以设置TextArea直接显示文本内容还是显示富文本。 
* TextArea使用`cut()`、`copy()`和`paste()`这3个函数实现剪贴板的剪贴、复制和粘贴等操作。类似传统桌面程序，
* TextArea可以使用鼠标选择需要操作的文本。不过，这个特性也可以通过设置`selectByMouse`属性为false而关闭。
* 除了鼠标操作，TextArea还支持完全使用QML代码控制文本选择。例如，可以通过设置`selectionStart`和`selectionEnd`两个属性控制TextArea的选择区域，或者使用`selectAll()`、 `selectWord()`这类函数。
* 但是，TextArea本身不能够滚动，如果需要显示滚动条，则需要将TextArea放置在ScrollView中。
* 与TextField类似， TextArea包含一个可视项目: background，通过定义这个项目，可以改变TextArea的外观。
* TextArea同样提供了3个信号: `pressAndHold(mouseEvent event)`、`pressed(MouseEvent event)`以及`released(MouseEvent event)`，分别在鼠标长时间按下鼠标按下以及鼠标释放时发射。
```js
ApplicationWindow {
    visible: true
    width: 250; height: 100
    
    ScrollView {
        anchors.fill: parent
        TextArea {
            text: "TextArea\n..\n..\n..\n..\n..\n..\n..\n..\n..\n..\n..\n.."
        }
    }
}
```

## ComboBox
ComboBox是一种带有下拉选择框的按钮，对应C++中的QComboBox。
* ComboBox可以使用一个字符串数组作为数据模型。ComboBox还可以使用ListModel作为数据模型。
* ListElement有多个属性时，使用textRole指定显示那个属性。
* ComboBox的`currentIndexChanged`信号，下拉选择变化时发射此信号。
* ComboBox的`editable`属性可以设置这个ComboBox是不是可以编辑，将其设置为true，下拉框允许用户编辑数据。
* 使用`selectAll`函数可以全选输入框中的内容。
* 在用户输入时，ComboBox自动显示下拉框中匹配的数据，而且还可以通过`accepted`信号确定是否可以将用户输入的数据添加到下拉框中。在添加新的数据时，需要确定下拉框中没有重复项。
```js
ComboBox {
    width: 200; currentIndex: 2
    textRole: "text"
    model: ListModel {
        id: cbItems
        ListElement { text: "Banana"; color: "Yellow" }
        ListElement { text: "Apple"; color: "Green" }
        ListElement { text: "Cocount"; color: "Brown" }
    }
    onCurrentIndexChanged: {
        console.debug(cbItems.get(currentIndex).text + ","
                      + cbItems.get(currentIndex).color)
    }
}
```

find函数用来查找当前输入的值是不是已经存在；如果不存在，则将其追加到下拉框数据的最后，然后设置下拉框的当前选择项为新增的数据项。
find函数有两个参数，第一个参数是要检索的文本值，第二个参数是匹配方式。目前支持的匹配选项有：
* Qt.Match Exactly: 完全匹配（默认）；
* Qt.MatchRegExp: 使用正则表达式匹配
* Qt.MatchWildcard: 使用通配符匹配；
* Qt.MatchFixedString: 使用固定字符串匹配；
* Qt.MatchStartsWith: 前方匹配；
* Qt.MatchEndsWidth: 后方匹配；
* Qt.MatchContains: 包含匹配；
* Qt.MatchCaseSensitive: 大小写敏感。

可以组合使用上述匹配选项，如Qt.MatchWildcard|Qt.MatchCaseSensitive

当ComboBox允许编辑时，可以使用`validator`属性为文本输入框设置验证器。如果有验证器，在按下回车键时，只有当输入的文本能够通过验证，才会发出 accepted信号。目前，ComboBox接受的验证器包括`IntValidator`、`DoubleValidator`和`RegExpValidator`。

只读属性`acceptableInput`可以获取文本输入框中是否包含可接受的文本。如果设置了验证器，则只有当验证器验证通过时，该输入才会返回true。
ComboBox包含4个可视项目: `background`、`contentItem`、`popup`和`delegate`通过定义这4个项目可 ComboBox以改变的外观。
```js
ComboBox {
    width: 200; currentIndex: 2
    textRole: "text"; editable: true
    validator: RegExpValidator { ... }
    model: ListModel {
        id: cbItems
        ListElement { text: "Banana"; color: "Yellow" }
        ListElement { text: "Apple"; color: "Green" }
        ListElement { text: "Cocount"; color: "Brown" }
    }
    onAccepted: {
        if (find(editText) === -1) {
            model.append({text: editText})
        }
    }
}
```

## SpinBox
SpinBox允许用户通过单击向上、向下的指示按钮或键盘的上下箭头选择一个整数值，对应C++中的QSpinBox。
* 通过将`editable`属性设置为true可以将SpinBox设置为可编辑的，这样，用户就可以在输入框输入文本值，而不仅仅使用按钮选择。 
* SpinBox的可选值范围默认是`[0，100]`，步长为1。 
* SpinBox的值使用`value`属性获取和设置，其范围由`from`和`to`属性进行定义。
* `wrap`属性设置`value`到最大值时，可以直接回到起点。 
* `inputMethodHints`属性用于通知输入法，当前SpinBox可接受的输入内容格式（如是否纯数字等），以便系统选择合适的输入法进行显示。 
* SpinBox提供了两个函数: `increase()`和`decrease()`，分别用于增加SpinBox的`value`值和减少SpinBox的`value`值，其单位改变都是一个步长。
* 当SpinBox的`value`发生改变时，则发射`valueModified()`信号。

虽然SpinBox内部基于整数，但可以自定义SpinBox的显示值，其主要思路是，将内部存储的整型与显示的文本做映射。通过使用`validator`、`valueFromText`和 `textFromValue`可以实现这种自定义。
```js
SpinBox {
    id: levelBox
    from: 0; to: items.length - 1; value: 1
    editable: true
    property var items: ["Small", "Medium", "Large"]
    validator: RegExpValidator {
        regExp: new RegExp("(Small|Medium|Large)", "i")
    }
    textFromValue: (value) => items[value];
    valueFromText: (text) => {
        for (let i=0; i<items.length; ++i) {
            if (item[i].toLowerCase().indexOf(text.toLowerCase()) === 0)
                return i;
        }
        console.log(item[i], levelBox.value)
        return levelBox.value
    }
}
```

SpinBox提供了一个`dislayText`属性，用于获取SpinBox当前显示的文本， `displayText`的值等价于
```js
spinBox.textFromValue(spinBox.value, spinBox.locale);
```

SpinBox提供了两个属性组`up`和`down`，用于获得向上指示符和向下指示符的相关信息。下面是up属性组的具体内容，down分组与此类似:
* up.pressed:bool类型，向上指示符是否按下；
* up.indicator:Item类型，向上指示符的渲染项目；
* up.hovered:bool类型，向上指示符是否滑过；
* up.implicitIndicatorWidth:real类型，上指示符的隐式宽度；
* up.implicitIndicatorHeight:real类型，上指示符的隐式高度。

SpinBox包含4个可视项目: `background`、`contentItem`、`up`指示符和`down`指示符，通过定义这些项目可以改变SpinBox的外观。

## Dial
Dial是一种转盘按钮，常见于传统的音响和工业设备，Dial对应C++中的QDialDial。
* 与SpinBox类似，区别在于SpinBox可以允许用户输入值，而Dial只能使用户通过转盘选择一个值。
* Dial的值使用`value`属性获取和设置，其范围由`from`和`to`属性进行定义。
* `wrap`属性设置转盘到尽头处是否可以直接回到起点。
* `live`属性用于设置转柄被拖动时，转盘是否应当实时更新数值。
* 当转盘转动时，Dial会发出`moved`信号。
* Dial包含两个可视项目: `background`和`handle`，通过定义这两个项目可以改变Dial的外观。
```js
Dial {
    id: control
    value: 40; from: 0; to: 100
    background: Rectangle {
        x: control.width / 2 - width /2;
        y: control.height / 2 - height /2;
        width: Math.max(64, Math.min(control.width, control.height))
        height: width; color: "transparent"; radius: width / 2
        border.color: control.pressed ? "#17a81a" : "#21be2b"
        opacity: control.enabled ? 1 : 0.3
    }
    handle: Rectangle {
        id: handleItem
        x: control.background.x + control.background.width / 2 - width / 2
        y: control.background.y + control.background.height / 2 - height / 2
        width: 16; height:16
        color: control.pressed ? "#17a81a" : "#21be2b"
        radius: 8; antialiasing: true
        opacity: control.enabled ? 1 : 0.3
        transform: [
            Translate {
                y: -Math.min(control.background.width, control.background.height) * 0.4 + handleItem.height / 2
            },
            Rotation {
                angle: control.angle
                origin.x: handleItem.width / 2; origin.y: handleItem.height / 2
            }
        ]
    }
}
```

## Slider
Slider用于提供一个范围内的值的选择，对应C++中的QSlider。 
Slider有一个滑道和一个滑块，拖动这个滑块可以选择Slider控件的值。 

* Slider默认选择范围是`[0，1]`，使用`from`和`to`属性可以修改这个范围。
* 如果需要更改步长，则可以设置`stepSize`属性。 
* `Value`属性可以获取当前选择的值，`valueAt()`函数则可以返回指定位置对应的值。
* `live`属性用于设置当Slider滑块拖动的时候，`value`属性是否会实时更新，其默认值为true。 
* `orientation`属性设置Slider的方向，其值可以是Qt.Horizontal或Qt.Vertical，默认值为Qt. Horizontal。 
* `horizontal`属性可以获取Slider的方向是否是水平的; 
* `vertical`属性可以获取Slider的方向是否是竖直的。 
* `touchDragThreshold`属性用于设置触发拖动事件的阈值，该值不影响鼠标拖动事件，仅影响触摸事件；其默认值为`Qt.styleHints.startDragDistance `。
* `snapMode`属性用于设置Slider滑块相对于步长的响应方式，其可选值为:
  * Slider.NoSnap: 滑块可以拖动到任意位置；
  * Slider.SnapAlways: 滑块只能按照步长拖动；
  * Slider.SnapOnRelease: 滑块在拖动时可以在任意位置，但释放时会固定到最近的步长位置。
* Slider滑块在由用户交互改变位置时会发出`moved()`信号。
* Slider包含两个可视项目: `background`和`handle`，通过定义这两个项目可以改变Slider的外观。
```js
Slider {
    from: 1; to: 100; stepSize: 5; value: 25
}

Slider {
    id: control
    value: 0.5
    background: Rectangle {
        x: control.leftPadding
        y: control.topPadding + control.availableHeight / 2 - height / 2
        implicitWidth: 200; implicitHeight: 4
        width: control.availableWidth; height: implicitHeight
        radius: 2; color: "black"
        Rectangle {
            width: control.visualPosition * parent.width
            height: parent.height
            color: "#21be2b"; radius: 2
        }
    }
    handle: Rectangle {
        x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
        y: control.topPadding + control.availableHeight / 2 - height / 2
        implicitWidth: 26; implicitHeight: 26
        radius: 13; color: control.pressed ? "#f0f0f0" : "#f6f6f6"
        border.color: "#bdbebf"
    }
}
```

## RangeSlider
RangeSlider与Slider类似，不同之处在于Slider只有一个滑块，用于选择一个值，而 RangeSlider有两个滑块，用于选择一个范围。

* RangeSlider默认选择范围是`[0，1]`，使用`from`和`to`属性可以修改这个范围。
* 如果需要修改步长，则可以设置`stepSize`属性。 
* RangeSlider有两个属性组: `first`和`second`，用于控制两个滑块的值。可以使用`first.value`和`second.value`分别设置两个滑块的初始值，也可以使用 `setValues()`函数一次设置两个值。 
* RangeSlider的很多属性与Slider基本一致，可以参考前面对Slider属性的讲解。
* RangeSlider包含3个可视项目: `background`、`first.handle`和`second.handle`，通过定义这3个项目可以改变 RangeSlider的外观。

## Tumbler
Tumbler类似iOS系统的UIPickerView，是一种转轮型选择器，由用户滑动“轮子”选择一项。当出现这样的场景：使用RadioButton时存在很多选项，也就需要创建很多RadioButton；或者可以使用可编辑的SpinBox，但又不需要用户可输入任意值的时候，就可以考虑使用Tumbler。Tumbler特别适合于没有键盘以及从大量选项中选取的情景。

Tumbler的API类似于ListView和PathView，可以设置`model`和`delegate`属性。
只读属性`count`和`currentItem`则可以访问当前视图的状态。
与ListView和PathView不同的是，如果`model`不为空，则Tumbler始终存在当前值。这意味着，如果`count`为0，则`currentIndex`为-1；否则，`currentIndex`始终会是非负值。
使用`positionViewAtIndex()`函数可以定位给定索引位置的视图。

默认情况下，当滑动到最后一项时（也就是`count`属性大于`visibleltemCount`属性）， Tumbler会自动返回第一项，可以通过`wrap`属性设置是否开启该行为。
`visibleItemCount`属性必须是奇数，因为 Tumbler必须有一个选项处于中间的位置。

Tumbler包含3个可视项目: `background`、`contentItem`和`delegate`，通过定义这3个项目可以改变Tumbler的外观。
如果需要定义自己的`contentItem`，则可以使用ListView或者PathView作为根项目。对于可回环的Tumbler，使用PathView；对于不可回环的Tumbler，使用 ListView
```js
// 时间选择器
Row {
    Tumbler { id: hoursTumbler; model: 12 }
    Tumbler { id: minutesTumbler; model: 60 }
    Tumbler { id: amPmTumbler; model: ["AM", "PM"] }
}
// 修改样式
Tumbler {
    id: control; model: 15
    background: Item {
        Rectangle {
            opacity: control.enabled ? 0.2 : 0.1
            border.color: "#000000"
            width: parent.width; height: 1
            anchors.top: parent.top
        }
        Rectangle {
            opacity: control.enabled ? 0.2 : 0.1
            border.color: "#000000"
            width: parent.width; height: 1
            anchors.bottom: parent.bottom
        }
    }
    delegate: Text {
        text: qsTr("Item %1").arg(modelData + 1); font: control.font
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        opacity: 1.0 - Math.abs(Tumbler.displacement) / (control.visibleItemCount / 2)
    }

    Rectangle {
        anchors.horizontalCenter: control.horizontalCenter
        y: control.height * 0.4; width: 40; height: 1; color: "#21be2b"
    }
    Rectangle {
        anchors.horizontalCenter: control.horizontalCenter
        y: control.height * 0.6; width: 40; height: 1; color: "#21be2b"
    }
}
```