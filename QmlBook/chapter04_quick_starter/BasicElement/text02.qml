import QtQuick 2.12

Rectangle {
    width: 400; height: 120

    Text {
        width: 140; height: 120
        text: "爾時，世尊告諸比丘：「於色當正思惟，色無常如實知。所以者何？比丘！於色正思惟，觀色無常如實知者，於色欲貪斷；欲貪斷者，說心解脫。" +
              "如是受、想、行、識當正思惟，觀識無常如實知。所以者何？於識正思惟，觀識無常者，則於識欲貪斷；欲貪斷者，說心解脫。" +
              "如是心解脫者，若欲自證，則能自證：『我生已盡，梵行已立，所作已作，自知不受後有。』如是正思惟無常，苦、空、非我亦復如是。」"
//        elide: Text.ElideMiddle
        style: Text.Sunken
        styleColor: "#ff4444"
        verticalAlignment: Text.AlignTop
        wrapMode: Text.WordWrap
    }
}
