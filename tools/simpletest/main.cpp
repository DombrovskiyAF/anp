#include <iostream>

#include "../../anp/anppdusequence.h"
#include "../../anp/anppdu.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Start!" << endl;
    AnpPduSequence s;

    if (argc < 2)
        return 0;

    s.readPcapFile(argv[1], 1000);
    s.printAttr();

    s.printPduData(5);
    int pos = s.findIp(5);

    cout << "Ipv4 pos= " << pos << endl;

    cout << "STOP." << endl;
    return 0;
}
