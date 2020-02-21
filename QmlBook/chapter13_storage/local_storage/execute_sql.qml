import QtQuick 2.12
import QtQuick.LocalStorage 2.12

Item {
    Component.onCompleted: {
        var db = LocalStorage.openDatabaseSync("MyExample", "1.0", "Example database", 10000);
        db.transaction(function (tx) {
            var result = tx.executeSql("select * from notes");
            for (var i = 0; i < result.rows.length; i++) {
                print(result.row[i].text);
            }
        });
    }
}
