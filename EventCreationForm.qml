import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import MonthCalendar
import EventManager 1.0

Item {
    id: formContainer
    width: parent.width
    height: parent.height * 0.8
    visible: false
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    anchors.right: parent.right

    required property MonthCalendar calendar
    required property EventManager eventManager

    property alias titleField: titleTextField.text
    property alias locationField: locationTextField.text
    property alias startTimeField: startTimeTextField.text
    property alias endTimeField: endTimeTextField.text
    property alias descriptionField: descriptionTextArea.text
    property alias dateField: dateTextField.text
    // Background dimmer
    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.4
        MouseArea {
            anchors.fill: parent
            onClicked: {
                // Check if the click is not on the formContent Rectangle
                if (!formContent.containsMouse) {
                    formContainer.close();
                }
            }
        }
    }

    // Actual form content
    Rectangle {
        width: formContainer.width   // Adjust width to match the second image
        height: formContainer.height
        color: "#333333"  // A lighter shade of grey
        anchors.centerIn: parent
        radius: 20  // Adjusted for more rounded corners
        MouseArea {
            anchors.fill: parent
            //onPressed: formContent.containsMouse = true
            //onReleased: formContent.containsMouse = false
        }
        ColumnLayout {
                    anchors.fill: parent
                    spacing: 10
                    Layout.topMargin: 0  // Reduce top margin to move text boxes up

                    // Header with title and submit button
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 10

                        Button {
                            text: "X"
                            onClicked: {
                                eventManager.testFunction();
                                formContainer.close()
                            }
                        }

                        Label {
                            text: qsTr("New Event")
                            Layout.fillWidth: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: 24  // Increase font size if needed
                            color: "white"  // Set the text color to white
                        }

                        Button {
                            text: qsTr("Submit")
                            onClicked: {
                                console.log("submit button clicked")
                                eventManager.createEvent(titleTextField.text, descriptionTextArea.text, locationTextField.text, startTimeTextField.text, endTimeTextField.text,dateTextField.text );
                                eventManager.updateEventList(calendar.viewDate);
                                calendar.refreshCalendar();
                                formContainer.close()
                            }
                        }
                    }
            // Fields container
            ColumnLayout {
                spacing: 10
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.margins: 10
                Layout.topMargin: 0
                // Event Title field
                TextField {
                    id: titleTextField
                    placeholderText: qsTr("Event Title")
                    Layout.fillWidth: true
                    color: "white"
                    padding: 10
                    background: Rectangle {
                        color: "#555555"
                        radius: 10
                        width: formContainer.width * .9
                    }
                }

                // Event Location field
                TextField {
                    id: locationTextField
                    placeholderText: qsTr("Event Location")
                    Layout.fillWidth: true
                    color: "white"
                    padding: 10
                    background: Rectangle {
                        color: "#555555"
                        radius: 10
                    }
                }
                TextField {
                    id: startTimeTextField
                    placeholderText: qsTr("Start Time (HH:mm)")
                    inputMask: "99:99;_"
                    Layout.fillWidth: true
                    inputMethodHints: Qt.ImhTime
                    color: "white"
                    padding: 10
                    background: Rectangle {
                        color: "#555555"
                        radius: 10
                        width: formContainer.width * .9
                    }

                    property bool isValidTime: true // Default to true

                    onTextChanged: {
                        if (text.length === 0) {
                            isValidTime = true; // Assume valid if empty to hide error message
                        } else {
                            const parts = text.split(":");
                            isValidTime = parts.length === 2 && !isNaN(parseInt(parts[0], 10)) && 
                                        !isNaN(parseInt(parts[1], 10)) && parseInt(parts[0], 10) < 24 && 
                                        parseInt(parts[1], 10) < 60;
                        }
                    }
                }

                Text {
                    text: "Invalid time format. Please use HH:mm."
                    color: "red"
                    visible: startTimeTextField.text.length > 0 && !startTimeTextField.isValidTime
                    Layout.alignment: Qt.AlignHCenter 
                    Layout.topMargin: 5 
                }

                TextField {
                    id: endTimeTextField
                    placeholderText: qsTr("End Time (HH:mm)")
                    inputMask: "99:99;_"
                    inputMethodHints: Qt.ImhTime
                    Layout.fillWidth: true
                    color: "white"
                    padding: 10
                    background: Rectangle {
                        color: "#555555"
                        radius: 10
                    }
                    property bool isValidTime: true

                    onTextChanged: {
                        if (text.length === 0) {
                            isValidTime = true; // Assume valid if empty to hide error message
                        } else {
                            const parts = text.split(":");
                            isValidTime = parts.length === 2 && !isNaN(parseInt(parts[0], 10)) && 
                                        !isNaN(parseInt(parts[1], 10)) && parseInt(parts[0], 10) < 24 && 
                                        parseInt(parts[1], 10) < 60;
                        }
                    }
                }

                Text {
                    text: "Invalid time format. Please use HH:mm."
                    color: "red"
                    visible: endTimeTextField.text.length > 0 && !endTimeTextField.isValidTime
                    Layout.alignment: Qt.AlignHCenter 
                    Layout.topMargin: 5 
                }
                // Date field
                TextField {
                    id: dateTextField
                    placeholderText: qsTr("YYYY-MM-DD")
                    Layout.fillWidth: true
                    color: "white"
                    padding: 10
                    background: Rectangle {
                        color: "#555555"
                        radius: 10
                    }
                    inputMethodHints: Qt.ImhDate

                    Component.onCompleted: {
                        text = Qt.formatDate(new Date(), "yyyy-MM-dd")
                    }
                }
                // Event Description field
                TextArea {
                    id: descriptionTextArea
                    placeholderText: qsTr("Event Description")
                    Layout.fillWidth: true
                    wrapMode: Text.Wrap
                    //Layout.preferredHeight:
                    color: "white"
                    padding: 30
                    background: Rectangle {
                        color: "#555555"
                        radius: 10
                    }
                    Layout.preferredHeight: formContainer.height * 0.3
                }
            }

        }
    }

    function open() {
        formContainer.visible = true
    }

    function close() {
        formContainer.visible = false;
        // Clear the text fields
        titleField = "";
        locationField = "";
        startTimeField = "";
        endTimeField = "";
        descriptionField = "";
    }
}
