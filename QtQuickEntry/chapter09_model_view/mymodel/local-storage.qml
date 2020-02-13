import QtQuick 2.9
import QtQuick.LocalStorage 2.12

Rectangle {
    width: 200; height: 100

    Text {
        text: "?"
        anchors.horizontalCenter: parent.horizontalCenter

        Component.onCompleted: findGreetings()

        function findGreetings() {
            let db = LocalStorage.openDatabaseSync(
                "QQmlExampleDB", "1.0", "The Example QML SQL!", 1000000)
            db.transaction((tx) => {
                // 如果数据库不存在则创建数据库
                tx.executeSql("CREATE TABLE IF NOT EXISTS Greeting (salutation TEXT, salutee TEXT)")
                // 添加一条记录
                let result = tx.executeSql("INSERT INTO Greeting VALUES(?, ?)", ["hello", "world"]);
                tx.executeSql("INSERT INTO Greeting VALUES(?, ?)", ["hello", "qml"]);
                tx.executeSql("INSERT INTO Greeting VALUES(?, ?)", ["hello", "c++"]);
                // 显示内容
                let rs = tx.executeSql("SELECT * FROM Greeting");
                let r = "";
                for (let row of rs.rows) {
                    r += row.salutation + "," + row.salutee + "\n";
                }
                text = r;
            });
        }
    }
}
