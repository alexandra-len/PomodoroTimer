#include "pomodorotimer.h"

PomodoroTimer::PomodoroTimer(QObject *parent, QTime workMins, QTime breakMins, int pomodoros)
    : QObject(parent), pomodoroComplete(0)
{
    workTime = workMins;
    breakTime = breakMins;
    pomodoroMax = pomodoros;
    timer = new Timer(this);
    connect(timer, &Timer::finished, this, [this]() {onTimerEnd();});
    connect(timer, &Timer::tick, this, [this](QTime t) {emit pomodoroTick(t);});
}

void PomodoroTimer::start() {
    startTimerFromTime(workTime);
    isWorking = true;
    pomodoroComplete = 0;
}

void PomodoroTimer::stop() {
    if (timer->isTimerRunning())
    {
        timer->stop();
    }
}

void PomodoroTimer::skip() {
    onTimerEnd();
}

void PomodoroTimer::pause() {
    if (timer->isTimerRunning()) {
        timer->pause();
    }
    else {
        timer->resume();
    }
}

void PomodoroTimer::onTimerEnd() {
    if (isWorking) {
        pomodoroComplete++;
        isWorking = false;
        emit pomodoroSingleFinished();
        if (!isLastPomodoro()) {
            startTimerFromTime(breakTime);
        }
        else {
            emit pomodorosFinished();
        }
    }
    else {
        isWorking = true;
        startTimerFromTime(workTime);
    }
}

bool PomodoroTimer::isLastPomodoro() {
    return pomodoroComplete >= pomodoroMax;
}
void PomodoroTimer::startTimerFromTime(QTime timeToStart) {
    if (timer->isTimerRunning()) {
        timer->stop();
    }
    timer->start(timeToStart);
}

void PomodoroTimer::setWorkTime(QTime workMins) {
    workTime = workMins;
}

void PomodoroTimer::setBreakTime(QTime breakMins) {
    breakTime = breakMins;
}

void PomodoroTimer::setPomodoroCount(int pomodoroCount) {
    pomodoroMax = pomodoroCount;
}

int PomodoroTimer::getPomodorosLeft() {
    return pomodoroMax - pomodoroComplete;
}

bool PomodoroTimer::isRunning() {
    return timer->isTimerRunning();
}
