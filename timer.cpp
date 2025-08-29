#include "timer.h"

Timer::Timer(QObject *parent)
    : QObject(parent), remaining(0,0,0), isPaused(false), isRunning(false)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Timer::updateTime);
    reachedZeroOnce = false;
}

void Timer::start(const QTime &duration) {
    if (!isPaused) {
        reachedZeroOnce = false;
        remaining = duration;
        emit tick(remaining);
    }
    resume();
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
    if (remaining == QTime(0,0,0))
    {
        if (!reachedZeroOnce) {
            remaining = remaining.addSecs(1);
            reachedZeroOnce = true;
        }
        else {
            stop();
            emit finished();
            return;
        }
    }
    remaining = remaining.addSecs(-1);
    emit tick(remaining);
}
void Timer::resume() {
    timer->start(1000);
    isPaused = false;
    isRunning = true;
}
