import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Window {
    visible: true
    width: 400
    height: 450
    title: "Tres en Raya"

    property bool showGameOver: false

    ColumnLayout {
        anchors.fill: parent
        spacing: 10


        RowLayout {
            Layout.alignment: Qt.AlignCenter
            spacing: 20

            Text {
                text: "Modo de juego:"
                font.pixelSize: 16
            }

            ComboBox {
                id: modeSelector
                model: ["2 Jugadores", "Jugador vs IA"]
                onCurrentIndexChanged: {
                    gameLogic.vsAI = (currentIndex === 1)
                    gameLogic.reset()
                    showGameOver = false
                }
            }
        }

        GridLayout {
            id: board
            Layout.fillWidth: true
            Layout.fillHeight: true
            rows: 3
            columns: 3

            Repeater {
                model: 9

                TresEnRayaBox {
                    required property int index
                    id: box
                    boxIndex: index
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    mark: gameLogic.markAt(index)

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            gameLogic.playAt(index)
                        }
                    }

                    Connections {
                        target: gameLogic
                        function onMarkChanged(i) {
                            if (i === index)
                                box.mark = gameLogic.markAt(index)
                        }
                        function onBoardChanged() {
                            box.mark = ""
                        }
                        function onGameOverChanged() {
                                   if (gameLogic.gameOver)
                                       showGameOver = true;
                                   else
                                       showGameOver = false;

                               }
                    }
                }
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignCenter
            spacing: 50

            Text {
                text: gameLogic.gameOver ? "Ganador: " + gameLogic.winner : "Turno: " + gameLogic.currentPlayer
                font.pixelSize: 18
            }

            Button {
                text: "Reiniciar"
                onClicked: gameLogic.reset()
            }
        }

    }

    Text {
        anchors.centerIn: parent
        visible: showGameOver
        text: "GAME OVER"
        font.pixelSize: Math.min(parent.width, parent.height) * 0.15
        color: "red"
        z: 999
    }
}
