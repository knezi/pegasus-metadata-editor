import QtQuick 2.0
import QtQuick.Controls 2.12

Dialog {
    width: parent.width * 0.45
    anchors.centerIn: parent

    modal: true
    standardButtons: Dialog.Ok

    Label {
        anchors.fill: parent
        text: "<h2>Pegasus Metadata Editor</h2>"
            + "<br>A graphical editor for the Metadata files of the Pegasus frontend."
            + "<br>Visit us at <a href=\"https://pegasus-frontend.org\">https://pegasus-frontend.org</a>!"
            + "<br><br>Version %1 (%2)".arg(Api.gitRevision).arg(Api.gitDate)
            + "<br>Copyright \xa9 2019 Mátyás Mustoha"
            + "<br><br><i>This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.</i>"
        wrapMode: Text.Wrap
        horizontalAlignment: Text.AlignJustify
        onLinkActivated: Qt.openUrlExternally(link)
    }
}
