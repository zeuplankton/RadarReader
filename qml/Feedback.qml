import QtQuick
import QtQuick.Controls

Rectangle {
    id: rootId

    property string okButtonUpSource: "qrc:/button/images/okup.png"
    property string okButtonDownSource: "qrc:/button/images/okdown.png"
    property color outerRectColor: "gold"
    property color innerRectColor: "goldenrod"
    property color backgroundColor: "gray"
    property color normalText: "white"
    property color errorText: "darkred"
    property string fontFamily: "Tahoma"

    width: parent.width/1.5
    height: parent.height/1.5
    anchors.centerIn: parent
    color: backgroundColor
    border.color: outerRectColor
    border.width: 4
    z: 1
    opacity: MainViewManager.feedbackOKButtonVisible ? 0.9 : 0.85
    visible: MainViewManager.feedbackAreaVisible

    Rectangle {
        id: feedbackRect
        border.color: innerRectColor
        anchors {
            fill: parent
            margins: 4
        }
        border.width: 2
        color: parent.color
        opacity: parent.opacity

        Text {
            id: feedbackMessage
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            anchors {
                fill: parent
                margins: 20
            }
            font {
                family: fontFamily
                pointSize: 24
            }
            wrapMode: Text.WordWrap
            clip: true
            elide: Qt.ElideRight
            color: MainViewManager.feedbackOKButtonVisible ? errorText : normalText
            text: MainViewManager.feedbackMessage
        }
        ProgressBar {
            from: 0
            to: 100
            anchors {
                right: feedbackRect.right
                rightMargin: 20
                verticalCenter: feedbackRect.verticalCenter
            }
            indeterminate: value >= 100
            value: MainViewManager.feedbackProgress
            visible: !MainViewManager.feedbackOKButtonVisible
        }
        Image {
            id: okbutton
            source: okButtonUpSource
            anchors {
                bottom: parent.bottom
                bottomMargin: 10
                horizontalCenter: parent.horizontalCenter
            }
            visible: MainViewManager.feedbackOKButtonVisible
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onPressed: parent.source = okButtonDownSource
                onHoveredChanged: parent.opacity = containsMouse ? hoverOpacity : 1.0
                onClicked: { MainViewManager.setFeedbackAreaVisibility(false); }
            }
        }
    }

}
