import QtQuick
import QtQuick3D

Node {
    id: node

    // Resources
    PrincipledMaterial {
        id: mat_material
        objectName: "mat"
        baseColor: "#ffffaa00"
        indexOfRefraction: 1
    }

    // Nodes:
    Node {
        id: a_obj
        objectName: "A.obj"
        Node {
            id: sample
            objectName: "Sample"
        }
        Model {
            id: mat
            objectName: "mat"
            source: "meshes/mat_mesh.mesh"
            materials: [
                mat_material
            ]
        }
    }

    // Animations:
}
