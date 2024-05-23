#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


#include "monthcalendar.h"
#include "EventManager.h"
// #include <QQmlComponent>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // menu menu;

    MonthCalendar calendar;
    EventManager eventManager;
    qmlRegisterType<MonthCalendar>("MonthCalendar", 1, 0, "MonthCalendar");
    qmlRegisterType<Q_Event>("Q_Event", 1, 0, "Q_Event");
    qmlRegisterType<EventManager>("EventManager", 1, 0, "EventManager");
    // qmlRegisterType<Date>("DateClass", 1, 0, "DateClass");

    // engi?ne.setInitialProperties({{ "eventDatabase", QVariant::fromValue(&eventDatabase) }});

    // qmlRegisterType<>("com.example", 1, 0, "MyComponent");

    const QUrl url(u"qrc:/TimeSync/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    QQmlContext * rootContext = engine.rootContext();

    // rootContext->setContextProperty("menu", &menu);
    // rootContext->setContextProperty("monthCalendar", &calendar);
    //engine.rootContext()->setContextProperty("eventManager", &eventManager);

    return app.exec();
}
