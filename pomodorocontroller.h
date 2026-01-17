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
    void resumeSession();
    void stopAllSessions();
    void onSessionEnd();
    int sessionsCompleted();
    QTime totalSessionTime();
    bool continuesAutomatically();

private:
    QObject* parent;
    QVector<PomodoroSession*> sessions;
    PomodoroSession* currentSession;
    bool continueAutomatically;
    int completedPomodoros;

    bool isInputValid(QTime workTime, QTime breakTime, int pomodoroNr);

signals:
    void pomodoroStarted();
    void tick(QTime);
    void sessionFinished();
    void allSessionsFinished();

};

#endif // POMODOROCONTROLLER_H
