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
    timer->start(workTime);
    isWorking = true;
    pomodoroComplete = 0;
};

void PomodoroTimer::stop() {
    timer->stop();
};

void PomodoroTimer::skip() {
    if (isWorking) {
        timer->stop();
        timer->start(breakTime);
        pomodoroComplete++; // add to pomodoro count when pomodoro session is done
        isWorking = false;
    } // ADD: check if this was the last pomodoro
    else {
        timer->stop();
        timer->start(workTime);
        isWorking = true;
    }
};

void PomodoroTimer::pause() {
    timer->pause();
};

void PomodoroTimer::resume() {
    timer->resume();
}
void PomodoroTimer::onTimerEnd() {
    if (!isLastPomodoro()) {

    }
}

bool PomodoroTimer::isLastPomodoro() {
    if (isWorking) {
        pomodoroComplete++;
    }

    if (pomodoroComplete < pomodoroMax - 1) {

    }
}
