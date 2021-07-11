#ifndef Core_H
#define Core_H

#include <type_traits>
#include <iostream>
#include <QObject>
#include <QtQml/QQmlApplicationEngine>

#include "Algo.h"
#include "xstring.h"
#include "Timer.h"


#define self (*this)


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
    virtual ~Core();
    bool initialize();

    // -------------------------------------------------------------------------
    // Invokables
public slots:
    Q_INVOKABLE void Generate();
    Q_INVOKABLE void FindNumberSequence();

public:
    // Invokables
    // -------------------------------------------------------------------------
    // QProperties Start 

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

    // QProperties End
    // -------------------------------------------------------------------------
    // QML Connection Signals Start

    signals: void sigGenerate(); 
    signals: void sigHighlightNumberSequence(uint location);
    signals: void sigDisplayNumberFound();
    
    // QML Connection Signals End
    // -------------------------------------------------------------------------
    // C++ Signals Start

    signals: void sigStartSearch(); // Used to reset timer
    signals: void sigEndSearch();   // Used to get time after search execution

    // C++ Signals End
    // -------------------------------------------------------------------------
};

#endif // Core_H
