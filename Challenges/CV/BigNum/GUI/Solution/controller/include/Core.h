#ifndef Core_H
#define Core_H

#include <iostream>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QQmlApplicationEngine>

#include "Algo.h"
#include "xstring.h"
#include "Timer.h"


#define self (*this)
//#pragma comment(lib, "c:\\Source\\Contracts\\Corteva\\BigNum\\GUI\\Build\\Windows\\Debug\\Debug\\lib\\Algo.lib")


using std::cout;
using std::endl;

class Core : public QObject
{
    Q_OBJECT
    Q_PROPERTY(
        QString AllNumbers
        READ    AllNumbers
        WRITE   SetAllNumbers
        NOTIFY  sigAllNumbersChanged
    )

    Q_PROPERTY(
        uint    StopClock
        READ    StopClock
        WRITE   SetStopClock
        NOTIFY  sigStopClockChanged
    )

    Q_PROPERTY(
        QString DisplayNum
        READ    DisplayNum
        NOTIFY  sigDisplayNumChanged
    )

    Q_PROPERTY(
        bool    UseThreading
        READ    UseThreading
        WRITE   SetUseThreading
        NOTIFY  sigUseThreadingChanged
    )

    Q_PROPERTY(
        bool    UseEightNums
        READ    UseEightNums
        WRITE   SetUseEightNums
        NOTIFY  sigUseEightNumsChanged
    )

    QQmlApplicationEngine mEngine;
    Timer   mTimer;
    bool    mUseThreading = false;
    bool    mUseEightNums = false;

public:
    explicit Core(QObject* parent = nullptr);
    ~Core();
    bool initialize();

public slots:
    Q_INVOKABLE void Generate();
    Q_INVOKABLE void FindNumberSequence();

public:
    // QProperties Start --------------------------------------------
    QString  AllNumbers() const;
    double   StopClock() const;
    QString  DisplayNum() const;
    bool     UseThreading() const;
    bool     UseEightNums() const;

    void SetAllNumbers(const QString& str);
    void SetStopClock(uint unused = 0);
    void SetUseThreading(bool truth);
    void SetUseEightNums(bool truth);

signals: void sigAllNumbersChanged(const QString& str);
signals: void sigStopClockChanged(const double val);
signals: void sigDisplayNumChanged(const QString& str);
signals: void sigUseThreadingChanged(bool truth);
signals: void sigUseEightNumsChanged(bool truth);
    // QProperties End -----------------------------------------------

signals: void sigGenerate();
signals: void sigHighlightNumberSequence(uint location);
signals: void sigDisplayNumberFound();

signals: void sigStartSearch();
signals: void sigEndSearch();
};

#endif // Core_H
