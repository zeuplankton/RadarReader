import QtQuick
import QtQuick.Controls
import QtQuick.Layouts



Rectangle {
    color:  headerBgColor
    anchors {
        top: parent.top
        left: parent.left
        right: parent.right
    }
    height: 120

    RowLayout {
        id: logoGrid
        anchors{
            left: parent.left
            right: parent.right
        }

        Image {
            id: swatLogo
            source: "qrc:/logo/images/swatteam.png"
            sourceSize.width: 100
            sourceSize.height: 100
            sourceClipRect: Qt.rect(-20, -10, 150, 120)
            verticalAlignment: Image.AlignVCenter
            horizontalAlignment: Image.AlignHCenter
        }
        Text {
            text: "Software and Technical Team \n@ Mantis Shrimp Inc."
            font {
                family: headerFontFamily
                pointSize: companyFontSize
            }
            color: companyFontColor
        }
        Text {
            text:  MainViewManager.appName
            font {
                family: headerFontFamily
                pointSize: headerFontSize
                weight: Font.Bold
            }
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
            color: gradientEndColor
        }
    }
}

