#ifndef POMODOROSESSION_H
#define POMODOROSESSION_H

#include "timer.h"

class PomodoroSession : public QObject
{
    Q_OBJECT
public:
    PomodoroSession(QObject *parent = nullptr, QTime duration = QTime(0,0,0));
    void start();
    void stop();
    void pause();
    void resume();

private:
    Timer *timer;
    QTime duration;

signals:
    void tick(QTime remaining);
    void sessionEnd();

};

#endif // POMODOROSESSION_H
