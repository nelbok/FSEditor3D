import QtQuick
import QtQuick3D

Node {
    id: node

    // Resources
    PrincipledMaterial {
        id: mat_material
        objectName: "Mat"
        baseColor: "#ffffaa00"
        indexOfRefraction: 1
    }

    // Nodes:
    Node {
        id: link_obj
        objectName: "Link.obj"
        Node {
            id: link
            objectName: "Link"
        }
        Model {
            id: mat
            objectName: "Mat"
            source: "meshes/mat_mesh.mesh"
            materials: [
                mat_material
            ]
        }
    }

    // Animations:
}
