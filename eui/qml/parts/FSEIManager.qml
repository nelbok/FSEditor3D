import QtQuick
import QtQuick.Dialogs

import eui

Item {
    FSEAskSaveDialog {
        anchors.centerIn: parent
        visible: MyInterface.isAskSaveDialogVisible
        onSaveClicked: MyInterface.saveClicked()
        onDiscardClicked: MyInterface.discardClicked()
        onCancelClicked: MyInterface.cancelClicked()
    }

    Connections {
        target: MyInterface
        function onOpenSaveDialog() {
            dialog.fileMode = FileDialog.SaveFile
            dialog.open()
        }
        function onOpenLoadDialog() {
            dialog.fileMode = FileDialog.OpenFile
            dialog.open()
        }
    }

    FileDialog {
        id: dialog
        nameFilters: ["JSON Files (*.json)"]
        onAccepted: {
            switch(fileMode) {
            case FileDialog.SaveFile:
                MyInterface.saveFile(selectedFile)
                break;
            case FileDialog.OpenFile:
                MyInterface.loadFile(selectedFile)
                break;
            default:
                //Nothing to do
            }
        }
        onRejected: MyInterface.cancelClicked()
    }

    FSEProgressDialog {
        anchors.centerIn: parent
        visible: MyInterface.isProgressDialogVisible
        onClicked: MyInterface.requestFileTransactionInterruption()
    }

    FSEMessageDialog {
        anchors.centerIn: parent
        visible: MyInterface.isMessageDialogVisible
        text: MyInterface.message
        onClicked: MyInterface.okClicked()
    }

    Component.onCompleted: {
        MyInterface.checkForUpdates()
    }

}
