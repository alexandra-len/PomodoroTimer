#include "pomodorosession.h"

PomodoroSession::PomodoroSession(QObject *parent, QTime duration)
    : QObject(parent)
{
    timer = new Timer(this, duration);

    connect(timer, &Timer::tick, this, [this](QTime t) {emit tick(t);});
    connect(timer, &Timer::finished, this, [this]() {emit sessionEnd();});
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
