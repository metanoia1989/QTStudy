import QtQuick 2.12
import QtQuick.Particles 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: root; width: 300; height: 300; color: "black"
    Button { text: "开始"; y: 0; onClicked: particles.start() }
    Button { text: "暂停"; y: 70; onClicked: particles.pause() }
    Button { text: "恢复"; y: 140; onClicked: particles.resume() }
    Button { text: "停止"; y: 210; onClicked: particles.stop() }

    ParticleSystem { id: particles; running: false }

    ItemParticle {
        system: particles
        delegate: Rectangle {
            id: rect; width: 10; height: 10
            color: "red"; radius: 10
        }
    }
    Emitter {
        system: particles; x: 100; width: 200
        velocity: PointDirection {
            y: 300
            yVariation: 100
        }
    }
}
