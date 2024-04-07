import QtQuick

Rectangle {
    property int knobCenterX: knobImageId.x + knobImageId.width/2
    property int knobCenterY: knobImageId.y + knobImageId.height/2
    // property int startRotation: 195
    property int startRotation: knobImageId.rotation = (currentValue - minValue) / (maxValue - minValue) * 330 - 165


    property real degreesPerRadian: 180.0/Math.PI
    property real radiansPerRev: 2 * Math.PI

    property real maxValue: 999
    property real minValue: -999
    property real midValue: minValue + (maxValue-minValue)/2
    property real maxAllowedChanged: maxValue/4
    property real maxFwdAngle: 75
    property real maxRevAngle: 105
    property real totalAngle: 330
    property int digits: 1
    property real incrementPerDeg: ((maxValue-minValue)/330) + 0.2
    property real oldValue: currentValue
    property real currentValue

    function getEventAngle(event) {
        var angle = Math.atan2(event.y - knobCenterY, event.x - knobCenterX);
        if (angle < 0)
            angle += radiansPerRev;
        return angle;
    }

    function getValueFromAngle(angle) {
        var result = angle * incrementPerDeg + midValue;
        if (result > maxValue) result = maxValue;
        if (result < minValue) result = minValue;
        return result.toFixed(digits);
    }

    function handleKnobMove(mouseEvent) {
        var angle = getEventAngle(mouseEvent);
        var rotDeg = angle * degreesPerRadian
        if (rotDeg > maxFwdAngle && rotDeg < maxRevAngle)
            return;
        var for_conversion = rotDeg - 270;
        if (rotDeg < 90)
            for_conversion = rotDeg + 90;
        var new_value = getValueFromAngle(for_conversion)
        var delta = Math.abs(new_value - oldValue)
        if (delta < maxAllowedChanged) {
            currentValue = new_value;
            knobImageId.rotation = rotDeg + 90.0
            oldValue = new_value;
        }
    }

    id: knobBgId
    width: parent.width
    height: width
    radius: width/2
    color: "gainsboro"
    anchors.horizontalCenter: parent.horizontalCenter
    onCurrentValueChanged: knobImageId.rotation = (currentValue - minValue) / (maxValue - minValue) * 330 - 165

    Image {
        id: knobImageId
        source: "qrc:/knob/images/knob.png"
        sourceSize {
            width: parent.width
            height: parent.height
        }
        rotation: startRotation
        anchors.centerIn: parent
    }


    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onMouseXChanged: (mouse) => { if (pressedButtons == Qt.LeftButton) handleKnobMove(mouse) }
        onMouseYChanged: (mouse) => { if (pressedButtons == Qt.LeftButton) handleKnobMove(mouse) }


        onHoveredChanged: knobImageId.opacity = containsMouse ? hoverOpacity : 1.0
    }
}
