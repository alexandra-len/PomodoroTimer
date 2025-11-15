#include "pomodorocontroller.h"

PomodoroController::PomodoroController(QObject *parent)
    : QObject(parent)
{
}

void PomodoroController::startPomodoro(QTime workTime, QTime breakTime, int pomodoroNr, bool continueAuto) {
    for (int i = 0; i < pomodoroNr - 1; i++) {
        sessions.push_back(new PomodoroSession(this, workTime));
        sessions.push_back(new PomodoroSession(this, breakTime));
    }
    sessions.push_back(new PomodoroSession(this, workTime));

    continueAutomatically = continueAuto;

    startSession();
}

void PomodoroController::startSession() {
    currentSession = sessions.at(0);

    connect(currentSession, &PomodoroSession::tick, this, [this](QTime t) {emit tick(t);});
    connect(currentSession, &PomodoroSession::sessionEnd, this, [this]() {onSessionEnd();});

    currentSession ->start();
}

void PomodoroController::pauseSession() {
    currentSession -> pause();
}

void PomodoroController::resumeSession() {
    currentSession -> resume();
}

void PomodoroController::stopAllSessions() {
    currentSession -> stop();
    emit allSessionsFinished();
}

void PomodoroController::nextSession() {
    if (sessions.size() > 0) {
        startSession();
    }
    else emit allSessionsFinished();
}

void PomodoroController::onSessionEnd() {
    sessions.pop_front();
    emit sessionFinished();

    if (continueAutomatically)
        nextSession();
}

int PomodoroController::sessionsLeft() {
    return sessions.size();
}


