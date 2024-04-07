import QtQuick
import QtQuick.Layouts

ColumnLayout {
    id: powerAreaId

    property url powerOnSource: "qrc:/button/images/power_on.png"
    property url powerOffSource: "qrc:/button/images/power_off.png"
    property url powerSource: powerOn ? powerOnSource : powerOffSource
    property bool powerOn: MainViewManager.powerOn

    function togglePower() {
        print("In Main.qml togglePower(), powerOn: " + powerOn);
        print("About to change powerOn, sending the powerOn change back to C++");
        MainViewManager.setPowerOn(!powerOn);
        print("Finished changing powerOn, now in QML re-rendering with powerOn: " + powerOn);
    }

    Layout.alignment: Qt.AlignTop
    Text {
        text: "RF Power"
        Layout.alignment: Qt.AlignCenter
        color: "white"
        font {
            pointSize: 25
            family: boldLabelFont
        }
    }
    Image {
        id: powerButtonId
        source: powerSource
        sourceSize {
            width: 110
            height: 110
        }
        MouseArea {
            onClicked: togglePower()
            anchors.fill: parent
            hoverEnabled: true
            onHoveredChanged: parent.opacity = containsMouse ? hoverOpacity : 1.0
        }
    }
}

