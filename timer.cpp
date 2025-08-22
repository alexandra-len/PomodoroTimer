#include "timer.h"

Timer::Timer(QObject *parent)
    : QObject(parent), remaining(0,0,0), isPaused(false), isRunning(false)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Timer::updateTime);
}

void Timer::start(const QTime &duration) {
    if (!isPaused) {
        remaining = duration;
    }
    timer->start(1000);
    isPaused = false;
    isRunning = true;
}

void Timer::pause() {
    timer->stop();
    isPaused = true;
    isRunning = false;
}

void Timer::stop() {
    timer->stop();
    isPaused = false;
    isRunning = false;
}

QTime Timer::remainingTime() const {
    return remaining;
}

bool Timer::isTimerRunning() const {
    return isRunning;
}

void Timer::updateTime() {
    remaining = remaining.addSecs(-1);
    emit tick(remaining);

    if (remaining <= QTime(0,0,0))
    {
        stop();
        emit finished();
    }
}
