#include "ip.h"
#include "crc.h"

/**
  Поиск IPv4 в пакете.
  Ищет сигнатуру 0100xxxx в фрейме, затем считает контрольную сумму заголовка.
  //TODO: добавить проверку старшего бита в поле "флаги" (должен быть 0)
  Если она верная - возвращает позицию IP-заголовка, иначе -1
*/
int find_ipv4( const uint8_t* frame, int len )
{
  const int end = len - sizeof(iphdr);  // sizeof(iphdr) - мин. длина заголовка IP

  for( int pos = 0; pos != end; ++pos ) // тек. позиция
  {
    const iphdr* ip = (const iphdr*) (frame+pos);

    // нашли сигнатуру IPv4
    //TODO: проверить 0вой бит в флагах (ip->frag_off)
    if( ip->version == 4 )
    {
      // проверяем размер заголовка IP
      int size = ip->ihl * 4;
      if( pos + size > len ) continue;

      // проверяем сумму IP
      if( anp::inet_checksum( frame + pos, size ) == 0 )
        return pos;
    }
  }

  return -1;
}
