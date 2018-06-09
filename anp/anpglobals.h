/**
 * @file anpglobals.h
 * @brief Глобальные определения библиотеки aputils
 * Определения поддерживаемых ОС и компиляторов
 * Определения типов согласно <stdint.h> ISO C99 header
 */

#ifndef ANPGLOBALS_H
#define ANPGLOBALS_H

//
// Поддерживаемые операционные системы (AP_OS_x):
//
//   * WIN      - Windows (Windows 95/98/ME and Windows NT/2000/XP)
//   * LINUX    - Linux
//   * FREEBSD  - FreeBSD
//

#if defined(_WIN32)
#  define ANP_OS_WIN
#elif defined(_linux) || defined(__linux)
#  define ANP_OS_LINUX
#elif defined(__FreeBSD__) || defined(__DragonFly__)
#  define ANP_OS_FREEBSD
#else
#  error "Unsupported OS"
#endif

//
// Поддерживаемые компиляторы (AP_CC_x):
//
//   * GNU      - GNU C++
//   * BOR      - Borland C++
//   * MSVC     - Microsoft Visual C/C++
//   * INTEL    - Intel C++ for Linux, Intel C++ for Windows
//

#if defined(__GNUC__)
#  define ANP_CC_GNU
#elif defined(__BORLANDC__)
#  define ANP_CC_BOR
#elif defined(_MSC_VER)
#  define ANP_CC_MSVC
#elif defined(__INTEL_COMPILER)
#  define ANP_CC_INTEL
#else
#  error "Unsupported compiler"
#endif

#if defined(ANP_CC_MSVC)
  typedef char              int8_t;
  typedef unsigned char     uint8_t;
  typedef short             int16_t;
  typedef unsigned short    uint16_t;
  typedef int               int32_t;
  typedef unsigned int      uint32_t;
  typedef __int64           int64_t;
  typedef unsigned __int64  uint64_t;
#else
#  include <stdint.h> // ISO C99 header
#endif

typedef unsigned char       uchar;
typedef unsigned short      ushort;
typedef unsigned int        uint;
typedef unsigned long       ulong;

typedef unsigned long       size_type;

#endif // ANPGLOBALS_H

