#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <opencv2/opencv.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startCamera();

private:
    void detectAndDisplay(cv::Mat &frame);

    Ui::MainWindow *ui;
    cv::CascadeClassifier faceCascade; // Haar Cascade for face detection
    cv::VideoCapture cap;              // VideoCapture for accessing camera
    QLabel *videoLabel;                // QLabel to display video frames
    QPushButton *startButton;          // Button to start the camera
};

#endif // MAINWINDOW_H
