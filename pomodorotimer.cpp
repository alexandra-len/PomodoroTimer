#include "pomodorotimer.h"

PomodoroTimer::PomodoroTimer(QObject *parent, QTime workMins, QTime breakMins, int pomodoros)
    : QObject(parent), pomodoroComplete(0)
{
    workTime = workMins;
    breakTime = breakMins;
    pomodoroMax = pomodoros;
    timer = new Timer(this);
    connect(timer, &Timer::finished, this, [this]() {onTimerEnd();});
}

void PomodoroTimer::start() {
    startTimerFromTime(workTime);
    isWorking = true;
    pomodoroComplete = 0;
};

void PomodoroTimer::stop() {
    timer->stop();
};

void PomodoroTimer::skip() {
    onTimerEnd();
};

void PomodoroTimer::pause() {
    timer->pause();
};

void PomodoroTimer::resume() {
    timer->resume();
}
void PomodoroTimer::onTimerEnd() {
    if (isWorking) {
        pomodoroComplete++;
        isWorking = false;
        if (!isLastPomodoro()) {
            startTimerFromTime(breakTime);
        }
        else {
            emit pomodoroFinished();
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
