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

    s.readPcapFile(argv[1]);
    s.printAttr();

    s.printPduData(0);
    int pos = s.findIp(0);

    s.printPduData(165);

    cout << "size= " << s.getSize() << endl;

    cout << "Ipv4 pos= " << pos << endl;

    cout << "STOP." << endl;
    return 0;
}
