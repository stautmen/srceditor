#include "chessman.h"

Chessman::Chessman(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    movePlace = false;
    c_side = "Black";
    type = "Empty";
}

void Chessman::setType(const QString t)
{
    type = t;
}

void Chessman::setSide(QString s)
{
    c_side = s;
}

QString Chessman::getSide()
{
    return c_side;
}

QString Chessman::getType()
{
    return type;
}

const qint16 Chessman::getPositionX()
{
    return positionX;
}

const qint16 Chessman::getPositionY()
{
    return positionY;
}

void Chessman::setPlace(bool flag)
{
    movePlace = flag;
}

bool Chessman::isPlace()
{
    return movePlace;
}

void Chessman::setPositionX(qint16 x)
{
    positionX = x;
}

void Chessman::setPositionY(qint16 y)
{
    positionY = y;
}

void Chessman::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    QStringList option;
    option << "Bishop" << "Pawn" << "King" << "Knight" << "Queen" << "Rook" << "MovePlace";

    switch (option.indexOf(type)) {
    case 0:
            painter->drawPixmap(0,0,50,50,QPixmap(QString("../Chess/img/bishop%1.png").arg(c_side)));
        break;
    case 1:
            painter->drawPixmap(0,0,50,50,QPixmap(QString("../Chess/img/pawn%1.png").arg(c_side)));
        break;
    case 2:
            painter->drawPixmap(0,0,50,50,QPixmap(QString("../Chess/img/king%1.png").arg(c_side)));
        break;
    case 3:
            painter->drawPixmap(0,0,50,50,QPixmap(QString("../Chess/img/knight%1.png").arg(c_side)));
        break;
    case 4:
            painter->drawPixmap(0,0,50,50,QPixmap(QString("../Chess/img/queen%1.png").arg(c_side)));
        break;
    case 5:
            painter->drawPixmap(0,0,50,50,QPixmap(QString("../Chess/img/rook%1.png").arg(c_side)));
        break;
    case 6:
            painter->setBrush(Qt::lightGray); painter->drawEllipse(22.5,22.5,5,5);
        break;
    default: break;
    }
}

