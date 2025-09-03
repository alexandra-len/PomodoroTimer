#ifndef POMODOROTIMER_H
#define POMODOROTIMER_H

#include <QObject>
#include <QTime>
#include "timer.h"

class PomodoroTimer : public QObject
{
    Q_OBJECT
public:
    PomodoroTimer(QObject *parent = nullptr, QTime workMins = QTime(0,25,0), QTime breakMins = QTime(0,5,0), int pomodoros = 4);

    void start(); // start pomodoro sessions
    void stop(); // stop
    void skip(); // skip current session
    void pause(); // pause current timer
    void continueTimer();
    void startTimerFromTime(QTime);
    void onTimerEnd();
    void onTimerSkipped();
    bool isLastPomodoro();
    bool isRunning();

    void setWorkTime(QTime);
    void setBreakTime(QTime);
    void setPomodoroCount(int);
    void setContinueAutomatically(bool);

    int getPomodorosLeft();

signals:
    void pomodorosFinished();
    void pomodoroTick(QTime);
    void pomodoroSingleFinished(bool, bool);
    void breakFinished(bool, bool);
    void timerStarted(QTime);

private:
    QTime workTime;
    QTime breakTime;
    int pomodoroMax;
    int pomodoroComplete;
    Timer *timer;
    bool isWorking;
    bool continueAutomatically;
};

#endif // POMODOROTIMER_H
