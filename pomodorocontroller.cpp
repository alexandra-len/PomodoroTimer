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
}

void PomodoroController::startSession() {
    currentSession = sessions.at(0);
}

void PomodoroController::pauseSession() {

}

void PomodoroController::stopAllSessions() {

}

void PomodoroController::nextSession() {

}

int PomodoroController::sessionsLeft() {
    return sessions.size();
}
