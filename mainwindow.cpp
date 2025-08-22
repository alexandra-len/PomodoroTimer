#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , isPaused(false)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timerController = new Timer(this);
    remainingTime = ui->setTimer->time();

    connect(timerController, &Timer::tick, this, [this](QTime t) {ui->timerTxt->setText(t.toString("mm:ss"));});

    connect(timerController, &Timer::finished, this, [this]() {on_timer_stop(); player->play();});

    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);

    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile("C:\\Users\\aaa\\Documents\\GitHub\\MatchaRun\\Assets\\Art\\SFX\\Bunny\\bunny_jump.wav"));
    audioOutput->setVolume(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime() {
//     remainingTime = remainingTime.addSecs(-1);

//     set_UI_time(remainingTime.toString("mm:ss"));

//     if (remainingTime <= QTime(0,0,0,0)) {
//         timer->stop();
//         set_btn_text("Start Timer");
//         ui->setTimer->setEnabled(true);
//         player->play();
//         QApplication::beep();
//     }
}

void MainWindow::on_startBtn_clicked()
{
    if (ui->setTimer->time() > QTime(0,0,0,0)) {
        if (!timerController->isTimerRunning())
        {
            timerController->start(ui->setTimer->time());
            set_btn_text("Pause Timer");
        }
        else {
            timerController->pause();
            set_btn_text("Resume Timer");
        }
        // if (!timer->isActive()) {
        //     if (!isPaused) {
        //         remainingTime = ui->setTimer->time();
        //     }
        //     ui->setTimer->setEnabled(false);
        //     timer->start(1000);
        //     set_btn_text("Pause Timer");
        //     isPaused = false;
        // }
        // else {
        //     timer->stop();
        //     isPaused = true;
        //     set_btn_text("Resume Timer");
        // }
    }
}
void MainWindow::on_resetBtn_clicked() {
    if (timerController->isTimerRunning()) {
        timerController->stop();
    }
    on_timer_stop();
    // if (timer->isActive()) {
    //     timer->stop();
    // }
    // ui->setTimer->setEnabled(true);
    // remainingTime = ui->setTimer->time();
    // set_UI_time(remainingTime.toString("mm:ss"));
    // set_btn_text("Start Timer");
    // isPaused = false;
}

void MainWindow::set_UI_time(QString timeToSet) {
    ui->timerTxt->setText(timeToSet);
}
void MainWindow::set_btn_text(QString text) {
    ui->startBtn->setText(text);
}

void MainWindow::on_timer_stop() {
    ui->startBtn->setText("Start Timer");
    ui->setTimer->setEnabled(true);
    set_UI_time(remainingTime.toString("mm:ss"));
}

