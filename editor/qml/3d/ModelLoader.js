.pragma library
.import QtQuick as QtQ
.import QtQuick3D as QtQ3D

// Global
var _cptTransform = Qt.createComponent("FSETransformNode.qml")
var _cptMeshShape = Qt.createComponent("FSEMeshShape.qml")
var _cptModel = null
var _transforms = []
var _scene = null
var _datas = []
var _index = 0
var _current = null
var _progress = false;

function setScene(scene) {
    _scene = scene
}

function load(datas) {
    _datas = datas
    _index = 0
    if (!_progress)
        next();
}

function next() {
    _progress = true;
    if (_index == 0) {
        clean()
    }
    if (_index < _datas.length) {
        _current = _datas[_index]
        ++_index
        beginLoading()
    } else {
        _progress = false
        _current = null
    }
}

function clean() {
    for (var m in _transforms) {
        _transforms[m].destroy()
    }
    _transforms = []
    _current = null
}

function beginLoading() {
    _cptModel = Qt.createComponent(_current.model)

    if (_cptModel.status === QtQ.Component.Error)
        console.log("Error while loading:" + _cptModel.errorString())

    if (_cptModel.status === QtQ.Component.Ready)
        finishLoading()
    else
        _cptModel.statusChanged.connect(finishLoading)
}

function finishLoading() {
    if (_cptModel.status === QtQ.Component.Ready) {
        // Create FSETransformNode instance
        var transform = _cptTransform.createObject(_scene)
        transform.geometry = _current.geometry
        transform.offset = _current.offset
        _transforms.push(transform)

        // Create model instance
        var model = _cptModel.createObject(transform.innerNode)
        findModels(model, transform)
    } else if (cpt.status === QtQ.Component.Error) {
        console.log("Error while loading:" + _cptModel.errorString())
    } else {
        console.log("Something wrong...")
    }
    _cptModel.destroy()
    _cptModel = null
    next()
}

function findModels(node, transform) {
    if (node instanceof QtQ3D.Model) {
        var meshShape = _cptMeshShape.createObject(transform)
        meshShape.geometry = _current.geometry
        meshShape.offset = _current.offset
        meshShape.source = _current.basePath + "/" + node.source
        transform.collisionShapes.push(meshShape)
    }
    for (var i in node.children) {
        findModels(node.children[i], transform)
    }
}
