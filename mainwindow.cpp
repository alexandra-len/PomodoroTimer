#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pomodorotimer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , isPaused(false)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    pomodoroController = new PomodoroTimer(this);

    remainingTime = ui->setWork->time();

    connect(pomodoroController, &PomodoroTimer::pomodoroTick, this, [this](QTime t) {ui->timerTxt->setText(t.toString("mm:ss"));});
    connect(pomodoroController, &PomodoroTimer::pomodorosFinished, this, [this]() {on_timer_stop(); player->play();});
    connect(pomodoroController, &PomodoroTimer::pomodoroSingleFinished, this, [this]() { update_pomodoro_count();});
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
    if (ui->setWork->time() > QTime(0,0,0,0) && ui->setBreak->time() > QTime(0,0,0,0)) {
        ui->stackedWidget->setCurrentIndex(1);
        pomodoroController->setBreakTime(ui->setBreak->time());
        pomodoroController->setWorkTime(ui->setWork->time());
        pomodoroController->setPomodoroCount(ui->pomodoroNr->value());
        update_pomodoro_count();
        ui->timerTxt->setText(ui->setWork->time().toString("mm:ss"));
        pomodoroController->start();
        set_pauseBtn_text("Pause Timer");
    }
    else {
        ui->warningTxt->setText("WARNING: Input time must be more than 0.");
    }
}
void MainWindow::on_resetBtn_clicked() {
    pomodoroController->stop();
    on_timer_stop();
}

void MainWindow::on_pauseBtn_clicked() {
    pomodoroController->pause();
    if (pomodoroController->isRunning()) {
        set_pauseBtn_text("Pause Timer");
    }
    else {
        set_pauseBtn_text("Resume Timer");
    }
}

void MainWindow::on_skipBtn_clicked() {
    pomodoroController->skip();
}

void MainWindow::set_UI_time(QString timeToSet) {
    ui->timerTxt->setText(timeToSet);
}
void MainWindow::set_pauseBtn_text(QString text) {
    ui->pauseBtn->setText(text);
}

void MainWindow::update_pomodoro_count() {
    ui->pomodorosLeft->setText(QVariant(pomodoroController->getPomodorosLeft()).toString());
}

void MainWindow::on_timer_stop() {
    ui->pauseBtn->setText("Start Timer");
    set_UI_time(remainingTime.toString("mm:ss"));
    ui->stackedWidget->setCurrentIndex(0);
}

