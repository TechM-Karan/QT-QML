import QtQuick 2.7
import QtQuick.Controls 2.0

ApplicationWindow {
    id: window
    visible: true
    width: 1080
    height: 880
    title: qsTr("Stack")

    StackView {
        id: stackView
        initialItem: "SocketConnection.qml"
        anchors.fill: parent
    }
}
