import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import MonthCalendar
import EventManager 1.0


Window {
    id:window
    width: 480
    height: 640
    visible: true
    title: qsTr("TimeSync")

    MonthCalendar {
      id: calendar
    }

    EventManager {
        id: eventManager
    }

    DetailedEventView {
        id: eventviewevent
        eventManager: eventManager
        visible: false
    }

    EventView{
        id: eventviewday
        calendar: calendar
        eventManager: eventManager
        visible: false
    }

   EventCalendar{
       id: eventviewcalendar
       calendar: calendar
       eventManager: eventManager
   }


// Floating Action Button to open menu
    Button {
        id: menu
        x: 20
        y: window.height - height - 20
        width: 128
        height: 56
        //borderRadius: width / 2
        text: "Menu"
        background: Rectangle {
            color: "#4B90FC" // A green color for the FAB
            radius: menu.width / 2
        }
        onClicked: {
            // Action to perform when the button is clicked
            menuForm.open()
            //menu.visible = false
        }
    }

    MenuForm {
        id: menuForm
        calendar: calendar
        eventManager: eventManager
    }




    // Floating Action Button to add new events
        Button {
            id: fab
            x: window.width - width - 20
            y: window.height - height - 20
            width: 56
            height: 56
            //borderRadius: width / 2
            text: "+"
            background: Rectangle {
                color: "#2E7D32" // A green color for the FAB
                radius: fab.width / 2
            }
            onClicked: {
                // Action to perform when the button is clicked
                eventCreationForm.open()
                eventManager.testFunction()
                console.log("Floating action button clicked")
            }
        }

        // The event creation form component
        EventCreationForm {
            id: eventCreationForm
            calendar: calendar
            eventManager: eventManager
            // Set anchors or position as per your design requirement
        }
}
