#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qdatetime.h"
#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "timer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startBtn_clicked();
    void on_resetBtn_clicked();
    void on_pauseBtn_clicked();

private:
    Timer *timerController;
    QTimer *timer;
    QTime remainingTime;
    bool isPaused;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    Ui::MainWindow *ui;
    void set_UI_time(QString timeToSet);
    void set_pauseBtn_text(QString);
    void on_timer_stop();
};
#endif // MAINWINDOW_H
