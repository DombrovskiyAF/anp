/**
 * @file file_formats.h
 * @brief Описание форматов файлов
 */

#ifndef FILE_FORMATS_H
#define FILE_FORMATS_H

#include "anpglobals.h"

/**
 * @file formats.h
 * @brief Структура заголовков pcap и sig форматов.
 */

#pragma pack(push, 1)

/// @brief штамп времени, отсутствующий в Windows
struct anp_timeval
{
  uint32_t tv_sec;      ///< seconds
  uint32_t tv_usec;     ///< microseconds
};

/// @brief заголовок pcap файла
struct pcap_file_header
{
  uint32_t magic;
  uint16_t version_major;
  uint16_t version_minor;
  int32_t  thiszone;      ///< gmt to local correction
  uint32_t sigfigs;       ///< accuracy of timestamps
  uint32_t snaplen;       ///< max length saved portion of each pkt
  uint32_t linktype;      ///< data link type (PCAP_LINKTYPE_*)
};

/// @brief заголовок кадра pcap
struct pcap_pkthdr
{
  anp_timeval ts;     ///< time stamp
  uint32_t  caplen;   ///< length of portion present
  uint32_t  len;      ///< length this packet (off wire)
};

/// @brief sig формат
struct sig_pkthdr
{
  uint16_t len;     ///< длина пакета
};

/// @brief sig4 формат
struct sig4_pkthdr
{
  uint32_t len;     ///< длина пакета
};

/// @brief erf формат
struct erf_pkthdr
{
  uint64_t ts;      ///< метка времени
  uint8_t  type;
  uint8_t  flags;
  uint16_t rlen;
  uint16_t lctr;
  uint16_t wlen;
};

struct pcap_packet_t
{
    pcap_pkthdr header;
    unsigned char data[];
};

#pragma pack(pop)


#endif // _FILE_FORMATS_H_
