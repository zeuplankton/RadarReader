import QtQuick
import QtQuick.Layouts

Item {
    id: rootId
    property string presetTitle: "Preset"
    property string labelFont: "Impact"
    property string presetFontFamily: "Tahoma"
    property int presetFontSize: 16
    property real velocity
    property real distance
    property int digits: 1

    property url buttonDownSource: "qrc:/button/images/preset_down.png"
    property url buttonUpSource: "qrc:/button/images/preset_up.png"
    property url imageSource: buttonUpSource
    property bool clickEvent: false
    property var distanceControl
    property var velocityControl
    property real hoverOapacity: .1

    height: presetLayout.height
    width: presetLayout.width

    function sendPreset(mouse) {
        print("PresetButton.QML: Sending " + velocity + " " + distance);
        clickEvent = true;
        distanceControl.knobCurrentValue = distance;
        velocityControl.knobCurrentValue = velocity;
    }

    ColumnLayout {
        id: presetLayout
        Text {
            text: presetTitle
            Layout.alignment: Qt.AlignCenter
            color: "white"
            font {
                family: labelFont
                pointSize: presetFontSize
            }
        }

        Image {
            id: buttonImageId
            source: imageSource

            MouseArea {
                id: mouseAreForButton
                anchors.fill: parent
                onClicked: (mouse) => sendPreset(mouse)
                onPressed: imageSource = buttonDownSource
                onReleased: imageSource = buttonUpSource
                hoverEnabled: true
                onHoveredChanged: parent.opacity = containsMouse ? hoverOapacity : 1.0
            }

            Column {
                width: parent.width
                anchors {
                    top: parent.top
                    topMargin: 5
                }
                spacing:  5
                Text {
                    width: parent.width
                    height: parent.height / 2
                    text: velocity.toFixed(digits) + " KPH"
                    font {
                        family: presetFontFamily
                        weight: Font.Bold
                        pointSize: presetFontSize
                    }
                    color: "black"
                    horizontalAlignment: Qt.AlignHCenter
                }
                Text {
                    width: parent.width
                    text: distance.toFixed(digits) + " KM"
                    font {
                        family: presetFontFamily
                        weight: Font.Bold
                        pointSize: presetFontSize
                    }
                    color: "ghostwhite"
                    horizontalAlignment: Qt.AlignHCenter
                }
            }
        }
    }
}
