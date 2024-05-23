//eventview.qml
//imports
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import MonthCalendar
import EventManager 1.0
import Q_Event

Item {
    width: parent.width
    height: parent.height
    id: eventitem
    readonly property date currentDate: new Date()

    required property MonthCalendar calendar //get date information
    required property EventManager eventManager

    Timer {
          id: timer
          interval: 1000 // every 1000 milliseconds (1 second)
          repeat: true // continue repeating
          running: true // start running immediately

          onTriggered: {

              var now = new Date();
              var timeString = Qt.formatTime(now, "hh:mm:ss");
              var dateString = calendar.getJSViewDate().toLocaleDateString(Qt.locale(), "yyyy-MM-dd");
              dateDisplay.text = dateString + " " + timeString; // Combine date and time
          }
      }

    ColumnLayout {
            width: parent.width
            height: parent.height
            RowLayout { // Top header for navigation
                width: parent.width
                //spacing: 10

                Button {
                    text: "<"
                    Layout.alignment: Qt.AlignLeft
                    onClicked: {

                        calendar.viewDate = new Date(calendar.getJSViewDate().getFullYear(), calendar.getJSViewDate().getMonth(), calendar.getJSViewDate().getDate() - 1);

                        eventManager.updateEventList(calendar.viewDate)

                        //selectedDate = new Date(calendar.viewDate.getFullYear(), calendar.viewDate.getMonth(), calendar.viewDate.getDate() + 1)//increment day as you want to go to next day

                        //selectedDate = new Date(selectedDate.getFullYear(), selectedDate.getMonth(), selectedDate.getDate() + 1)//increment day as you want to go to next day
                        dateDisplay.text = calendar.getJSViewDate().toLocaleDateString(Qt.locale(), "yyyy-MM-dd")

                    }
                }
                Text {
                           id: dateDisplay
                           Layout.fillWidth: true //Ensure text component takes up available space
                           horizontalAlignment: Text.AlignHCenter //Center-align the text

                           text: calendar.getJSViewDate().toLocaleDateString(Qt.locale(), "yyyy-MM-dd")
                       }
                Button {
                    text: ">"
                    Layout.alignment: Qt.AlignRight
                    onClicked: {

                        calendar.viewDate = new Date(calendar.getJSViewDate().getFullYear(), calendar.getJSViewDate().getMonth(), calendar.getJSViewDate().getDate() + 1);

                        eventManager.updateEventList(calendar.viewDate)
                        //selectedDate = new Date(selectedDate.getFullYear(), selectedDate.getMonth(), selectedDate.getDate() + 1)//increment day as you want to go to next day

                        dateDisplay.text = calendar.getJSViewDate().toLocaleDateString(Qt.locale(), "yyyy-MM-dd")
                    }
                }
            }
            // Events List
            ListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                // height: 640//same as device, temporarily hardcoded
                // width: 480
                width: parent.width
                model: eventManager.viewEvents

                delegate: Rectangle {
                    width: parent.width
                    height: 60//event option height

//color will be changed according to theme
                    color: "#f0f0f0"
                    Button {
                        anchors.fill: parent
                        RowLayout {//row formatting
                            spacing: 20
                            anchors.fill: parent
                            Rectangle{}
                            Text {
                                text: modelData.title
                                font.bold: true
                            }

                            Text {
                                Layout.alignment: Qt.AlignRight
                                horizontalAlignment: Text.AlignRight
                                text: modelData.getTimeDisplay()
                            }
                            Rectangle{}
                        }
                        onClicked: {
                            eventManager.viewEvent = modelData
                            eventviewday.visible = false;//set calendar to invisible if page is switched but it is not 'closed'
                            eventviewevent.visible = true;
                        }
                    }
                }
            }
        } // End ColumnLayout
        // ListModel {//hard coded to see widget display
        //     id: eventsModel
        //     Repeater {
        //         model: eventManager.getEvents()

        //         property Q_Event eventData: modelData
        //         ListElement { name: eventData.title; startTime: eventData.startTime; endTime: eventData.startTime }
        //     }

        // }


    }

