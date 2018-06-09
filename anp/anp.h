#ifndef ANP_H
#define ANP_H

/// Информация из libpcap
#define TCPDUMP_MAGIC       0xa1b2c3d4
#define PCAP_VERSION_MAJOR  2
#define PCAP_VERSION_MINOR  4

/// linktype для заголовка файла в pcap формате
#define PCAP_LINKTYPE_UNKNOWN  0
#define PCAP_LINKTYPE_ETH      1
#define PCAP_LINKTYPE_PPP      9
#define PCAP_LINKTYPE_AAL5     100
#define PCAP_LINKTYPE_IP       101
#define PCAP_LINKTYPE_CHDLC    104
#define PCAP_LINKTYPE_FR       107
#define PCAP_LINKTYPE_ATM      123
#define PCAP_LINKTYPE_MTP2     140

#define MAX_PACKET_LEN      65535





#endif // ANP_H
