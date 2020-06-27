#pragma warning ( disable : 26444 )

#include <QNetworkRequest>
#include <QQmlContext>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

#include "Core.h"


Core::Core(QObject *parent) : QObject(parent)
{
    self.connect(this, &Core::sigStartSearch, [this]() {
        mTimer.clear(); // clears out recored lap times
        mTimer.reset(); // resets the timer to 0
    });

    self.connect(this, &Core::sigEndSearch, [this]() {
        self.SetStopClock();
    });
}

Core::~Core()
{
}

bool Core::initialize()
{
    mEngine.rootContext()->setContextProperty("vDisplayTimer", QVariant::fromValue(QString("Exe Time : Never Run")));
    
    mEngine.rootContext()->setContextProperty("Core", this);

    mEngine.load(QUrl(QStringLiteral("qrc:/view/main.qml")));
    if (mEngine.rootObjects().isEmpty()) 
        return false;
    else 
        return true;
}

Q_INVOKABLE 
void Core::Generate()
{
    emit self.sigGenerate();
    return Q_INVOKABLE void();
}

Q_INVOKABLE 
void Core::FindNumberSequence()
{
    emit self.sigStartSearch();
    uint location = Algo::FindDisplayStr(mUseThreading, mUseEightNums);
    emit self.sigEndSearch();
    cout << "loc: " << location << endl;
    emit self.sigHighlightNumberSequence(location);
    emit self.sigDisplayNumChanged(self.DisplayNum());
    return Q_INVOKABLE void();
}

QString Core::AllNumbers() const {
    return  Algo::GetAllNumbers().c_str();
}

double Core::StopClock() const
{
    if (mTimer.get_xvector().size())
        return mTimer.get(0);
    else
        return 0;
}

QString Core::DisplayNum() const 
{
    if (!Algo::GetDisplayStr().size())
        return QString("[ Number ]");

    return Algo::GetDisplayStr().c_str();
}

bool Core::UseThreading() const {
    return mUseThreading;
}

bool Core::UseEightNums() const {
    return mUseEightNums;
}

void Core::SetAllNumbers(const QString& str){
    Algo::SetAllNumbers(str.toStdString());
    emit sigAllNumbersChanged(Algo::GetAllNumbers().c_str());
}

void Core::SetStopClock(uint unused)
{
    mTimer.lap(); // recoreds the stopwatch

    // emit self.sigStopClockChanged(mTimer.get(0)); // I prefer the method below
    mEngine.rootContext()->setContextProperty("vDisplayTimer", QVariant::fromValue(
        QString("Exe Time: ") + QString::number(mTimer.get(0), 'd', 3)
        //QString("Exe Time: ")+ QString::number(mTimer.get(0))
    ));
}

void Core::SetUseThreading(bool truth)
{
    mUseThreading = truth;
    emit sigUseThreadingChanged(mUseThreading);
}

void Core::SetUseEightNums(bool truth)
{
    mUseEightNums = truth;
    emit sigUseEightNumsChanged(mUseEightNums);
}

