import QtQuick 2.4
import QtQuick.Window 2.2
import Chesspieces 1.0
import Chessgame 1.0
import QtQuick.Controls 1.3
import Screenloader 1.0
import QtQuick.Dialogs 1.1
import QtQuick.Dialogs 1.2

Window {
    id : wd
    width : 435
    height: 455
    visible: true

    ChessGame {
        id: game
        property string currentPlayer: "Black"
        property int selectedIndex: 0
        property bool selectionSaved: false
        property bool selected: false
        onBlackWin: {messageDialog.setText("Black won!")
                        messageDialog.visible = true}
        onWhiteWin: {messageDialog.setText("White won!")
                        messageDialog.visible = true}
        onPawnChange:{pChange.visible = true}
    }

    MessageDialog {
        id: messageDialog
        title: "Game Over"
        onAccepted: {
            console.log("And of course you could only agree.")
            Qt.quit()
        }
    }

    Dialog {
        visible: false
        id: pChange
        title: "Change pawn"

        contentItem: Rectangle {
            color: "gray"
            implicitWidth: 320
            implicitHeight: 80
            Button {
                 x: 0
                 width: 80
                 height: 80
                 text : "Rook"
                 onClicked: {
                     pChange.visible = false;
                     game.setChessPieceAt(game.getToPlace(),"Rook");
                     var newBoard = [];
                     for(var i=0;i<64;++i)
                     {
                         newBoard[i]= game.chessPieceAt(i);
                     }

                     boardRepeater.model = newBoard;}
            }
            Button {
                width: 80
                height: 80
                 x: 80
                 text : "Bishop"
                 onClicked: {
                     pChange.visible = false;
                     game.setChessPieceAt(game.getToPlace(),"Bishop");
                     var newBoard = [];
                     for(var i=0;i<64;++i)
                     {
                         newBoard[i]= game.chessPieceAt(i);
                     }

                     boardRepeater.model = newBoard;}
            }
            Button {
                width: 80
                height: 80
                 x: 160
                 text : "Knight"
                 onClicked: {
                     pChange.visible = false;
                     game.setChessPieceAt(game.getToPlace(),"Knight");
                     var newBoard = [];
                     for(var i=0;i<64;++i)
                     {
                         newBoard[i]= game.chessPieceAt(i);
                     }

                     boardRepeater.model = newBoard;}
            }
            Button {
                width: 80
                height: 80
                 x: 240
                 text : "Queen"
                 onClicked: {
                     pChange.visible = false;
                     game.setChessPieceAt(game.getToPlace(),"Queen");
                     var newBoard = [];
                     for(var i=0;i<64;++i)
                     {
                         newBoard[i]= game.chessPieceAt(i);
                     }

                     boardRepeater.model = newBoard;}
            }
        }
    }

    ScreenLoader {
        id: screenLoader
    }

    Row {
        height: 10
        x:35
        Text { text: "a"; width:50;}
        Text { text: "b"; width:50;}
        Text { text: "c"; width:50;}
        Text { text: "d"; width:50;}
        Text { text: "e"; width:50;}
        Text { text: "f"; width:50;}
        Text { text: "g"; width:50;}
        Text { text: "h"; width:50;}
    }
    Column {
        y:35
        Text { text: "8"; height:50;}
        Text { text: "7"; height:50;}
        Text { text: "6"; height:50;}
        Text { text: "5"; height:50;}
        Text { text: "4"; height:50;}
        Text { text: "3"; height:50;}
        Text { text: "2"; height:50;}
        Text { text: "1"; height:50;}
    }

    Grid {
        id: board
        y: 20
        x: 20
        rows: 8; columns: 8
        property alias model: repeater.model
        signal clicked(int square)

        Repeater {
            id : repeater

            model: {
                var board = []
                for(var i=1;i<64;++i)
                    board[i]="empty";
                board;
            }
            Rectangle {
                width: 50; height: 50
                color: {
                    var row = Math.floor(index/8);
                    var column = index % 8
                    if((row+column) % 2 == 1)
                        repeater.model[index] = "darkgray";
                    else
                        repeater.model[index] = "white";

                }
            }
        }
    }

    Grid {
        id: chessBoard
        anchors.bottomMargin: 10
        y: 20
        x: 20
        rows: 8; columns: 8
        property alias model: boardRepeater.model
        property int clickedIndex: 0
        signal clicked(int square)

        Repeater {
            id : boardRepeater

            model: {

                var board = ["Rook" , "Knight" , "Bishop" , "Queen" , "King" , "Bishop" , "Knight" , "Rook" ,
                              "Pawn" , "Pawn" , "Pawn" , "Pawn" , "Pawn" , "Pawn" , "Pawn" , "Pawn" ,
                              "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty",
                              "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty",
                              "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty",
                              "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty",
                              "Pawn" , "Pawn" , "Pawn" , "Pawn" , "Pawn" , "Pawn" , "Pawn" , "Pawn",
                              "Rook" , "Knight" , "Bishop" , "Queen" , "King" , "Bishop" , "Knight" , "Rook"];
                board;
            }

            Chessman {
                id: chess
                width:50
                height:50
                x:100
                y:100
                property int moveX: 0
                property int moveY: 0
                property int oldPos: 0
                property int newPos: 0
                property bool selected: false
                side: {
                    boardRepeater.model[index] = game.chessSideAt(index)
                }

                chessPiece: boardRepeater.model[index]

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(game.selected)
                        {
                            console.log(game.selectedIndex,index)
                            if(boardRepeater.itemAt(index).chessPiece == "MovePlace"||boardRepeater.itemAt(index).chessPiece == "Empty"||boardRepeater.itemAt(index).side != game.currentPlayer||boardRepeater.itemAt(index).chessPiece=="MovePlace")
                            {
                                if(game.checkMove(game.selectedIndex,index,game.currentPlayer))
                                {
                                    (Math.floor(game.selectedIndex/8) + (game.selectedIndex%8)) % 2 == 1 ? repeater.itemAt(game.selectedIndex).color = "darkgray" : repeater.itemAt(game.selectedIndex).color = "white";
                                    game.currentPlayer == "Black" ? game.currentPlayer = "White" : game.currentPlayer = "Black";
                                    boardRepeater.itemAt(game.selectedIndex).y = (Math.floor(index/8) * 50);
                                    boardRepeater.itemAt(game.selectedIndex).x = (index % 8 * 50);
                                    game.selected = false;
                                    game.selectionSaved = false;
                                    var newBoard = [];
                                    for(var i=0;i<64;++i)
                                    {
                                        newBoard[i]= game.chessPieceAt(i);
                                    }

                                    boardRepeater.model = newBoard;

                                }
                                else
                                {
                                    (Math.floor(game.selectedIndex/8) + (game.selectedIndex%8)) % 2 == 1 ? repeater.itemAt(game.selectedIndex).color = "darkgray" : repeater.itemAt(game.selectedIndex).color = "white";
                                    game.selected = false;
                                    game.selectionSaved = false;
                                    game.clearPossibleMoves();

                                    var newBoard = [];
                                    for(var i=0;i<64;++i)
                                    {
                                        newBoard[i]= game.chessPieceAt(i);
                                    }

                                    boardRepeater.model = newBoard;
                                }
                            }
                              console.log("selected")
                        }
                        else
                        {
                          if(boardRepeater.itemAt(index).side == game.currentPlayer&&boardRepeater.itemAt(index).chessPiece != "Empty")
                          {

                                game.selected = true;
                                repeater.itemAt(index).color = "green";


                              if(!game.selectionSaved){
                                console.log("new index")
                                game.selectedIndex = index;
                                  game.selectionSaved = true;
                              }
                              game.generatePossibleMoves(game.selectedIndex,game.currentPlayer);
                              console.log("selection at "+game.selectedIndex);
                              var newBoard = [];
                              for(var i=0;i<64;++i)
                              {
                                  newBoard[i]= game.chessPieceAt(i);
                              }

                              boardRepeater.model = newBoard;

                          }
                        }
                    }
                }

            }
        }
    }

    Button {
        x: 200
        y: 425
        text: "Stop"
        onClicked: {screenLoader.load("../Chess/screenOne.qml")
        wd.visible = false}
    }
    Button {
        text: "Save"
        onClicked:{ game.saveGame()
                    console.log("saving")}
        x: 300
        y: 425
    }
    Text {
        x: 10
        y : 430
        text : "Current player:" + game.currentPlayer
    }

}
