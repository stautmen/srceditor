#include <QGuiApplication>
#include <QtQml>
#include <QQmlApplicationEngine>
#include "chessman.h"
#include "chessgame.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<QQmlApplicationEngine>("Screenloader",1,0,"ScreenLoader");
    qmlRegisterType<Chessman>("Chesspieces", 1, 0, "Chessman");
    qmlRegisterType<ChessGame>("Chessgame", 1, 0, "ChessGame");
    engine.load(QUrl(QStringLiteral("qrc:/screenOne.qml")));

    return app.exec();
}
