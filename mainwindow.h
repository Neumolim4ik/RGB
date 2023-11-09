#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "data_processor.h"

class QPushButton;
class QLabel;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onBrowseButtonClicked();
    void onProcessButtonClicked();

private:
    DataProcessor *dataProcessor;
    QString selectedFilePath;
    QPushButton *browseButton;
    QPushButton *processButton;
    QLabel *filePathLabel;
    QLabel *resultImageLabel;

    void displayProcessedData();
};

#endif
