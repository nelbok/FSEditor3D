import QtQuick

import editor

LHEEntity {
    property MyObject object: null

    id: root

    entity: object

    LHEComboBox {
        name: qsTr("Model")

        MySelectionManager {
            id: mng
            model: MyModels.modelModel
            currentData: (root.object) ? root.object.model : null
            onCurrentUpdated: { if (root.object && root.object.model !== currentData) MyCommands.objectCommand.setModel(root.object, currentData) }
        }

        model: mng.model
        currentIndex: mng.currentIndex
        onActivated: mng.currentIndex = currentIndex
    }
}
