import qbs 1.0

Project {
    name: "Browser"

    readonly property string version: "0.0.0"

    property bool withFluid: false

    minimumQbsVersion: "1.6"

    qbsSearchPaths: "qbs/shared"

    references: [
        "res/res.qbs",
        "src/src.qbs",
    ]

    SubProject {
        filePath: "fluid/fluid.qbs"

        Properties {
            condition: withFluid ||
                       qbs.targetOS.contains("windows") ||
                       qbs.targetOS.contains("macos") ||
                       qbs.targetOS.contains("android")
            autotestEnabled: false
            deploymentEnabled: false
            withDocumentation: false
            withDemo: false
        }
    }
}