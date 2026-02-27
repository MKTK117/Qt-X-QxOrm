import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import Fluo

ApplicationWindow {
    visible: true
    width: 1100
    height: 680
    title: "Projects & Users"

    Material.theme: Material.Dark
    Material.accent: Material.Teal
    Material.primary: Material.BlueGrey
    Material.foreground: "#e0e0e0"

    Rectangle {
        anchors.fill: parent
        color: Material.background
    }

    header: ToolBar {
        height: 56

        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 16
            anchors.rightMargin: 16

            Label {
                text: "Projects & Users"
                font.pixelSize: 20
                font.bold: true
                color: "white"
            }

            Item {
                Layout.fillWidth: true
            }

            ToolButton {
                text: "Refresh"
                icon.name: "refresh"
                onClicked: {
                    projectModel.refresh();
                    userModel.refresh();
                    console.log("Refresh requested");
                }
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 16

        // ──────────────── Users ────────────────
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 8

            Label {
                text: "Users"
                font.pixelSize: 18
                font.bold: true
                color: Material.accent
            }

            Frame {
                Layout.fillWidth: true
                Layout.fillHeight: true
                padding: 1

                ListView {
                    id: usersTable
                    anchors.fill: parent
                    clip: true
                    model: AppController.user

                    ScrollBar.vertical: ScrollBar {}

                    delegate: Rectangle {
                        implicitHeight: 52
                        implicitWidth: projectsTable.width

                        color: active ? Material.primary : index % 2 === 0 ? Qt.rgba(1, 1, 1, 0.04) : Qt.rgba(0, 0, 0, 0.03)
                        border.color: "#404040"
                        border.width: 1

                        Rectangle {
                            anchors.fill: parent
                            color: "#20ffffff"
                            visible: mouseArea.containsMouse
                            radius: 3
                        }

                        MouseArea {
                            id: mouseArea
                            anchors.fill: parent
                            hoverEnabled: true
                            acceptedButtons: Qt.LeftButton | Qt.RightButton

                            onClicked: function (mouse) {
                                if (mouse.button === Qt.LeftButton) {
                                    console.log("Left clicked:", model.name);
                                    active = !active;
                                } else if (mouse.button === Qt.RightButton) {
                                    console.log("Right clicked:", model.name);
                                    appController.deleteProjectByName(model.name);
                                }
                            }
                        }

                        RowLayout {
                            anchors.fill: parent
                            anchors.leftMargin: 12
                            anchors.rightMargin: 12
                            spacing: 12

                            Label {
                                text: name
                                font.pixelSize: 15
                                font.bold: true
                                Layout.fillWidth: true
                                elide: Text.ElideRight
                            }
                        }
                    }
                }
            }
        }

        // ──────────────── Projects ────────────────

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 320
            spacing: 8

            Label {
                text: "Projects"
                font.pixelSize: 18
                font.bold: true
                color: Material.accent
            }

            Frame {
                Layout.fillWidth: true
                Layout.fillHeight: true
                padding: 1

                TableView {
                    id: projectsTable
                    anchors.fill: parent
                    model: AppController.project
                    clip: true

                    ScrollBar.vertical: ScrollBar {}

                    columnSpacing: 1
                    rowSpacing: 1

                    columnWidthProvider: function (column) {
                        switch (column) {
                        case 0:
                            return 200;
                        case 1:
                            return 160;
                        case 2:
                            return 200;
                        case 3:
                            return 200;
                        default:
                            return 120;
                        }
                    }

                    delegate: Rectangle {
                        implicitHeight: 48

                        color: row % 2 === 0 ? Qt.rgba(1, 1, 1, 0.04) : Qt.rgba(0, 0, 0, 0.03)

                        border.color: "#404040"
                        border.width: 1

                        Label {
                            anchors.fill: parent
                            anchors.margins: 12

                            text: {
                                switch (column) {
                                case 0:
                                    return model.name;
                                case 1:
                                    return model.creationDate;
                                case 2:
                                    return "Some text";
                                case 3:
                                    return "Some text";
                                default:
                                    return "";
                                }
                            }

                            font.pixelSize: column === 0 ? 15 : 14
                            color: column === 0 ? "#e0f7fa" : "#b0bec5"

                            elide: Text.ElideRight
                            wrapMode: Text.WordWrap
                            verticalAlignment: Text.AlignVCenter
                        }

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            acceptedButtons: Qt.LeftButton | Qt.RightButton

                            onClicked: function (mouse) {
                                if (mouse.button === Qt.LeftButton) {
                                    console.log("Left clicked:", model.name);
                                } else if (mouse.button === Qt.RightButton) {
                                    appController.deleteProjectByName(model.name);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    footer: ToolBar {
        height: 36
        Label {
            anchors.centerIn: parent
            text: "Total projects: " + (AppController.project ? AppController.project.rowCount() : 0)
            color: "#aaa"
            font.pixelSize: 13
        }
    }
}
