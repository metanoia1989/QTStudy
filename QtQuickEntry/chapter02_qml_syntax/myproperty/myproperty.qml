import QtQuick 2.12

Displayable {
    title: "hello"
    Person {
        id: person; title: "Qt"
    }
    Component.onCompleted: {
        console.log(person.fullName() + getTitle())
    }
}
