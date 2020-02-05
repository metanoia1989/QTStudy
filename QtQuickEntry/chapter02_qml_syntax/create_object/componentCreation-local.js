var component;
var sprite;

function createSpriteOjbects() {
    component = Qt.createComponent("Sprite.qml");
    sprite = component.createObject(appWindow, {"x": 100, "y": 100})
    if (sprite === null) {
        // 错误处理
        console.log("Error creating object");
    }
}

