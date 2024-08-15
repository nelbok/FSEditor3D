.pragma library
.import QtQuick as QtQ

// Global
var _cptTransform = null
var _cptModel = null
var _transforms = []
var _scene = null

function init() {
    _cptTransform = Qt.createComponent("FSETransformNode.qml")
}

function setScene(scene) {
    _scene = scene
}

function clean() {
    for (var m in _transforms) {
        _transforms[m].destroy()
    }
    _transforms = []
}

function load(url) {
    clean()
    _cptModel = Qt.createComponent(url)

    if (_cptModel.status === QtQ.Component.Error)
        console.log("Error while loading:" + _cptModel.errorString())

    if (_cptModel.status === QtQ.Component.Ready)
        finishLoading()
    else
        _cptModel.statusChanged.connect(finishLoading)
}

function finishLoading() {
    if (_cptModel.status === QtQ.Component.Ready) {
        var transform = _cptTransform.createObject(_scene)
        _cptModel.createObject(transform)
        _transforms.push(transform)
    } else if (cpt.status === QtQ.Component.Error) {
        console.log("Error while loading:" + _cptModel.errorString())
    } else {
        console.log("Something wrong...")
    }
    _cptModel.destroy()
    _cptModel = null
}
