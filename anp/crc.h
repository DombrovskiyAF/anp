/**
 * @file crc.h
 * @brief Вычисление стандартных CRC
 */

#ifndef CRC_H
#define CRC_H

#include "anpglobals.h"

namespace anp
{
  /// @addtogroup CodesGroup
  ///@{

  /**
   * @brief CRC-8
   * Используется в ATM
   * @param buf [in] Указатель на данные
   * @param len [in] Размер данных
   * @param crc_in [in] Начальный остаток (опционально)
   * @return Контрольная сумма, вычисленная по CRC-8
   */
  uint8_t crc8( const uint8_t* buf, size_type len, uint8_t  crc_in = 0 );

  /**
   * @brief СRC-16-CCITT
   * @param buf [in] Указатель на данные
   * @param len [in] Размер данных
   * @param crc_in [in] Начальный остаток (опционально)
   * @return Контрольная сумма, вычисленная по CRC-16-CCITT
   */
  uint16_t crc16_ccitt( const uint8_t* buf, size_type len, uint16_t crc_in = ~0 );

  /**
   * @brief CRC-32-CCITT
   * @param buf [in] Указатель на данные
   * @param len [in] Размер данных
   * @param crc_in [in] Начальный остаток (опционально)
   * @return Контрольная сумма, вычисленная по CRC-32-CCITT
   */
  uint32_t crc32_ccitt( const uint8_t* buf, size_type len, uint32_t crc_in = ~0 );

  /**
   * @brief CRC-32-AAL5
   * @param buf [in] Указатель на данные
   * @param len [in] Размер данных
   * @param crc_in [in] Начальный остаток (опционально)
   * @return Контрольная сумма, используемая в AAL5
   */
  uint32_t crc32_aal5( const uint8_t* buf, size_type len, uint32_t crc_in = ~0 );

  /**
   * @brief CRC16
   * Используется некоторыми архиваторами
   * @param buf [in] Указатель на данные
   * @param len [in] Размер данных
   * @param crc_in [in] Начальный остаток (опционально)
   * @return Контрольная сумма, вычисленная по CRC-16
   */
  uint16_t crc16( const uint8_t* buf, size_type len, uint16_t crc_in = 0 );

  /**
   * @brief CRC-16-XMODEM
   * Используется в протоколе передачи файлов xmodem
   * @param buf [in] Указатель на данные
   * @param len [in] Размер данных
   * @param crc_in [in] Начальный остаток (опционально)
   * @return Контрольная сумма, вычисленная по CRC-16-XMODEM
   */
  uint16_t crc16_xmodem( const uint8_t* buf, size_type len, uint16_t crc_in = 0 );

  /**
   * @brief Internet checksum
   * @param buf [in] Указатель на данные
   * @param len [in] Размер данных
   * Используется в TCP/IP. см. RFC-1071
   * @return Контрольная сумма, вычисленная по RFC-1071
   */
  uint16_t inet_checksum( const uint8_t* buf, size_type len );

  /**
   * @brief Блочный код, используемый в ODLC
   * Порождающая матрица:
   *     1000 0000  0100 1110   80 4E
   *     0100 0000  0010 0111   40 27
   *     0010 0000  1000 1111   20 8F
   * G = 0001 0000  1101 1011 = 10 DB
   *     0000 1000  1111 0001   08 F1
   *     0000 0100  1110 0100   04 E4
   *     0000 0010  0111 0010   02 72
   *     0000 0001  0011 1001   01 39
   * @param value [in] Входной байт
   * @return Закодированное значение
   */
  uint16_t odlc_block_code( uint8_t value );

  ///@}

} // namespace anp

#endif // CRC_H
