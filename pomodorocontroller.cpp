#include "pomodorocontroller.h"

PomodoroController::PomodoroController(QObject *parent)
    : QObject(parent)
{

}

void PomodoroController::StartPomodoro(QTime workTime, QTime breakTime, int pomodoroNr) {
    for (int i = 0; i < pomodoroNr - 1; i++) {
        sessions.push_back(PomodoroSession(this, workTime));
        sessions.push_back(PomodoroSession(this, breakTime));
    }
    sessions.push_back(PomodoroSession(this, workTime));
}
