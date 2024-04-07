import QtQuick
import QtQuick.Layouts

Column {
    id: rootId

    property string labelText: "Velocity"
    property string unitText: "KPH"
    property string labelFont: "Impact"
    property color labelColor: "white"
    property color unitColor: "#505050"
    property string readoutFont: "Digital-7 Mono"
    property int readoutSize: 55
    property color readoutColor: "blue"
    property int stdSpacing: 10
    property int labelSize: 28
    property int unitSize: 25
    property int headerWidth: 200
    property int headerHeight: 110

    property int knobLabelSize: 12
    property int knobLabelSpacing: 30
    property real midValue: knobMinValue + (knobMaxValue-knobMinValue)/2

    property alias knobCurrentValue: knobId.currentValue
    property alias knobMinValue: knobId.minValue
    property alias knobMaxValue: knobId.maxValue


    spacing: stdSpacing
    //width: 200
    Item {
        id: knobHeaderId
        height: labelSize + readoutSize + stdSpacing
        width:200

        Item {
            id: labelUnitId
            width: parent.width
            height: labelSize + stdSpacing
            anchors.bottomMargin: stdSpacing

            Text {
                id: labelId
                text: labelText
                font {
                    family: labelFont
                    pixelSize: labelSize
                }
                color: labelColor
                anchors.left: parent.left
            }
            Text {
                id: unitId
                text: unitText
                font {
                    family: labelFont
                    pixelSize: unitSize
                }
                color: unitColor
                anchors.bottom: labelId.bottom
                anchors.right: parent.right
            }
        }

        Rectangle {
            id: readoutAreaId
            color: "white"
            width: parent.width
            height: readoutSize
            anchors.top: labelUnitId.bottom

            Rectangle {
                color: "cyan"
                width: parent.width - 4
                height: readoutSize - 4
                anchors.centerIn: parent

                Text {
                    id: readoutValueId
                    text: knobId.currentValue.toFixed(knobId.digits)
                    font {
                        family: readoutFont
                        pixelSize: readoutSize
                    }
                    color: readoutColor
                    anchors {
                        right: parent.right
                        rightMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                }
            }
        }
    }

    Text {
        text: midValue
        font {
            family: labelFont
            pointSize: knobLabelSize
        }
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Knob {
        id: knobId
    }

    Row {
        anchors.horizontalCenter: knobId.horizontalCenter
        spacing: knobLabelSpacing
        Text {
            id: leftLabelId
            text: knobMinValue > 0 ? "+" + knobMinValue: knobMinValue
            font {
                family: labelFont
                pointSize: knobLabelSize
            }
            color: "white"
        }
        Text {
            id: rightLabelId
            text: knobMaxValue > 0 ? "+" + knobMaxValue: knobMaxValue
            font {
                family: labelFont
                pointSize: knobLabelSize
            }
            color: "white"
        }
    }
}
