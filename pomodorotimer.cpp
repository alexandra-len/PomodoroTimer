#include "pomodorotimer.h"
#include "timer.h"

PomodoroTimer::PomodoroTimer(QObject *parent, QTime workMins, QTime breakMins, int pomodoros)
    : QObject(parent), pomodoroComplete(0), continueAutomatically(false)
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
    onTimerSkipped();
}

void PomodoroTimer::pause() {
    if (timer->isTimerRunning()) {
        timer->pause();
    }
    else {
        timer->resume();
    }
}

void PomodoroTimer::continueTimer() {
    if (!isWorking) {
        startTimerFromTime(breakTime);
    }
    else {
        startTimerFromTime(workTime);
    }
}

void PomodoroTimer::onTimerEnd() {
    if (isWorking) {
        pomodoroComplete++;
        isWorking = false;
        if (!isLastPomodoro()) {
            emit pomodoroSingleFinished(continueAutomatically, false);
            if (continueAutomatically) {
                startTimerFromTime(breakTime);
            }
        }
        else {
            emit pomodorosFinished();
        }
    }
    else {
        isWorking = true;
        emit breakFinished(continueAutomatically, false);
        if (continueAutomatically) {
            startTimerFromTime(workTime);
        }
    }
}

void PomodoroTimer::onTimerSkipped() {
    if (isWorking) {
        pomodoroComplete++;
        isWorking = false;
        if (!isLastPomodoro()) {
            emit pomodoroSingleFinished(continueAutomatically, true);
            startTimerFromTime(breakTime);
        }
        else {
            emit pomodorosFinished();
        }
    }
    else {
        isWorking = true;
        emit breakFinished(continueAutomatically, true);
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
    emit timerStarted(timeToStart);
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

void PomodoroTimer::setContinueAutomatically(bool state) {
    continueAutomatically = state;
}

int PomodoroTimer::getPomodorosLeft() {
    return pomodoroMax - pomodoroComplete;
}

bool PomodoroTimer::isRunning() {
    return timer->isTimerRunning();
}
