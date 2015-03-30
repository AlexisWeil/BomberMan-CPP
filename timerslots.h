#ifndef TIMERSLOTS_H
#define TIMERSLOTS_H

#include <QObject>
#include <QTimer>
#include <QLabel>

class TimerSlots : public QObject
{
Q_OBJECT
public:
    explicit TimerSlots(QObject *parent = 0);

    QTimer *timer;
    QLabel *tonLabel;

signals:

public slots:
    void compter();

};

#endif // TIMERSLOTS_H
