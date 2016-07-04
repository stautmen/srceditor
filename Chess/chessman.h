#ifndef CHESSMAN_H
#define CHESSMAN_H

#include <QObject>
#include <QPixmap>
#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QPainter>

class Chessman : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(qint16 posX READ getPositionX WRITE setPositionX)
    Q_PROPERTY(qint16 posY READ getPositionY WRITE setPositionY)
    Q_PROPERTY(QString chessPiece READ getType WRITE setType)
    Q_PROPERTY(QString side READ getSide WRITE setSide)
public:
    explicit Chessman(QQuickItem *parent = 0);
    void paint(QPainter *painter);
    void setType(const QString);
    void setSide(QString);
    QString getSide();
    QString getType();
    const qint16 getPositionX();
    const qint16 getPositionY();
    void setPlace(bool);
    bool isPlace();
signals:

public slots:
    void setPositionX(qint16 x);
    void setPositionY(qint16 y);
private:
    qint16 positionX;
    qint16 positionY;
    QString type;
    QString c_side;
    int it;
    bool movePlace;
};

#endif // CHESSMAN_H
