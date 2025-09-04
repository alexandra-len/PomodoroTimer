#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>
#include <QTime>

class Timer : public QObject
{
    Q_OBJECT
public:
    Timer(QObject *parent = nullptr, const QTime time = QTime(0,0,0));

    void start();
    void pause();

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
};

#endif // TIMER_H
