#include "pomodorosession.h"

PomodoroSession::PomodoroSession(QObject *parent, QTime duration, SessionType type)
    : QObject(parent), duration(duration), sessionType(type)
{
    timer = new Timer(this, duration);

    connect(timer, &Timer::tick, this, [this](QTime t) {emit tick(t);});
    connect(timer, &Timer::finished, this, [this]() { timer->deleteLater(); emit sessionEnd();});
}

void PomodoroSession::start() {
    timer->start();
}

void PomodoroSession::stop() {
    timer->pause();
    emit sessionEnd();
}

void PomodoroSession::pause() {
    timer->pause();
}

void PomodoroSession::resume() {
    timer->start();
}

QTime PomodoroSession::totalTime() const {
    return duration;
}

SessionType PomodoroSession::type() const {
    return sessionType;
}
