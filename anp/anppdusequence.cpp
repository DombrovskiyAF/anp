#include <iostream>
#include <fstream>

#include <cstring>

#include "anppdusequence.h"
#include "anppdu.h"

using namespace std;

AnpPduSequence::AnpPduSequence():
m_fileName("")
{
    //m_pduCol= -1;
}

AnpPduSequence::~AnpPduSequence()
{

}

void AnpPduSequence::readPcapFile(string fileName, uint quantity)
{
    fstream f;
    f.open(fileName.c_str(), ios::in | ios::binary);
    if (!f)
    {
        cout << "File not open: " << fileName << endl;
        return;
    }

    m_fileName = fileName;

    f.read((char*)&m_fHeader, sizeof(m_fHeader));

    int pduCol = 0;
    m_minLen = 0xFFFF;
    m_maxLen = 0;
    m_sredLen = 0;
    cout << dec;

    uint cnt = 0;
    while (!f.eof())
    {
        if (quantity > 0 && cnt >= quantity )
            break;
        cnt++;

        pcap_pkthdr pcapHdr;
        f.read((char*) &pcapHdr, sizeof(pcapHdr));
        if (f.gcount() != sizeof(pcapHdr))
        {
            break;
        }

        unsigned char *pduData = new unsigned char[pcapHdr.caplen];
        f.read((char*)pduData, pcapHdr.caplen);
        if (f.gcount() != pcapHdr.caplen)
        {
            break;
        }

        AnpPdu pdu;
        pdu.setData(pcapHdr, pduData);
        m_packets.push_back(pdu);

        pduCol++;
        if (pcapHdr.caplen > m_maxLen)
            m_maxLen = pcapHdr.caplen;
        if (pcapHdr.caplen < m_minLen)
            m_minLen = pcapHdr.caplen;
        m_sredLen += pcapHdr.caplen;
    }
    m_sredLen = m_sredLen / pduCol;
    f.close();
}

void AnpPduSequence::printAttr()
{
    cout << "Attributes for packet sequence from file "
         << m_fileName
         << ":" << endl << dec;

    cout << "Link type: "  << m_fHeader.linktype << endl;
    cout << "Col: "  << m_packets.size() << endl;
    cout << "min len: "  << m_minLen << endl;
    cout << "max len: "  << m_maxLen << endl;
    cout << "sred len: "  << m_sredLen << endl;
}

int AnpPduSequence::printPduData(uint num)
{
    if (num > (m_packets.size() - 1) )
    {
        cout << "Error: no packet" << endl;
        return -1;
    }
    m_packets[num].printData();
    return 0;
}

int AnpPduSequence::findIp(uint num)
{
    if (num > (m_packets.size() - 1) )
    {
        cout << "Error: no packet" << endl;
        return -1;
    }
    return m_packets[num].findIpv4();
}

int AnpPduSequence::getSize()
{
    return m_packets.size();
}

AnpPdu AnpPduSequence::getPdu(uint32_t num)
{
    return m_packets.at(num);
}
