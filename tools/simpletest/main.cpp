#include <iostream>

#include "../../anp/anppdusequence.h"
#include "../../anp/anppdu.h"

using namespace std;

int main()
{
    cout << "Start!" << endl;
    AnpPduSequence s;
    s.readPcapFile("c:\\projects\\anp\\data\\mix.cap", 1000);
    s.printAttr();

    s.printPduData(5);
    int pos = s.findIp(5);

    cout << "Ipv4 pos= " << pos << endl;

    cout << "STOP." << endl;
    return 0;
}
