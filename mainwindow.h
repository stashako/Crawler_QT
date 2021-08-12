#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTextEdit>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include <QVBoxLayout>
#include <QAction>
#include <QMediaRecorder>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    void createDockWindows();
    void CameraSetup();
    QWidget *CamWidget;
    QDockWidget *dock1;
    QListWidget *List;
    QCamera *Camera;
    QCameraViewfinder *CameraViewfinder;
    QCameraImageCapture *CameraImageCapture;
    QVBoxLayout *VBoxlayout;
    QMediaRecorder *recorder;

public slots:
    void List_keys(QListWidgetItem* item);


};
#endif // MAINWINDOW_H
