import QtQuick 2.12
import QtQuick.Particles 2.12
import QtQuick.Controls 2.12

Rectangle {
    width: 320; height: 480; color: "#222222"

    ParticleSystem {
        anchors.fill: parent
        ImageParticle {
            groups: ["smoke"]; color: "#111111"
            source: "qrc:///particleresources/glowdot.png"
        }
        ImageParticle {
            groups: ["flame"];
            color: "#11ff4004"; colorVariation: 0.1
            source: "qrc:///particleresources/glowdot.png"
        }
        Emitter {
            anchors.centerIn: parent; group: "flame"
            emitRate: 120; lifeSpan: 1200
            size: 20; endSize: 10; sizeVariation: 10
            acceleration: PointDirection { y: -40 }
            velocity: AngleDirection {
                angle: 270; magnitude: 20;
                angleVariation: 22; magnitudeVariation: 5
            }
        }
        TrailEmitter {
            group: "smoke"; follow: "flame"
            emitRatePerParticle: 1; lifeSpan: 2400; lifeSpanVariation: 400
            size: 16; endSize: 8; sizeVariation: 8
            acceleration: PointDirection { y: -40 }
            velocity: AngleDirection {
                angle: 270; magnitude: 40;
                angleVariation: 22; magnitudeVariation: 5
            }
        }
    }
}
