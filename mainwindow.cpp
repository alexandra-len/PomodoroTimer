#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , isPaused(false)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    timerController = new Timer(this);
    remainingTime = ui->setWork->time();

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

void MainWindow::on_startBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    if (ui->setWork->time() > QTime(0,0,0,0)) {
        if (!timerController->isTimerRunning())
        {
            ui->timerTxt->setText(ui->setWork->time().toString("mm:ss"));
            timerController->start(ui->setWork->time());
            set_pauseBtn_text("Pause Timer");
        }
        else {
            timerController->pause();
            set_pauseBtn_text("Resume Timer");
        }
    }
}
void MainWindow::on_resetBtn_clicked() {
    if (timerController->isTimerRunning()) {
        timerController->stop();
    }
    on_timer_stop();
}

void MainWindow::on_pauseBtn_clicked() {
    if (!timerController->isTimerRunning())
    {
        timerController->start(ui->setWork->time());
        set_pauseBtn_text("Pause Timer");
    }
    else {
        timerController->pause();
        set_pauseBtn_text("Resume Timer");
    }
}

void MainWindow::set_UI_time(QString timeToSet) {
    ui->timerTxt->setText(timeToSet);
}
void MainWindow::set_pauseBtn_text(QString text) {
    ui->pauseBtn->setText(text);
}

void MainWindow::on_timer_stop() {
    ui->pauseBtn->setText("Start Timer");
    ui->setWork->setEnabled(true);
    set_UI_time(remainingTime.toString("mm:ss"));
    ui->stackedWidget->setCurrentIndex(0);
}

