#include <iostream>
#include <fstream>

#include "anpstatisticalcalc.h"

using namespace std;

AnpStatisticalCalc::AnpStatisticalCalc() {

}

void AnpStatisticalCalc::bitShaping(AnpPduSequence *pduSeq, int max_lenght) {
    // формирование массива пакетов [всего_пакетов][выставленное_ограничение]
    int bit_packets[pduSeq->getSize()][max_lenght]; // массив байт в битовом представлении
    int dec_packets[pduSeq->getSize()][max_lenght]; // массив байт в десятичном предст. (для проверки. будет удален)
    for (int num = 0; num < pduSeq->getSize(); num++) {
        AnpPdu pdu = pduSeq->getPdu(num);
        uint8_t* pdu_data = pdu.getData();
        //pcap_pkthdr phdr = pdu.getPcapHdr();
        //for (int i = 0; i < phdr.caplen; i++) {
        for (int i = 0; i < max_lenght; i++) {
            uint byte = pdu_data[i];
            char b[100];
            itoa(byte,b,2);
            int c; c = strtol(b, NULL, 10);
            bit_packets[num][i] = c;
            dec_packets[num][i] = byte;
        }
    }
    //Вывод-проверка
    cout << "\n\t\t* PROBEROCHNIY VIVOD BIT *\n";
    for (int num = 0; num < 4; num++) {
        for (int i = 0; i < 4; i++) {
            cout << bit_packets[num][i] << " = " << dec_packets[num][i] << " \t";
        }
        cout << endl;
    }
}

void AnpStatisticalCalc::constSearch(AnpPduSequence *pduSeq, int max_lenght) {
    // Формирование массива встречаемости байт

    int tables[256][max_lenght];// = {0};
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < max_lenght; j++) {
            tables[i][j] = -1;
        }
    }

    // Работа с пакетом № num для поиска констант

    for (int num = 0; num < pduSeq->getSize(); num++) {
        AnpPdu pdu = pduSeq->getPdu(num);
        uint8_t* pdu_data = pdu.getData();
        //pcap_pkthdr phdr = pdu.getPcapHdr();
        //for (int i = 0; i < phdr.caplen; i++) { // i - порядковый номер текущего байта byte из пакета num
        for (int i = 0; i < max_lenght; i++) {
            uint byte = pdu_data[i];
            for (uint j = 0; j < 256; j++) { // сравнение с каждым из 256 возможных байт
                if (byte == j) {
                    tables[j][i]++; // ++ встречаемость байта j на позиции i
                }
            }
        }
    }
    // вычисление частоты
    ofstream cac("constants.csv"); // дополнительный вывод для отслеживания
    cout << "\n* Constants:\n"; int const_count = 0;
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < max_lenght; j++) {
            cac << tables[i][j] << ";";
            if (tables[i][j] >= pduSeq->getSize()/4 && tables[i][j] <= pduSeq->getSize()) { // s.getSize()/4 регулирует значение порога принятия частоты за константу
                const_count++; cout << "  " << const_count << ": ";
                double freq1 = tables[i][j]; double freq2 = pduSeq->getSize();
                cout << "byte \t" << hex << i << "\t";
                cout << dec << " | position \t" << j << " \t| frequency " << freq1/freq2 << endl; // печать предполагаемых констант
            }
        }
        cac << "\n";
    }

}

void AnpStatisticalCalc::countSearch(AnpPduSequence *pduSeq, int max_lenght) {
    // Поиск счетчиков

    int counters[pduSeq->getSize()][max_lenght]; // формирование массива пакетов [всего_пакетов][выставленное_ограничение]
    for (int num = 0; num < pduSeq->getSize(); num++) {
        AnpPdu pdu = pduSeq->getPdu(num);
        uint8_t* pdu_data = pdu.getData();
        //pcap_pkthdr phdr = pdu.getPcapHdr();
        //for (int i = 0; i < phdr.caplen; i++) {
        for (int i = 0; i < max_lenght; i++) {
            uint byte = pdu_data[i];
            counters[num][i] = byte;
        }
    }
    // непосредственно поиск
    for (int i = 0; i < max_lenght; i++) { // идем по столбцам
        int no_count = 0, no_const = 0, step;
        for (int j = 0; j < pduSeq->getSize()-2; j++) {
            int difference1 = counters[j+1][i] - counters[j][i]; // разница между соседними значениями в столбце
            int difference2 = counters[j+2][i] - counters[j+1][i]; // следующая разница
            if (difference1 == difference2 || difference1 == 0 || difference2 == 0) { // если разницы одинаковые, либо увеличение счетчика не произошло
                if (difference1 > 0) {
                    no_const = 1; // если хоть раз было увеличение, то это не константа (чтобы не пересекаться с поиском констант)
                    step = difference1;
                }
            }
            else no_count = 1; // если разницы различны - в столбце нет счетчика

        }
        if (no_count == 0 && no_const == 1) { // если все условия выполнились - выводим позицию счетчика
            cout << "\n* Counter pos:\n  " << i << " (with step = " << step << ") \n";
        }
    }
}
