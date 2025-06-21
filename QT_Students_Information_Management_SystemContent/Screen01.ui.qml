

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import QT_Students_Information_Management_System
import QtQuick.Studio.Utils
import QtQuick3D 6.8
import QtQuick3D.Particles3D 6.8
import QtQuick3D.Physics
import QtQuick.VirtualKeyboard.Settings
import QtQuick.VirtualKeyboard.Layouts
import QtQuickUltralite.Layers
import QtQuick3D.Helpers 6.8
import QtQuick.VirtualKeyboard.Styles
import QtQuick.VectorImage
import QtQuick.Timeline.BlendTrees
import QtQuick.Timeline

Rectangle {
    id: rectangle
    width: 800
    height: 550

    color: Constants.backgroundColor

    Item {
        id: __materialLibrary__
    }

    Frame {
        id: frame0
        x: 8
        y: 8
        width: 784
        height: 54

        Label {
            id: label
            x: 306
            y: 7
            text: qsTr("Student Information System")
            scale: 2
        }
    }

    Frame {
        id: frame1
        x: 8
        y: 68
        width: 784
        height: 179

        Label {
            id: label1
            x: 56
            y: 21
            text: qsTr("Student ID")
        }

        Label {
            id: label2
            x: 56
            y: 70
            text: qsTr("First Name")
        }

        Label {
            id: label3
            x: 56
            y: 123
            text: qsTr("Last Name")
        }

        Label {
            id: label4
            x: 437
            y: 19
            text: qsTr("State")
        }

        Label {
            id: label5
            x: 437
            y: 68
            text: qsTr("City")
        }

        Label {
            id: label6
            x: 437
            y: 121
            text: qsTr("E-mail")
        }

        TextField {
            id: textField
            x: 123
            y: 7
            placeholderText: qsTr("Text Field")
        }

        TextField {
            id: textField1
            x: 123
            y: 58
            placeholderText: qsTr("Text Field")
        }

        TextField {
            id: textField2
            x: 123
            y: 111
            placeholderText: qsTr("Text Field")
        }

        TextField {
            id: textField3
            x: 509
            y: 111
            placeholderText: qsTr("Text Field")
        }

        ComboBox {
            id: comboBox
            x: 509
            y: 7
        }

        ComboBox {
            id: comboBox1
            x: 509
            y: 58
        }
    }

    Frame {
        id: frame2
        x: 8
        y: 253
        width: 784
        height: 70
        leftPadding: 12

        Button {
            id: button
            x: 39
            y: 8
            height: 30
            visible: true
            text: qsTr("Add")

            Image {
                id: image
                x: 8
                y: 2
                width: 24
                height: 24
                source: "qrc:/qtquickplugin/images/template_image.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        Button {
            id: button1
            x: 156
            y: 8
            height: 30
            text: qsTr("Button")
        }

        Button {
            id: button2
            x: 273
            y: 8
            height: 30
            text: qsTr("Button")
        }

        Button {
            id: button3
            x: 389
            y: 8
            height: 30
            text: qsTr("Button")
        }

        Button {
            id: button4
            x: 506
            y: 8
            height: 30
            text: qsTr("Button")
        }

        Button {
            id: button5
            x: 623
            y: 8
            height: 30
            text: qsTr("Button")
        }
    }

    Frame {
        id: frame3
        x: 8
        y: 329
        width: 784
        height: 213
    }
}
