#include "pomodorocontroller.h"
#include <QMessageBox>

PomodoroController::PomodoroController(QObject *parent)
    : QObject(parent), parent(parent), completedPomodoros(0)
{}

void PomodoroController::startPomodoro(QTime workTime, QTime breakTime, int pomodoroNr, bool continueAuto) {
    completedPomodoros = 0;
    if (!isInputValid(workTime, breakTime, pomodoroNr)) {
        QMessageBox msgBox(QMessageBox::Warning, "Invalid input", "You have entered an invalid time or pomodoro value.");
        msgBox.exec();
        return;
    }

    for (int i = 0; i < pomodoroNr - 1; i++) {
        sessions.push_back(new PomodoroSession(this, workTime, SessionType::Work));
        sessions.push_back(new PomodoroSession(this, breakTime, SessionType::Break));
    }
    sessions.push_back(new PomodoroSession(this, workTime, SessionType::Work));

    continueAutomatically = continueAuto;

    emit pomodoroStarted();

    startSession();
}

void PomodoroController::startSession() {
    if (sessions.isEmpty())
        return;

    currentSession = sessions.takeFirst();
    emit tick(currentSession->totalTime());

    connect(currentSession, &PomodoroSession::tick, this, [this](QTime t) {emit tick(t);});
    connect(currentSession, &PomodoroSession::sessionEnd, this, [this]() { onSessionEnd();});

    currentSession ->start();
}

void PomodoroController::pauseSession() {
    currentSession -> pause();
}

void PomodoroController::resumeSession() {
    currentSession -> resume();
}

void PomodoroController::stopAllSessions() {
    if (currentSession) {
        currentSession->stop();
        currentSession->deleteLater();
        currentSession = nullptr;
    }

    qDeleteAll(sessions);
    sessions.clear();

    emit allSessionsFinished();
}

void PomodoroController::onSessionEnd() {
    if (currentSession->type() == SessionType::Work)
        completedPomodoros++;

    currentSession->deleteLater();
    currentSession = nullptr;

    emit sessionFinished();

    if (sessions.empty()) {
        emit allSessionsFinished();
        return;
    }

    if (continueAutomatically) {
        startSession();
    }
}

int PomodoroController::sessionsCompleted() {
    return completedPomodoros;
}

bool PomodoroController::isInputValid(QTime workTime, QTime breakTime, int pomodoroNr) {
    return (workTime > QTime(0,0,0) && breakTime > QTime(0,0,0) && pomodoroNr > 0);
}

QTime PomodoroController::totalSessionTime() {
    return currentSession->totalTime();
}


bool PomodoroController::continuesAutomatically() {
    return continueAutomatically;
}
