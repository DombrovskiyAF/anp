#ifndef ANPPDU_H
#define ANPPDU_H

#include "anp.h"
#include "anpglobals.h"
#include "file_formats.h"

class AnpPdu
{
public:
    AnpPdu();
    AnpPdu(const AnpPdu &pdu);
    void operator=(const AnpPdu &pdu);
    ~AnpPdu();

    pcap_pkthdr getPcapHdr() const;
    uint8_t *getData() const;

    void setData(pcap_pkthdr pktHdr, uint8_t *pktData);
    int printData();

    int findIpv4();

protected:

    pcap_pkthdr m_pcapHdr;
    uint8_t    *m_data;
};

#endif // ANPPDU_H
