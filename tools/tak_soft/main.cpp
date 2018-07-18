#include <iostream>
#include <fstream>

#include "anpstatisticalcalc.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Start!\n\n";

    if (argc < 2)
        return 0;

    AnpPduSequence s;
    // имя файла передавать 1ым элементом коммандной строки
    s.readPcapFile(argv[1]); // считать первые 1000 пакетов из файла

    s.printAttr(); cout << endl;

    int max_lenght = 0;

    // Установление ограничения для поиска констант и счетчиков
    max_lenght = 30;//s.findIp(1); // например, до 30 или до позиции IP
    cout << "Constraint position = " << max_lenght << endl;

    AnpStatisticalCalc sc;
    //sc.constSearch(&s, max_lenght);
    //sc.bitConstSearch(&s, max_lenght);
    //sc.countSearch(&s, max_lenght);
    sc.sizeFilter(&s);

    cout << "\nStop!" << endl;
    return 0;
}
