#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , isPaused(false)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
    remainingTime = ui->setTimer->time();

    set_UI_time(remainingTime.toString("mm:ss"));
    set_btn_text("Start Timer");

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
    remainingTime = remainingTime.addSecs(-1);

    set_UI_time(remainingTime.toString("mm:ss"));

    if (remainingTime <= QTime(0,0,0,0)) {
        timer->stop();
        set_btn_text("Start Timer");
        ui->setTimer->setEnabled(true);
        player->play();
        QApplication::beep();
    }
}

void MainWindow::on_startBtn_clicked()
{
    if (ui->setTimer->time() > QTime(0,0,0,0)) {
        if (!timer->isActive()) {
            if (!isPaused) {
                remainingTime = ui->setTimer->time();
            }
            ui->setTimer->setEnabled(false);
            timer->start(1000);
            set_btn_text("Pause Timer");
            isPaused = false;
        }
        else {
            timer->stop();
            isPaused = true;
            set_btn_text("Resume Timer");
        }
    }
}
void MainWindow::on_resetBtn_clicked() {
    if (timer->isActive()) {
        timer->stop();
    }
    ui->setTimer->setEnabled(true);
    remainingTime = ui->setTimer->time();
    set_UI_time(remainingTime.toString("mm:ss"));
    set_btn_text("Start Timer");
    isPaused = false;
}

void MainWindow::set_UI_time(QString timeToSet) {
    ui->timerTxt->setText(timeToSet);
}
void MainWindow::set_btn_text(QString text) {
    ui->startBtn->setText(text);
}

