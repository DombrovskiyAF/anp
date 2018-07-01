#include <iostream>
#include <fstream>

#include "searchengine.h"
#include "anppdusequence.h"
#include "anppdu.h"

using namespace std;

SearchEngine::SearchEngine() {

}

SearchEngine::~SearchEngine() {

}

void SearchEngine::constSearch(int max_lenght) {

    cout << "\n[PROVERKA] - m_packets.size(): " << m_packets.size() << " | getSize(): " << getSize() << endl; // ВЫВОДИТ НУЛИ!!! ???

    // Формирование массива встречаемости байт

        int tables[256][max_lenght];// = {0};
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < max_lenght; j++) {
                tables[i][j] = -1;
            }
        }

        // Работа с пакетом № num для поиска констант

        for (int num = 0; num < getSize(); num++) {
            AnpPdu pdu = getPdu (num);
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
        cout << "Constants:\n"; int const_count = 0;
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < max_lenght; j++) {
                cac << tables[i][j] << ";";
                if (tables[i][j] >= getSize()/4 && tables[i][j] <= getSize()) { // s.getSize()/4 регулирует значение порога принятия частоты за константу
                    const_count++; cout << const_count << ": ";
                    double freq1 = tables[i][j]; double freq2 = getSize();
                    cout << "byte \t" << hex << i;
                    cout << dec << " | position \t" << j << " \t| frequency " << freq1/freq2 << endl; // печать предполагаемых констант
                }
            }
            cac << "\n";
        }

}

void SearchEngine::countSearch(int max_lenght) {
    // Поиск счетчиков

        int counters[getSize()][max_lenght]; // формирование массива пакетов [всего_пакетов][выставленное_ограничение]
        for (int num = 0; num < getSize(); num++) {
            AnpPdu pdu = getPdu (num);
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
            int no_count = 0, no_const = 0;
            for (int j = 0; j < getSize()-2; j++) {
                int difference1 = counters[j+1][i] - counters[j][i]; // разница между соседними значениями в столбце
                int difference2 = counters[j+2][i] - counters[j+1][i]; // следующая разница
                if (difference1 == difference2 || difference1 == 0 || difference2 == 0) { // если разницы одинаковые, либо увеличение счетчика не произошло
                    if (difference1 > 0) no_const = 1; // если хоть раз было увеличение, то это не константа (чтобы не пересекаться с поиском констант)
                }
                else no_count = 1; // если разницы различны - в столбце нет счетчика
            }
            if (no_count == 0 && no_const == 1) { // если все условия выполнились - выводим позицию счетчика
                cout << "Counter pos: \n" << i;
            }
        }
}
