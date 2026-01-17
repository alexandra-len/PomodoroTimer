#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void on_doneBtn_clicked();

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
    QTime workTime;
    bool isInputValid();
    void setWindowAlwaysOnTop();
    void updateUi();
    void setTimerPage();
    void connectPomodoro();
    void setStartPage();
    void setAudio();
    void onSessionsFinished();
};
#endif // MAINWINDOW_H
