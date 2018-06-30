#include <iostream>
#include <fstream>

#include "anpstatisticalcalc.h"

using namespace std;

int main()
{
    cout << "Start!\n\n";

    AnpPduSequence s;
    s.readPcapFile("C:\\anp\\anp-master\\data\\temp.cap", 100); // считать первые 1000 пакетов из файла
    //s.readPcapFile("mix.cap"); // считать все пакеты
    s.printAttr(); cout << endl;

    int max_lenght = 0;/*
    // Получить длину самого большого пакета
    for (int num = 0; num < s.getSize(); num++) {
        AnpPdu pdu = s.getPdu (num);
        pcap_pkthdr phdr = pdu.getPcapHdr();
        if (phdr.caplen > max_lenght) max_lenght = phdr.caplen;
    }*/

    // Установление ограничения для поиска констант и счетчиков
    max_lenght = 15;//s.findIp(1); // например, до 15 или до позиции IP
    cout << "Constraint position = " << max_lenght << endl;

    AnpStatisticalCalc sc;    
    sc.constSearch(&s, max_lenght);
    sc.countSearch(&s, max_lenght);
    sc.bitShaping(&s, max_lenght);

    cout << "\nStop!" << endl;
    return 0;
}
