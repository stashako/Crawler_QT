#include <QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
        setWindowTitle(tr("Crawler Control Box"));
        createDockWindows();
        CameraSetup();
        connect(List, SIGNAL(itemPressed(QListWidgetItem*)),this, SLOT(List_keys(QListWidgetItem*)));

}


MainWindow::~MainWindow()
{
}


void MainWindow::createDockWindows()
{
    dock1 = new QDockWidget(this);
    dock1->setAllowedAreas(Qt::AllDockWidgetAreas);
    List = new QListWidget(dock1);
    List->addItem("Start Camera");
    List->addItem("Stop Camera");
    List->addItem("Start Recording");
    List->addItem("Stop Recording");
    List->addItem("Moving forward");
    List->addItem("Moving backward");

    dock1->setWidget(List);
    addDockWidget(Qt::LeftDockWidgetArea, dock1);

}

void MainWindow::CameraSetup()
{
    Camera = new QCamera;
    CameraViewfinder = new QCameraViewfinder(this);
    //CameraImageCapture = new QCameraImageCapture(Camera,this);
    VBoxlayout = new QVBoxLayout(this);
    Camera->setViewfinder(CameraViewfinder);
    CamWidget = new QWidget(this);
    setCentralWidget(CamWidget);
    VBoxlayout->addWidget(CameraViewfinder);
    CamWidget->setLayout(VBoxlayout);

    recorder = new QMediaRecorder(Camera,this);
    QVideoEncoderSettings settings = recorder->videoSettings();
    settings.setResolution(640,480);
    settings.setQuality(QMultimedia::VeryHighQuality);
    settings.setFrameRate(30.0);
    settings.setCodec("video/mp4");
    recorder->setVideoSettings(settings);
    recorder->setContainerFormat("mp4");

    Camera->setCaptureMode(QCamera::CaptureVideo);
    Camera->focus();



}

void MainWindow::List_keys(QListWidgetItem* item)
{
    if (List->item(0) == item) {
        qDebug() << "Start Camera";
        Camera->start();
    }
    if (List->item(1) == item) {
        qDebug() << "Stop Camera";
        Camera->stop();
    }
    if (List->item(2) == item) {
        qDebug() << "Start Recording";
        auto filename = QFileDialog::getSaveFileName(this, "Capture", "/", "video(*.mp4)");
        //QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"/home/jana/untitled.png",tr("Images (*.png *.xpm *.jpg)"));
        recorder->setOutputLocation(QUrl::fromLocalFile(filename));
        recorder->record();
    }
    if (List->item(3) == item) {
        qDebug() << "Stop Recording";
        recorder->stop();
    }
    if (List->item(4) == item) {
        qDebug() << "Moving forward";
    }
    if (List->item(5) == item) {
        qDebug() << "Moving backward";
    }
}
