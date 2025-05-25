#ifndef COUNTDOWNTIMER_H
#define COUNTDOWNTIMER_H

#include <QObject>

class CountdownTimer : public QObject
{
    Q_OBJECT
public:
    explicit CountdownTimer(QObject *parent = nullptr);

signals:
};

#endif // COUNTDOWNTIMER_H
