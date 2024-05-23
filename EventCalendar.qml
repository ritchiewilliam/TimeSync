import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import MonthCalendar
import EventManager

Item {
    width: parent.width
    height: parent.height
    id: eventitem

    property var locale: Qt.locale()

    readonly property date currentDate: new Date()
    required property MonthCalendar calendar
    required property EventManager eventManager

    calendar: calendar

    Rectangle {
        anchors.fill: parent
        width: parent.width
        height: parent.height
        color: "#202020"

        Column {
            id: column
            width: parent.width
            height: parent.height/2
            spacing: 10
            leftPadding: 10
            rightPadding: 10
            topPadding: 10

            Rectangle {
                id: calHeader
                width: column.width - (column.leftPadding * 2)
                height: parent.parent.height * 0.05
                //anchors.margins: 10
                color: "#303030"
                Button {
                    anchors.left: parent.left
                    text: "<"
                    font.pixelSize: parent.height * 0.3
                    height: parent.height
                    width: parent.width * 0.15
                    onClicked: {
                        calendar.viewDate = new Date(calendar.getJSViewDate().getFullYear(), calendar.getJSViewDate().getMonth() - 1, calendar.getJSViewDate().getDate());
                    }
                }

                Text {
                    id: heading
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: new Date(calendar.viewDate.getFullYear(), calendar.viewDate.getMonth(), calendar.viewDate.getDate() + 1).toLocaleString(locale, "MMMM yyyy")
                    color: "white"
                    font.pixelSize: parent.height * 0.75
                }

                Button {
                    anchors.right: parent.right
                    text: ">"
                    font.pixelSize: parent.height * 0.3
                    height: parent.height
                    width: parent.width * 0.15
                    onClicked: {
                        calendar.viewDate = new Date(calendar.getJSViewDate().getFullYear(), calendar.getJSViewDate().getMonth() + 1, calendar.getJSViewDate().getDate());
                    }
                }

            }

            Rectangle {
                height: 3 * calHeader.height/4
                width: calHeader.width
                color: "#303030"
                RowLayout {
                    width: parent.width

                    property var dayNames: ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"]
                    Repeater {
                        model: parent.dayNames
                        Text {
                            //Layout.alignment: Qt.AlignHCenter
                            text: modelData
                            color: "white"
                        }
                    }
                }
            }

            Rectangle {
                width: column.width - (column.leftPadding * 2)

                height: 6 * (width / 7)
                color: "white"

                GridLayout {
                    id: grid

                    width: column.width - (column.leftPadding * 2) - 4
                    height: 6 * (width / 7) - 2

                    anchors.verticalCenterOffset: - (height / 12)
                    anchors.horizontalCenter: parent.Center

                    columnSpacing: 1
                    rowSpacing: 1

                    anchors.centerIn: parent

                    columns: 7

                    Repeater {
                        id: repeat
                        model: calendar.dayList
                        Item {
                            Rectangle {
                                id: box

                                width: grid.width / 7 - 2
                                height: width
                                color: "#303030"

                                // Rectangle {
                                //     width: parent.width / 6
                                //     height: width
                                //     anchors.topMargin: width / 3
                                //     anchors.leftMargin: width / 3
                                //     anchors.top: parent.top
                                //     anchors.left: parent.left
                                //     color: "#FF0000"
                                //     radius: width/2
                                //     visible:
                                // }

                                Text {
                                    anchors.fill: parent
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    text: modelData.getDate()
                                    font.pixelSize: height / 3
                                    color: modelData.getMonth() === (calendar.getJSViewDate()).getMonth() ? "white" : "gray"

                                    Rectangle {
                                        height: Math.max(parent.width, parent.height) * 0.5
                                        width: height
                                        radius: width/5
                                        color: "red"
                                        anchors.centerIn: parent
                                        // anchors.verticalCenterOffset: parent.height - parent.baselineOffset
                                        z: -1
                                        visible: calendar.today.getDate() === modelData.getDate() && calendar.today.getMonth() === modelData.getMonth() && calendar.today.getFullYear() === modelData.getFullYear()
                                    }

                                }

                                TapHandler {
                                    acceptedButtons: Qt.TapGesture | Qt.LeftButton
                                    onTapped: (eventPoint, button)=> {
                                                  for( var i = 0; i < repeat.count; i++ ) {
                                                      // console.log("Color:" + repeat.itemAt(i).children[0].color)
                                                      if(repeat.itemAt(i).children[0].color == "#505050") {
                                                           repeat.itemAt(i).children[0].color = "#303030"
                                                      }
                                                  }
                                                  //console.log(modelData);

                                                  box.color = "#505050"

                                                  calendar.viewDate = new Date(modelData - 1);
                                                  eventManager.updateEventList(calendar.viewDate)

                                                  eventviewcalendar.visible = false;//set calendar to invisible if page is switched but it is not 'closed'
                                                  eventviewday.visible = true;

                                              }
                                }
                            }

                        }
                    }
                }
            }


        }

    }

}

