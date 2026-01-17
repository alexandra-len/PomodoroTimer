#ifndef POMODOROSESSION_H
#define POMODOROSESSION_H

#include "timer.h"

enum class SessionType {
    Work,
    Break
};

class PomodoroSession : public QObject
{
    Q_OBJECT
public:
    PomodoroSession(QObject *parent = nullptr, QTime duration = QTime(0,0,0), SessionType type = SessionType::Work);
    void start();
    void stop();
    void pause();
    void resume();
    QTime totalTime() const;
    SessionType type() const;

private:
    Timer *timer;
    QTime duration;
    SessionType sessionType;

signals:
    void tick(QTime remaining);
    void sessionEnd();

};

#endif // POMODOROSESSION_H
