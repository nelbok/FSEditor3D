.pragma library
.import QtQuick as QtQ

// Global
var _cpt = null
var _models = []
var _scene = null

function setScene(scene) {
    _scene = scene
}

function clean() {
    for (var m in _models) {
        _models[m].destroy()
    }
    _models = []
}

function load(url) {
    clean()
    _cpt = Qt.createComponent(url)

    if (_cpt.status === QtQ.Component.Error)
        console.log("Error while loading:" + _cpt.errorString())

    if (_cpt.status === QtQ.Component.Ready)
        finishLoading()
    else
        _cpt.statusChanged.connect(finishLoading)
}

function finishLoading() {
    if (_cpt.status === QtQ.Component.Ready) {
        var model = _cpt.createObject(_scene)
        // FIXME: Tmp
        model.scale = Qt.vector3d(100, 100, 100)
        _models.push(model)
    } else if (cpt.status === QtQ.Component.Error) {
        console.log("Error while loading:" + _cpt.errorString())
    } else {
        console.log("Something wrong...")
    }
    _cpt.destroy()
    _cpt = null
}
