#include "pomodorotimer.h"

PomodoroTimer::PomodoroTimer(QObject *parent, QTime workMins, QTime breakMins, int pomodoros)
    : QObject(parent)
{
    workTime = workMins;
    breakTime = breakMins;
    pomodoroNr = pomodoros;
    timer = new Timer(this);
}

void start() {

};

void stop() {

};

void skip() {

};

void pause() {

};
