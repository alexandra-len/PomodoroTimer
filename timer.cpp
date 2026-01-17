#include "timer.h"

Timer::Timer(QObject *parent, const QTime time)
    : QObject(parent)
{
    timer = new QTimer(this);
    remaining = time;
    connect(timer, &QTimer::timeout, this, &Timer::updateTime);
}

void Timer::start() {
    timer->start(1000);
}

void Timer::updateTime() {
    if (remaining >= QTime(0,0,0)) {
        if (remaining == QTime(0,0,0)) {
            emit tick(remaining);
            emit finished();
        }
        else {
            remaining = remaining.addSecs(-1);
            emit tick(remaining);
        }
    }
}

void Timer::pause() {
    timer->stop();
}

QTime Timer::remainingTime() const {
    return remaining;
}

bool Timer::isTimerRunning() const {
    return timer->isActive();
}
