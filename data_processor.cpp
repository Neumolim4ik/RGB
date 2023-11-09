#include "data_processor.h"

DataProcessor::DataProcessor() {
    // Конструктор класса
}

bool DataProcessor::processBinaryData(const QByteArray &data) {
    int pos1, pos2, pos3;

    if (!findMagicNumbers(data, pos1, pos2, pos3)) {
        return false;  // Не найдены магические числа
    }

    // Извлекаем данные для каждого канала
    channel1Data = data.mid(pos1 + 8, pos2 - pos1 - 8);
    channel2Data = data.mid(pos2 + 8, pos3 - pos2 - 8);
    channel3Data = data.mid(pos3 + 8);

    return true;
}

bool DataProcessor::findMagicNumbers(const QByteArray &data, int &pos1, int &pos2, int &pos3) {
    pos1 = data.indexOf(QByteArray::fromHex("DEADBABE"));
    if (pos1 == -1) {
        return false;
    }

    pos2 = data.indexOf(QByteArray::fromHex("BABADEDA"), pos1);
    if (pos2 == -1) {
        return false;
    }

    pos3 = data.indexOf(QByteArray::fromHex("DEADBEEF"), pos2);
    if (pos3 == -1) {
        return false;
    }

    return true;
}

QByteArray DataProcessor::getChannel1Data() const {
    return channel1Data;
}

QByteArray DataProcessor::getChannel2Data() const {
    return channel2Data;
}

QByteArray DataProcessor::getChannel3Data() const {
    return channel3Data;
}

