#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>
#include <QTime>

class Timer : public QObject
{
    Q_OBJECT
public:
    Timer(QObject *parent = nullptr);

    void start(const QTime &duration);
    void pause();
    void resume();
    void stop();

    QTime remainingTime() const;
    bool isTimerRunning() const;

signals:
    void tick(QTime remaining);
    void finished();

private slots:
    void updateTime();

private:
    QTimer *timer;
    QTime remaining;
    bool isPaused;
    bool isRunning;
    bool reachedZeroOnce;
};

#endif // TIMER_H
