import QtQuick 2.12
import QtQuick.Particles 2.12

Rectangle {
    width: 300; height: 300;

    ParticleSystem { id: particles }
    ImageParticle {
        system: particles; color: "green"
        source: "qrc:///particleresources/glowdot.png"
    }
    Emitter {
        system: particles
        emitRate: 30; lifeSpan: 2000
        velocity: PointDirection { y: 100; yVariation: 40 }
        width: parent.width; height: 70
    }
    Rectangle {
        x: 80; y: 120; width: 140; height: 30
        color: "#803333aa"
        Friction {
            anchors.fill: parent; system: particles
            factor: 3; threshold: 10
        }
    }
}
