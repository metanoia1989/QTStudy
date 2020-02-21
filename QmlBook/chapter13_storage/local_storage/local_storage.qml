import QtQuick 2.12
import QtQuick.LocalStorage 2.12

Item {
    property var db
    width: 640
    height: 480

    function initDatabase() {
        print("initDatabase()");
        db = LocalStorage.openDatabaseSync("CrazyBox", "1.0", "A box who remembers its position", 100000);
        db.transaction(function(tx){
            print("....create table")
            tx.executeSql("CREATE TABLE IF NOT EXISTS data(name TEXT, value TEXT)")
        });
    }

    function storeData() {
        print("storeData()")
        if (!db) return;
        db.transaction(function(tx) {
            print("... check if a crazy object exists")
            var result = tx.executeSql("select * from data where name = 'crazy'")
            var obj = { x: crazy.x, y: crazy.y }
            if (result.rows.length === 1) {
                print("... crazy exists, update it")
                result = tx.ececuteSql("UPDATE data set value=? where name='crazy'")
            } else {
                print("... crazy does not exists, create it")
                result = tx.executeSql("insert into data values(?, ?)", ['crazy', JSON.stringify()])
            }
        });
    }

    function readData() {
        print("readData")
        if(!db) return;
        db.transaction(function(tx){
            print("... read crazy object")
            var result = tx.executeSql("select * from data where name='crazy'")
            if (result.rows.length === 1) {
                print("... update crazy geometry")
                var value = result.rows[0].value;
                var obj = JSON.parse(value)
                crazy.x = obj.x;
                crazy.y = obj.y;
            }
        });
    }

    Component.onCompleted: {
        initDatabase();
        readData();
    }

    Component.onDestruction: {
        storeData();
    }
}
