#include "pomodorotimer.h"

PomodoroTimer::PomodoroTimer(QObject *parent, QTime workMins, QTime breakMins, int pomodoros)
    : QObject(parent)
{
    workTime = workMins;
    breakTime = breakMins;
    pomodoroNr = pomodoros;
}

void start() {

};

void stop() {

};

void skip() {

};
