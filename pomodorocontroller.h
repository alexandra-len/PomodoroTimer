#ifndef POMODOROCONTROLLER_H
#define POMODOROCONTROLLER_H

#include <QObject>
#include "pomodorosession.h"

class PomodoroController : public QObject
{
    Q_OBJECT
public:
    PomodoroController(QObject *parent = nullptr);

    void StartPomodoro(QTime, QTime, int);

private:
    std::vector<PomodoroSession> sessions;

signals:
    void tick(QTime);
    void sessionFinished();
    void allSessionsFinished();
};

#endif // POMODOROCONTROLLER_H
