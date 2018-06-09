/**
 * @author DAF
 */

#ifndef IP_H
#define IP_H

#include "anpglobals.h"

#pragma pack(push,1)
// IP header
struct iphdr
{
  uint8_t       ihl:4;
  uint8_t       version:4;
  uint8_t       tos;
  uint16_t      tot_len;
  uint16_t      id;
  uint16_t      frag_off;
  uint8_t       ttl;
  uint8_t       protocol;
  uint16_t      check;
  uint32_t      saddr;
  uint32_t      daddr;
  // The options start here
};
#pragma pack(pop)

// возвращает позицию IPv4-заголовка или -1 если не найден
int find_ipv4( const uint8_t* frame, int len );

#endif // IP_H
