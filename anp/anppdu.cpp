#include "anppdu.h"
#include "ip.h"

#include <iostream>
#include <cstring>

using namespace std;

AnpPdu::AnpPdu():
m_data(NULL)
{}

AnpPdu::AnpPdu(const AnpPdu &pdu )
{
    m_pcapHdr = pdu.getPcapHdr();
    m_data = new uint8_t[m_pcapHdr.caplen];
    memcpy(m_data, pdu.getData(), m_pcapHdr.caplen);
}

void AnpPdu::operator=(const AnpPdu &pdu)
{
    m_pcapHdr = pdu.getPcapHdr();
    m_data = new uint8_t[m_pcapHdr.caplen];
    memcpy(m_data, pdu.getData(), m_pcapHdr.caplen);
}


AnpPdu::~AnpPdu()
{
    if(m_data != NULL)
        delete [] m_data;
}

pcap_pkthdr AnpPdu::getPcapHdr() const
{
    return m_pcapHdr;
}

uint8_t *AnpPdu::getData() const
{
    return m_data;
}

int AnpPdu::printData()
{
    if(m_data == NULL) return -1;

    cout << "Captured lenght: " << m_pcapHdr.caplen << endl;
    cout << hex << uppercase;
    int colStr = m_pcapHdr.caplen / 16 + 1;
    uint curByte = 0;
    for(int i = 0; i < colStr; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            unsigned int uc = m_data[curByte];
            if(uc < 0x10)
                cout << "0";
            cout << uc << " ";
            curByte++;
            if (curByte == m_pcapHdr.caplen)
                break;
        }
        cout << endl;
    }

    cout << dec << endl;
    return 0;
}
int AnpPdu::findIpv4()
{
    return find_ipv4( m_data, m_pcapHdr.caplen );
}

void AnpPdu::setData(pcap_pkthdr pktHdr, uint8_t *pktData)
{
    m_pcapHdr = pktHdr;
    m_data = pktData;
}
