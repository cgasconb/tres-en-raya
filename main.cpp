#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "gamelogic.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    GameLogic gameLogic;
    engine.rootContext()->setContextProperty("gameLogic", &gameLogic);

    engine.load(QUrl(QStringLiteral("../../Main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
