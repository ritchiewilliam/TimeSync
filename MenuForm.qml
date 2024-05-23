import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import MonthCalendar
import EventManager 1.0

Item {
    id: formContainer
    width: parent.width * 0.25
    height: parent.height * 0.3
    visible: false
    anchors.bottom: parent.bottom
    anchors.left: parent.left

    required property MonthCalendar calendar
    required property EventManager eventManager

    // Actual form content
    Rectangle {
        width: formContainer.width   // Adjust width to match the second image
        height: formContainer.height
        color: "#333333"  // A lighter shade of grey
        anchors.centerIn: parent
        radius: 20  // Adjusted for more rounded corners
        RowLayout {
            spacing: parent.width * 0.1
            Rectangle {

            }

            ColumnLayout {
                spacing: 8
                Rectangle {

                }
                Button {
                    text: "Calendar"
                    onClicked: {
                        eventviewday.visible = false;
                        eventviewevent.visible = false;
                        eventviewcalendar.visible = true;
                        calendar.refreshCalendar();
                        formContainer.close();
                    }
                }
                Button {
                    text: "Event"
                    onClicked: {
                        eventviewday.visible = true;
                        eventviewevent.visible = false;
                        eventviewcalendar.visible = false;

                        eventManager.updateEventList(calendar.viewDate)

                        formContainer.close();
                    }
                }
                Button {
                    text: "Task"
                    onClicked: {
                        formContainer.close();
                    }
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
