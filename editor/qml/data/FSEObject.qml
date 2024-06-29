import QtQuick

import editor

FSEEntity {
    property MyObject object: null
    property alias filters: proxy.filters

    id: root

    entity: object

    FSEComboBox {
        name: qsTr("Model")

        MyProxyModel {
            id: proxy
            sourceModel: MyModels.modelModel
        }

        MySelectionWrapper {
            id: mng
            model: proxy
            currentData: (root.object) ? root.object.model : null
            onCurrentUpdated: { if (root.object && root.object.model !== currentData) MyCommands.objectCommand.setModel(root.object, currentData) }
        }

        model: mng.model
        currentIndex: mng.currentIndex
        onActivated: mng.currentIndex = currentIndex
    }
}
