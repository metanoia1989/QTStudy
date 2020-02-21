# QT 学习
Qt 5 编程入门 https://book.douban.com/subject/26325495/
Qt Creator快速入门 https://book.douban.com/subject/30199912/
PyQt5快速开发与实战 https://book.douban.com/subject/27170635/
Qt 5.9 C++开发指南 https://book.douban.com/subject/30320649/


```js

import bb.cascades 1.0

Page {
    content: Container {
        Label {
            id: emailLabel
            text: qsTr("Email")
        }
        Label {
            id: urlLabel
            text: qsTr("URL")
        }
        Label {
           id: sinceLabel
           text: qsTr("Since")
        }
        Label {
           id: bioLabel
           text: qsTr("Bio")
        }
        Button {
            id: requestButton
            text: "World Domination"
            onClicked: {

                request('http://someurlgoeshere.com', function (o) {
                        
                        // log the json response
                        console.log(o.responseText);
                        
                        // translate response into object
                        var d = eval('new Object(' + o.responseText + ')');

                        // access elements inside json object with dot notation
                        emailLabel.text = d.email
                        urlLabel.text = d.url
                        sinceLabel.text = d.since
                        bioLabel.text = d.bio
                         
                    });
            }
        }
    }
    // this function is included locally, but you can also include separately via a header definition
    function request(url, callback) {
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = (function(myxhr) {
            return function() {
                if (myxhr.readyState === 4) callback(myxhr);
            }
        })(xhr);
        xhr.open('GET', url, true);
        xhr.send('');
    }
}
```