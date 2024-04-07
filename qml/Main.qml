import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Window {
    id: mainView
    width: 1024
    height: 700
    visible: true
    // flags: Qt.FramelessWindowHint  // Turn on this line for embedded screen
    title: qsTr(MainViewManager.appNameVer)

    property string headerFontFamily: "Tahoma"
    property int companyFontSize: 12
    property string companyFontColor: "darkred"
    property int headerFontSize: 18
    property string headerBgColor: "white"
    property string gradientStartColor: "lightblue"
    property string gradientEndColor: "blue"

    property int rowLeftMargin: 30
    property string boldLabelFont: "Impact"
    property real hoverOpacity: 0.75

    property real minVelocity: -250
    property real maxVelocity: 250

    property real minDistance: 1
    property real maxDistance: 299

    property var velocities: [MainViewManager.velocityPreset1,
        MainViewManager.velocityPreset2,
        MainViewManager.velocityPreset3,
        MainViewManager.velocityPreset4]

    property var distances: [MainViewManager.distancePreset1,
        MainViewManager.distancePreset2,
        MainViewManager.distancePreset3,
        MainViewManager.distancePreset4]


    Gradient {
        id: appGradientId
        GradientStop {
            position: 0.0
            color: gradientStartColor
        }
        GradientStop {
            position: 1.0
            color: gradientEndColor
        }
    }

    Rectangle {
        id: mainViewRect
        objectName: "mainViewRect"

        anchors.fill: parent
        gradient: appGradientId

        Header {
            id: headerId
        }

        Feedback {
            NumberAnimation on opacity {
                from: 0
                to: 0.85
                duration: 2000
                easing.type: Easing.OutQuad
            }
        }

        RowLayout {
            id: powerKnobRowId
            enabled: MainViewManager.instrumentControlsEnabled

            Layout.alignment: Qt.AlignTop
            Layout.minimumHeight: velocityId.height

            anchors {
                top: headerId.bottom
                topMargin: 15
                left: parent.left
                right: parent.right
                leftMargin: rowLeftMargin
            }

            RfPower {
            }

            KnobControl {
                id: velocityId
                knobMinValue: minVelocity
                knobMaxValue: maxVelocity
                labelText: "Velocity"
                unitText: "KPH"
                knobCurrentValue: MainViewManager.velocity
                onKnobCurrentValueChanged: MainViewManager.setVelocity(knobCurrentValue)
            }

            KnobControl {
                id: distanceId
                knobMinValue: minDistance
                knobMaxValue: maxDistance
                labelText: "Distance"
                unitText: "KM"
                knobCurrentValue: MainViewManager.distance
                onKnobCurrentValueChanged: MainViewManager.setDistance(knobCurrentValue)
            }


        }

        RowLayout {
            id: presetRowId
            enabled: MainViewManager.instrumentControlsEnabled

            anchors {
                bottom: parent.bottom
                bottomMargin: 10
                left: parent.left
                right: parent.right
                leftMargin: rowLeftMargin
            }
            Layout.alignment: Qt.AlignBottom

            PresetButton {
                presetTitle: "Preset 1"
                labelFont: boldLabelFont
                velocity: velocities[0]
                distance: distances[0]
                velocityControl: velocityId
                distanceControl: distanceId
                hoverOapacity: mainView.hoverOpacity
            }
            PresetButton {
                presetTitle: "Preset 2"
                labelFont: boldLabelFont
                velocity: velocities[1]
                distance: distances[1]
                velocityControl: velocityId
                distanceControl: distanceId
                hoverOapacity: mainView.hoverOpacity
            }
            PresetButton {
                presetTitle: "Preset 3"
                labelFont: boldLabelFont
                velocity: velocities[2]
                distance: distances[2]
                velocityControl: velocityId
                distanceControl: distanceId
                hoverOapacity: mainView.hoverOpacity
            }
            PresetButton {
                presetTitle: "Preset 4"
                labelFont: boldLabelFont
                velocity: velocities[3]
                distance: distances[3]
                velocityControl: velocityId
                distanceControl: distanceId
                hoverOapacity: mainView.hoverOpacity
            }

        }
    }




}
