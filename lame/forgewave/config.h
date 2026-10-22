/* config.h di ForgeWave per compilare libmp3lame (LAME 3.100, in ../lame, non modificato)
 * senza autotools, uguale su macOS, Linux e Windows. Il decoder (mpglib) resta escluso. */
#ifndef FORGEWAVE_LAME_CONFIG_H
#define FORGEWAVE_LAME_CONFIG_H

#define STDC_HEADERS 1
#define HAVE_ERRNO_H 1
#define HAVE_FCNTL_H 1
#define HAVE_LIMITS_H 1
#define HAVE_STDINT_H 1
#define HAVE_STRCHR 1
#define HAVE_MEMCPY 1
#define PACKAGE "lame"
#define PROTOTYPES 1
#define USE_FAST_LOG 1
#define LAME_LIBRARY_BUILD 1

/* Ottimizzazioni x86 come nella build ufficiale: SSE (sempre presente su x86_64) e il
 * trucco IEEE 754 di takehiro.c. */
#if defined(__x86_64__) || defined(_M_X64)
# define HAVE_XMMINTRIN_H 1
# define MIN_ARCH_SSE 1
# define TAKEHIRO_IEEE754_HACK 1
#endif

#include <stdint.h>
typedef float ieee754_float32_t;
typedef double ieee754_float64_t;
typedef long double ieee854_float80_t;

#ifdef _MSC_VER
# pragma warning(disable : 4305 4244 4267 4996)
#endif

#endif
