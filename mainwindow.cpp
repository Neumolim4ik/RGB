#include "mainwindow.h"
#include "data_processor.h"
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    QLabel *filePathLabel = new QLabel("Выберите файл:");
    QPushButton *browseButton = new QPushButton("Обзор");
    QPushButton *processButton = new QPushButton("Обработать");
    resultImageLabel = new QLabel;  // Инициализируем QLabel для отображения результата


    dataProcessor = new DataProcessor;

    // Устанавливаем слоты для кнопок
    connect(browseButton, &QPushButton::clicked, this, &MainWindow::onBrowseButtonClicked);
    connect(processButton, &QPushButton::clicked, this, &MainWindow::onProcessButtonClicked);

    // Создаем горизонтальный layout
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(filePathLabel);
    layout->addWidget(browseButton);
    layout->addWidget(processButton);

    // Создаем и настраиваем центральный виджет
    QWidget *centralWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout);
    mainLayout->addWidget(resultImageLabel);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    selectedFilePath = "";
}

MainWindow::~MainWindow() {
    delete dataProcessor;
}

void MainWindow::onBrowseButtonClicked() {

    selectedFilePath = QFileDialog::getOpenFileName(this, tr("Выберите файл"), QString(), tr("Бинарные файлы (*.bin)"));

    if (!selectedFilePath.isEmpty()) {

    }
}

void MainWindow::onProcessButtonClicked() {
    if (selectedFilePath.isEmpty()) {

        return;
    }


    QFile file(selectedFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QByteArray binaryData = file.readAll();
    file.close();


    if (dataProcessor->processBinaryData(binaryData)) {

        QByteArray channel1Data = dataProcessor->getChannel1Data();
        QByteArray channel2Data = dataProcessor->getChannel2Data();
        QByteArray channel3Data = dataProcessor->getChannel3Data();

        int width = 256;
        int height = 256;

        QImage resultImage(width, height, QImage::Format_RGB888);

        for (int y = 0; y < resultImage.height(); y++) {
            for (int x = 0; x < resultImage.width(); x++) {
                QRgb pixel = qRgb(channel1Data[x + y * resultImage.width()], channel2Data[x + y * resultImage.width()], channel3Data[x + y * resultImage.width()]);
                resultImage.setPixel(x, y, pixel);
            }
        }

        QPixmap pixmap = QPixmap::fromImage(resultImage);

        resultImageLabel->setPixmap(pixmap);
    } else {

    }
}
