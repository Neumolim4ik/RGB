#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <QByteArray>
#include <QVector>
#include <QString>

class DataProcessor {
public:
    DataProcessor();

    bool processBinaryData(const QByteArray &data);
    QByteArray getChannel1Data() const;
    QByteArray getChannel2Data() const;
    QByteArray getChannel3Data() const;

private:
    QByteArray channel1Data;
    QByteArray channel2Data;
    QByteArray channel3Data;

    bool findMagicNumbers(const QByteArray &data, int &pos1, int &pos2, int &pos3);
};

#endif
