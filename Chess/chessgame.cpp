#include "chessgame.h"
#include <QDebug>
#include <QDialog>
#include <QVBoxLayout>
#include <QListWidget>
#include <QApplication>

ChessGame::ChessGame(QObject *parent) : QObject(parent)
{
    currentStep = 0;
    restoreBoard();
}

void ChessGame::clearPossibleMoves()
{
    for(Chessman *i:history[currentStep])
    {
        if(i->getType()=="MovePlace")
            i->setType("Empty");
        i->setPlace(false);
    }
}

void ChessGame::restoreBoard()
{
    QString tempBoard[8][8] = { { "Rook" , "Knight" , "Bishop" , "Queen" , "King" , "Bishop" , "Knight" , "Rook" },
                              { "Pawn" , "Pawn" , "Pawn" , "Pawn" , "Pawn" , "Pawn" , "Pawn" , "Pawn" },
                              { "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty",},
                              { "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty",},
                              { "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty",},
                              { "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty",},
                              { "Pawn" , "Pawn" , "Pawn" , "Pawn" , "Pawn" , "Pawn" , "Pawn" , "Pawn" },
                              { "Rook" , "Knight" , "Bishop" , "Queen" , "King" , "Bishop" , "Knight" , "Rook" }};
    history.clear();
    Chessman *chessman;
    QVector<Chessman*> temp;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            chessman = new Chessman;
            if(i==0||i==1)
                chessman->setSide("White");
            else if(i==6||i==7)
                chessman->setSide("Black");
            else
                chessman->setSide("No");
            chessman->setPositionX(i);
            chessman->setPositionY(j);
            chessman->setType(tempBoard[i][j]);
            temp.append(chessman);
        }
    }

    history.append(temp);
}

QString ChessGame::chessPieceAt(int index)
{
    return history[currentStep][index]->getType();
}

QString ChessGame::chessSideAt(int index)
{
    return history[currentStep][index]->getSide();
}

int ChessGame::getHistoryLenght()
{
    return history.length();
}

int ChessGame::getStep()
{
    return currentStep;
}

void ChessGame::setStep(int step)
{
    if(step<0||step>=history.length())
        return;
    else
        currentStep = step;
}
void ChessGame::setChessPieceAt(int index,QString t)
{
    history[currentStep][index]->setType(t);
}

bool ChessGame::checkMove(int from, int to,QString s)
{
    QVector<Chessman*> temp;
    Chessman *chess;
    for(int i=0;i<64;i++)
    {
        chess = new Chessman;
        chess->setType(history[currentStep][i]->getType());
        chess->setSide(history[currentStep][i]->getSide());
        chess->setPlace(history[currentStep][i]->isPlace());
        chess->setPositionX(history[currentStep][i]->getPositionX());
        chess->setPositionY(history[currentStep][i]->getPositionY());
        temp.append(chess);
    }
    history.append(temp);

    currentStep = history.length()-1;

    if(history[currentStep][to]->isPlace())
    {

        if(history[currentStep][from]->getType()=="Pawn")
        {
            if( (to<8&&history[currentStep][from]->getSide()=="Black") || (to>55&&history[currentStep][from]->getSide()=="White"))
            {toPlace = to; emit pawnChange(to);}
        }

        clearPossibleMoves();
        checkWinner(to);
        return moveAndSave(from,to);
    }
    else
        return false;
}

void ChessGame::saveGame()
{
    qDebug()<<"save";
    QFile file("history.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    for(int i=0;i<history.length();i++)
    {
        for(int j=0;j<history[i].length();j++)
        {
            if(history[i][j]->getType()=="MovePlace")
                out<<"Empty"<<" ";
            else
                out<<history[i][j]->getType()<<" ";
            out<<history[i][j]->getSide()<<" ";
            qDebug()<<"here";
        }
    }
    file.close();
}

void ChessGame::loadGame()
{
    currentStep = 0;
    history.clear();
    QFile file("history.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList t;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        t.append(line.split(" "));
    }
    t.removeLast();

    int j=0;
    QVector<Chessman*> temp;
    Chessman *chessman;

    for(int i=0;i<t.length()-1;i+=2)
    {
        chessman = new Chessman;
        chessman->setType(t[i]);
        chessman->setSide(t[i+1]);
        temp.append(chessman);
        j+=2;
        if(j==128)
        {
            qDebug()<<temp.length();
            currentStep++;
            history.append(temp);
            temp.clear();
            j=0;
        }
    }
    currentStep--;
    qDebug()<<history.length();
    emit historyLoaded();
}

bool ChessGame::moveAndSave(int from, int to)
{
    int x = history[currentStep][to]->getPositionX();
    int y = history[currentStep][to]->getPositionY();
    history[currentStep][to]->setPositionX(history[currentStep][from]->getPositionX());
    history[currentStep][to]->setPositionY(history[currentStep][from]->getPositionY());
    history[currentStep][from]->setPositionX(x);
    history[currentStep][from]->setPositionY(y);
    history[currentStep][to]->setType(history[currentStep][from]->getType());
    history[currentStep][from]->setType("Empty");
    history[currentStep][to]->setSide(history[currentStep][from]->getSide());

    history[currentStep][from]->setPositionX(history[currentStep][to]->getPositionX());
    history[currentStep][from]->setPositionY(history[currentStep][to]->getPositionY());

    return true;
}

void ChessGame::checkWinner(int to)
{
    if(history[currentStep][to]->getType()=="King")
    {
        if(history[currentStep][to]->getSide() == "Black")
            emit whiteWin();
        else
            emit blackWin();
    }
}

void ChessGame::generatePossibleMoves(int from,QString side)
{
    clearPossibleMoves();
    int it=0;
    Chessman *tempBoard[8][8];
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            history[currentStep][it]->setPositionX(i);
            history[currentStep][it]->setPositionY(j);
            tempBoard[i][j]=history[currentStep][it];
            it++;
        }
    }


    int row = history[currentStep][from]->getPositionX();
    int column = history[currentStep][from]->getPositionY();


    if(history[currentStep][from]->getType()=="Bishop"||history[currentStep][from]->getType()=="Queen")
    {
            for (int j = column + 1, i = row + 1; j < 8 && i < 8; j++, i++) {

                if (tempBoard[i][j]->getType()=="Empty") {
                    tempBoard[i][j]->setType("MovePlace");
                    tempBoard[i][j]->setPlace(true);
                } else if (tempBoard[i][j]->getSide()!=side) {
                    tempBoard[i][j]->setPlace(true);
                    break;
                } else {
                    break;
                }
            }
            for (int j = column - 1, i = row + 1; j > -1 && i < 8; j--, i++) {
                if (tempBoard[i][j]->getType()=="Empty") {
                    tempBoard[i][j]->setType("MovePlace");
                    tempBoard[i][j]->setPlace(true);
                } else if (tempBoard[i][j]->getSide()!=side) {
                    tempBoard[i][j]->setPlace(true);
                    break;
                } else {
                    break;
                }
            }
            for (int j = column - 1, i = row - 1; j > -1 && i > -1; j--, i--) {
                if (tempBoard[i][j]->getType()=="Empty") {
                    tempBoard[i][j]->setType("MovePlace");
                    tempBoard[i][j]->setPlace(true);
                } else if (tempBoard[i][j]->getSide()!=side) {
                    tempBoard[i][j]->setPlace(true);
                    break;
                } else {
                    break;
                }
            }
            for (int j = column + 1, i = row - 1; j < 8 && i > -1; j++, i--) {
                if (tempBoard[i][j]->getType()=="Empty") {
                    tempBoard[i][j]->setType("MovePlace");
                    tempBoard[i][j]->setPlace(true);
                } else if (tempBoard[i][j]->getSide()!=side) {
                    tempBoard[i][j]->setPlace(true);
                    break;
                } else {
                    break;
                }
            }
    }
    if(history[currentStep][from]->getType()=="Rook"||history[currentStep][from]->getType()=="Queen")
    {
        for (int i = row + 1; i < 8; i++) {
                  if (tempBoard[i][column]->getType()=="Empty") {
                      tempBoard[i][column]->setType("MovePlace");
                      tempBoard[i][column]->setPlace(true);
                  } else if (tempBoard[i][column]->getSide()!=side) {
                      tempBoard[i][column]->setPlace(true);
                      break;
                  } else {
                      break;
                  }
              }
              for (int i = row - 1; i > -1; i--) {
                  if (tempBoard[i][column]->getType()=="Empty") {
                      tempBoard[i][column]->setType("MovePlace");
                      tempBoard[i][column]->setPlace(true);
                  } else if (tempBoard[i][column]->getSide()!=side) {
                      tempBoard[i][column]->setPlace(true);
                      break;
                  } else {
                      break;
                  }
              }
              for (int i = column + 1; i < 8; i++) {
                  if (tempBoard[row][i]->getType()=="Empty") {
                      tempBoard[row][i]->setType("MovePlace");
                      tempBoard[row][i]->setPlace(true);
                  } else if (tempBoard[row][i]->getSide()!=side) {
                      tempBoard[row][i]->setPlace(true);
                      break;
                  } else {
                      break;
                  }
              }
              for (int i = column - 1; i > -1; i--) {
                  if (tempBoard[row][i]->getType()=="Empty") {
                      tempBoard[row][i]->setType("MovePlace");
                      tempBoard[row][i]->setPlace(true);
                  } else if (tempBoard[row][i]->getSide()!=side) {
                      tempBoard[row][i]->setPlace(true);
                      break;
                  } else {
                      break;
                  }
              }
    }
    else if(history[currentStep][from]->getType()=="Knight")
    {
        int offsets[8][2] = {
             {-2, 1},
             {-1, 2},
             {1, 2},
             {2, 1},
             {2, -1},
             {1, -2},
             {-1, -2},
             {-2, -1}
         };


        for(int i=0;i<8;i++)
        {
            if((row+offsets[i][0]<8&&row+offsets[i][0]>=0)&&(column+offsets[i][1]<8&&column+offsets[i][1]>=0))
            {
                qDebug()<<row+offsets[i][0];
                if(tempBoard[row+offsets[i][0]][column+offsets[i][1]]->getType()=="Empty")
                {
                    tempBoard[row+offsets[i][0]][column+offsets[i][1]]->setPlace(true);
                    tempBoard[row+offsets[i][0]][column+offsets[i][1]]->setType("MovePlace");
                }
                else if(tempBoard[row+offsets[i][0]][column+offsets[i][1]]->getType()!="Empty"&&tempBoard[row+offsets[i][0]][column+offsets[i][1]]->getSide()!=side)
                    tempBoard[row+offsets[i][0]][column+offsets[i][1]]->setPlace(true);
            }
        }

    }
    else if(history[currentStep][from]->getType()=="King")
    {
        int offsets[8][2] = {
                    {1, 0},
                    {0, 1},
                    {-1, 0},
                    {0, -1},
                    {1, 1},
                    {-1, 1},
                    {-1, -1},
                    {1, -1}
                };


        for(int i=0;i<8;i++)
        {
            if((row+offsets[i][0]<8&&row+offsets[i][0]>=0)&&(column+offsets[i][1]<8&&column+offsets[i][1]>=0))
            {
                if(tempBoard[row+offsets[i][0]][column+offsets[i][1]]->getType()=="Empty")
                {
                    tempBoard[row+offsets[i][0]][column+offsets[i][1]]->setPlace(true);
                    tempBoard[row+offsets[i][0]][column+offsets[i][1]]->setType("MovePlace");
                }
                else if(tempBoard[row+offsets[i][0]][column+offsets[i][1]]->getType()!="Empty"&&tempBoard[row+offsets[i][0]][column+offsets[i][1]]->getSide()!=side)
                    tempBoard[row+offsets[i][0]][column+offsets[i][1]]->setPlace(true);
            }
        }

    }
    else if(history[currentStep][from]->getType()=="Pawn")
    {
        int coeff;
        int offside;
        if(side=="Black")
           coeff=-1;
        if(side=="White")
            coeff=1;


        if( (from+(16*coeff))>=0 && (from+(16*coeff))<64 )
        {
            if(((row==6&&side=="Black") || (row==1&&side=="White"))&&history[currentStep][from+(16*coeff)]->getType()=="Empty")
            {
                if( history[currentStep][from+(8*coeff)]->getType()=="Empty" )
                {
                history[currentStep][from+(16*coeff)]->setType("MovePlace");
                history[currentStep][from+(16*coeff)]->setPlace(true);
                }
            }
        }

        if( (from+(8*coeff))>=0 && (from+(8*coeff))<64 )
        {
            if(history[currentStep][from+(8*coeff)]->getType()=="Empty")
            {
                history[currentStep][from+(8*coeff)]->setType("MovePlace");
                history[currentStep][from+(8*coeff)]->setPlace(true);
            }
        }

        if( (from+(7*coeff))>=0 && (from+(7*coeff))<64 )
        {
            if(history[currentStep][from+(7*coeff)]->getType()!="Empty"&&history[currentStep][from+(7*coeff)]->getSide()!=history[currentStep][from]->getSide())
            {
                history[currentStep][from+(7*coeff)]->setPlace(true);
            }
        }

        if( (from+(9*coeff))>=0 && (from+(9*coeff))<64 )
        {
            if(history[currentStep][from+(9*coeff)]->getType()!="Empty"&&history[currentStep][from+(9*coeff)]->getSide()!=history[currentStep][from]->getSide())
            {
                history[currentStep][from+(9*coeff)]->setPlace(true);
            }
        }
    }
}

int ChessGame::getToPlace()
{
    return toPlace;
}
