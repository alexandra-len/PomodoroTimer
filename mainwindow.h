#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pomodorotimer.h"
#include "qdatetime.h"
#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QScreen>
#include "timer.h"
#include "pomodorocontroller.h"

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
    void on_stopBtn_clicked();
    void on_pauseBtn_clicked();
    void on_skipBtn_clicked();
    void on_nextBtn_clicked();
    void on_resumeBtn_clicked();

private:
    Timer *timerController;
    QTimer *timer;
    // PomodoroTimer *pomodoroController;
    PomodoroController *pomodoroController;
    QTime remainingTime;
    bool isPaused;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    Ui::MainWindow *ui;
    QScreen *screen;
    Qt::WindowFlags flags;
    // void set_UI_time(QString timeToSet);
    // void set_pauseBtn_text(QString);
    // void on_timer_stop();
    // void update_ui(const QTime &t);
    // void on_timer_finish(bool, bool);
    // void set_on_top(bool);
    bool isInputValid();
    void setWindowAlwaysOnTop();
    void updateUi();
    void switchToTimerScreen();
};
#endif // MAINWINDOW_H
