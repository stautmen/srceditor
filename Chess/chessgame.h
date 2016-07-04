#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <QObject>
#include <QVector>
#include "chessman.h"

class ChessGame : public QObject
{
    Q_OBJECT
public:
    explicit ChessGame(QObject *parent = 0);
signals:
    void boardChanged();
    void historyLoaded();
    void whiteWin();
    void blackWin();
    void pawnChange(int toPlace);
public slots:

    void clearPossibleMoves();
    void restoreBoard();
    QString chessPieceAt(int index);
    QString chessSideAt(int index);
    int getHistoryLenght();
    int getStep();
    void setStep(int step);
    void setChessPieceAt(int index, QString t);
    bool checkMove(int from, int to, QString s);
    void saveGame();
    void loadGame();
    bool moveAndSave(int,int);
    void checkWinner(int);
    void generatePossibleMoves(int, QString);
    int getToPlace();
private:
   Chessman board[8][8];
   QList<QVector<Chessman*>> history;
   int currentStep;
   QString selectedChesspiece;
   int selectedIndex;
   bool selected;
   int toPlace;
};

#endif // CHESSGAME_H
