#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <QString>

#include "anpstatisticalcalc.h"

using namespace std;

AnpStatisticalCalc::AnpStatisticalCalc() {

}

void AnpStatisticalCalc::sizeFilter(AnpPduSequence *pduSeq) {
    int *temp_sizes = new int[pduSeq->getMaxPduLen()]; // массив хранения всех длин пакетов
    for (int i = 0; i < pduSeq->getMaxPduLen(); i++) {
        temp_sizes[i] = 0;
    } // занулил
    int j_now = 0; // текущая позиция в массиве
    for (int i = 0; i < pduSeq->getSize(); i++) {
        AnpPdu pdu = pduSeq->getPdu(i);
        pcap_pkthdr phdr = pdu.getPcapHdr();
        int size = phdr.caplen, repeat = 0;
        for (int j = 0; j < pduSeq->getMaxPduLen(); j++) {
            if (size == temp_sizes[j]) repeat = 1; // если встретился уже такой размер
        }
        if (repeat == 0) { // если не встретился
            temp_sizes[j_now] = size; // запись
            j_now++; // ++ pos
        }
    }
    int sizes[j_now];
    for (int i = 0; i < j_now; i++) {
        sizes[i] = temp_sizes[i];
    }
    delete [] temp_sizes; // переписал в новый статик и удалил старый динамический

    //--------------------------------------------------------------------------------------
    // Сортировка пузырьком

    int temp;
    for (int i = 0; i < j_now; i++) {
        for (int j = 0; j < j_now - i; j++) {
            if (sizes[j] > sizes[j + 1]) {
                temp = sizes[j];
                sizes[j] = sizes[j + 1];
                sizes[j + 1] = temp;
            }
        }
    }


    //--------------------------------------------------------------------------------------
    //Переписывание пакетов

    for (int i = 0; i < j_now; i++) { //i = 1; // на i=1 12 пакетов размера 48
        vector <AnpPdu> filter_packets;
        for (int j = 0; j < pduSeq->getSize(); j++) {
            AnpPdu pdu = pduSeq->getPdu(j);
            pcap_pkthdr phdr = pdu.getPcapHdr();
            int size = phdr.caplen;
            if (size == sizes[i]) {
                filter_packets.push_back(pdu);
            }
        }
        cout << "\n** For packets of size " << sizes[i] << " bytes: " << endl;

        // ЗДЕСЬ ПРИМЕНЯТЬ АЛГОРИТМЫ К ВЕКТОРУ filter_packets

    }
}

void AnpStatisticalCalc::bitConstSearch(AnpPduSequence *pduSeq, int max_lenght) {
    int bit_packets[pduSeq->getSize()][max_lenght]; // массив байт [всего_пакетов][выставленное_ограничение] в битовом представлении
    for (int num = 0; num < pduSeq->getSize(); num++) {
        AnpPdu pdu = pduSeq->getPdu(num);
        uint8_t* pdu_data = pdu.getData();
        for (int i = 0; i < max_lenght; i++) {
            uint byte = pdu_data[i];
            char b[100];
            itoa(byte,b,2);
            int c; c = strtol(b, NULL, 10);
            bit_packets[num][i] = c;
        }
    }
    //Поиск
    cout << "\n* Bit constants:\n";
    int new_col = 0, bit_const_count = 0; QString bit_const;
    for (int i = 0; i < max_lenght; i++) {
        for (int num = 0; num < pduSeq->getSize()-1; num++) {
            if (new_col == 0) {
                bit_const = QString::number(bit_packets[num][i]);
                while (bit_const.size() < 8) bit_const = "0" + bit_const;
                new_col++;
            }
            QString temp = QString::number(bit_packets[num][i]);
            QString temp2 = QString::number(bit_packets[num+1][i]);
            while (temp.size() < 8) temp = "0" + temp;
            while (temp2.size() < 8) temp2 = "0" + temp2;
            for (int j = 0; j < 8; j++) {
                if (temp[j] != temp2[j]) {
                    bit_const[j] = '~';
                }
            }
        }
        new_col = 0;
        if (bit_const != "~~~~~~~~") {
            int true_byte = 0;
            for (int j = 0; j < 8; j++) {
                if (bit_const[j] == '~') {
                    true_byte = 1;
                }
            }
            if (true_byte == 1) {
                bit_const_count++;
                cout << "  " << bit_const_count << ": "<< "Position \t" << i << "\t | Data \t" <<
                        bit_const.toLocal8Bit().constData() << endl;
            }
            // ~ - меняющиеся биты
            // 0, 1 - константные
        }
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
            if (tables[i][j] >= pduSeq->getSize()/1.1 && tables[i][j] <= pduSeq->getSize()) { // s.getSize()/x регулирует значение порога принятия частоты за константу
                const_count++; cout << "  " << const_count << ": ";
                //double freq1 = tables[i][j]; double freq2 = pduSeq->getSize();
                cout << "Byte \t" << hex << i << "\t";
                cout << dec << " | Position \t" << j << endl; //" \t| frequency " << freq1/freq2 << endl; // печать предполагаемых констант
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
    cout << "\n* Counters:\n"; int count_count = 0;
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
            count_count++;
            cout << "  " << count_count << ": "<< "Position \t" << i << "\t | Step \t" << step << "\n";
        }
    }
}
