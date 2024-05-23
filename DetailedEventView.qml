import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import EventManager


Item {
    id: view
    width: parent.width
    height: parent.height
    required property EventManager eventManager
    property int padding: 20
    Column {
        width: parent.width
        height: parent.height
        padding: view.padding
        spacing: 20

        RowLayout {
            width: parent.width - view.padding * 2
        Text {
            //anchors.horizontalCenter: parent.horizontalCenter
            //horizontalAlignment: Text.AlignHCenter
            text: eventManager.viewEvent.title
            font.pixelSize: parent.parent.height * 0.05
            font.bold: true
        }
        Button {
            Layout.alignment: Qt.AlignRight
            text: "Delete"
            onClicked: {

                var temp = new Date(calendar.viewDate.getFullYear(), calendar.viewDate.getMonth(), calendar.viewDate.getDate() + 1);

                eventManager.removeEvent(eventManager.viewEvent.title);
                eventManager.updateEventList(temp)

                eventviewevent.visible = false;
                eventviewday.visible = true;
            }
        }
        }

        Text {
            text: "Location: " + eventManager.viewEvent.location
            font.pixelSize: parent.height * 0.025
        }

        Text{
            text: eventManager.viewEvent.getDateDisplay() + '\n' + eventManager.viewEvent.getTimeDisplay()
            font.pixelSize: parent.height * 0.025
        }

        // Text{
        //     text: "Description"
        //     font.pixelSize: parent.height * 0.025
        // }

        Text{
            width: parent.width - view.padding * 2
            wrapMode: Text.Wrap
            text: eventManager.viewEvent.description
        }
    }
}
