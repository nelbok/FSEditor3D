import QtQuick

import editor

FSEEntity {
    property MyShape shape: null
    property alias filters: proxy.filters

    id: root

    entity: shape

    FSEComboBox {
        name: qsTr("Model")

        MyProxyModel {
            id: proxy
            sourceModel: MyModels.modelModel
        }

        MySelectionWrapper {
            id: mng
            model: proxy
            project: MyProject
            currentData: (root.shape) ? root.shape.model : null
            onCurrentUpdated: { if (root.shape && root.shape.model !== currentData) MyCommands.shapeCommand.setModel(root.shape, currentData) }
        }

        model: mng.model
        currentIndex: mng.currentIndex
        onActivated: mng.currentIndex = currentIndex
    }
}
