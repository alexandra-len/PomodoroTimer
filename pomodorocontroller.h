#ifndef POMODOROCONTROLLER_H
#define POMODOROCONTROLLER_H

#include <QObject>
#include "pomodorosession.h"

class PomodoroController : public QObject
{
    Q_OBJECT
public:
    PomodoroController(QObject *parent = nullptr);

    void startPomodoro(QTime, QTime, int, bool);
    void startSession();
    void pauseSession();
    void stopAllSessions();
    void nextSession();
    int sessionsLeft();

private:
    QVector<PomodoroSession*> sessions;
    PomodoroSession* currentSession;
    bool continueAutomatically;

signals:
    void tick(QTime);
    void sessionFinished();
    void allSessionsFinished();
};

#endif // POMODOROCONTROLLER_H
