#include <iostream>
#include "anppdusequence.h"
#include "anppdu.h"
#include <fstream>

using namespace std;

int main()
{
    cout << "Start!" << endl;     

    AnpPduSequence s;
    s.readPcapFile("mix.cap", 1000); // считать первые 1000 пакетов из файла
    //s.readPcapFile("mix.cap"); // считать все пакеты
    s.printAttr();
    cout << endl;

    // Получить количество считаных пакетов

    cout << "Packets col = " << s.getSize () << endl;
    cout << endl;

    // Получить длину самого большого пакета

    int max_lenght = 0;
    for (int num = 0; num < s.getSize(); num++) {
        AnpPdu pdu = s.getPdu (num);
        pcap_pkthdr phdr = pdu.getPcapHdr();
        if (phdr.caplen > max_lenght) max_lenght = phdr.caplen;
    }

    // Формирование массива встречаемости байт

    int tables[256][max_lenght];// = {0};
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < max_lenght; j++) {
            tables[i][j] = -1;
        }
    }

    // Работа с пакетом № num

    for (int num = 0; num < s.getSize(); num++) {
        AnpPdu pdu = s.getPdu (num);
        uint8_t* pdu_data = pdu.getData();
        pcap_pkthdr phdr = pdu.getPcapHdr();
        for (int i = 0; i < phdr.caplen; i++) { // i - порядковый номер текущего байта byte из пакета num
            uint byte = pdu_data[i];
            for (uint j = 0; j < 256; j++) { // сравнение с каждым из 256 возможных байт
                if (byte == j) {
                    tables[j][i]++; // ++ встречаемость байта j на позиции i
                }
            }
        }
    }

    // Вычисление частоты

    ofstream cac("const_and_count.csv"); // дополнительный вывод для отслеживания
    cout << "Constants:\n"; int const_count = 0;
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < max_lenght; j++) {
            cac << tables[i][j] << ";";
            if (tables[i][j] >= s.getSize()/4 && tables[i][j] <= s.getSize()) { // s.getSize()/4 регулирует значение порога принятия частоты за константу
                const_count++; cout << const_count << ": ";
                double freq1 = tables[i][j]; double freq2 = s.getSize();
                cout << "byte \t" << hex << i;
                cout << dec << " | position \t" << j << " \t| frequency " << freq1/freq2 << endl; // печать предполагаемых констант
            }
        }
        cac << "\n";
    }

    cout << "STOP." << endl;
    return 0;
}
