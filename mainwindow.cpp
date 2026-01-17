#include "mainwindow.h"
#include "ui_mainwindow.h"
// #include "pomodorotimer.h"
#include "pomodorocontroller.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    // , isPaused(false)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setStartPage();
    setAudio();

    pomodoroController = new PomodoroController(this);

    connectPomodoro();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startBtn_clicked() {
    workTime = ui->workTimeInput->time();
    pomodoroController -> startPomodoro(workTime, ui->breakTimeInput->time(), ui->pomodoroNr->value(), ui->continueCheckBox->isChecked());
}

void MainWindow::on_stopBtn_clicked() {
    pomodoroController -> stopAllSessions();
}

void MainWindow::on_pauseBtn_clicked() {
    pomodoroController -> pauseSession();
    ui->pauseBtn->hide();
    ui->resumeBtn->show();
}

void MainWindow::on_resumeBtn_clicked() {
    pomodoroController -> resumeSession();
    ui->pauseBtn->show();
    ui->resumeBtn->hide();
}

void MainWindow::on_skipBtn_clicked() {
    pomodoroController -> onSessionEnd();
}

void MainWindow::on_nextBtn_clicked() {
    ui->nextBtn->hide();
    ui->pauseBtn->show();
    pomodoroController -> startSession();
    ui->timerTxt->setText(pomodoroController->totalSessionTime().toString("mm:ss"));
}

void MainWindow::on_doneBtn_clicked() {
    setStartPage();
}

void MainWindow::onSessionsFinished() {
    ui->nextBtn->hide();
    ui->pauseBtn->hide();
    ui->stopBtn->hide();
    ui->skipBtn->hide();
    ui->resumeBtn->hide();

    ui->doneBtn->show();
    player->setSource(QUrl("qrc:/assets/3_notes.wav"));
    player->play();
}

void MainWindow::setStartPage() {
    ui->stackedWidget->setCurrentIndex(0);
    this->setWindowFlag(Qt::WindowStaysOnTopHint, false);
    this->show();
}

void MainWindow::setTimerPage() {
    ui->stackedWidget->setCurrentIndex(1);
    ui->resumeBtn->hide();
    ui->nextBtn->hide();
    ui->doneBtn->hide();

    ui->pauseBtn->show();
    ui->stopBtn->show();
    ui->skipBtn->show();

    ui->timerTxt->setText(workTime.toString("mm:ss"));
    QString pomodoroText = QString("%1/%2 pomodoros completed.").arg(pomodoroController->sessionsCompleted()).arg(ui->pomodoroNr->value());
    ui->pomodorosLeft->setText(pomodoroText);

    setWindowAlwaysOnTop();
}

void MainWindow::setAudio() {
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);

    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/assets/1_note.wav"));
    audioOutput->setVolume(1);
}

void MainWindow::connectPomodoro() {
    connect(pomodoroController, &PomodoroController::pomodoroStarted, this, [this]() {setTimerPage();});
    connect(pomodoroController, &PomodoroController::tick, this, [this](QTime t) {ui->timerTxt->setText(t.toString("mm:ss"));});
    connect(pomodoroController, &PomodoroController::sessionFinished, this, [this]() {updateUi(); player->play();});
    connect(pomodoroController, &PomodoroController::allSessionsFinished, this, [this]() {onSessionsFinished();});
}

void MainWindow::updateUi() {
    QString pomodoroText = QString("%1/%2 pomodoros completed.").arg(pomodoroController->sessionsCompleted()).arg(ui->pomodoroNr->value());
    ui->pomodorosLeft->setText(pomodoroText);

    if (!pomodoroController->continuesAutomatically()) {
        ui->pauseBtn->hide();
        ui->nextBtn->show();
    }
}

void MainWindow::setWindowAlwaysOnTop() {
    this->raise();
    this->activateWindow();

    this->setWindowFlag(Qt::WindowStaysOnTopHint, ui->keepOnTopCheckBox->isChecked());
    this->show();
}
