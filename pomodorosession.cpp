#include "pomodorosession.h"

PomodoroSession::PomodoroSession(QObject *parent, QTime duration)
    : QObject(parent)
{
    timer = new Timer(this, duration);
}
