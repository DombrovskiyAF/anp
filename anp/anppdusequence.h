#ifndef ANPPDUSEQUENCE_H
#define ANPPDUSEQUENCE_H

#include "anppdu.h"
#include "file_formats.h"

#include <vector>
#include <string>

class AnpPduSequence
{
public:
    AnpPduSequence();
    ~AnpPduSequence();
    void readPcapFile(std::string fileName, uint quantity = 0);

    int getSize();
    AnpPdu getPdu(uint32_t num);

    void printAttr();
    int printPduData(uint num);
    int findIp(uint num);
    int getMaxPduLen (){ return m_maxLen; }
    int getMinPduLen (){ return m_minLen; }

private:
    std::string m_fileName;
    pcap_file_header m_fHeader;
    int m_pduCol;

    std::vector <AnpPdu> m_packets;

    unsigned int m_minLen;
    unsigned int m_maxLen;
    unsigned int m_sredLen;

};

#endif // ANPPDUSEQUENCE_H
