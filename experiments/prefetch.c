#include "../hedley.h"

#if defined(HEDLEYX_PREFETCH)
#  undef HEDLEYX_PREFETCH
#endif
#if \
  HEDLEY_HAS_BUILTIN(__builtin_prefetch) || \
  HEDLEY_GCC_VERSION_CHECK(3,4,0) || \
  HEDLEY_INTEL_VERSION_CHECK(13,0,0)
#  define HEDLEYX_PREFETCH(addr, rw, locality) __builtin_prefetch((addr), (rw), (locality))
#elif defined(__ARM_ACLE)
#  include <arm_acle.h>
#  if (__ARM_ACLE >= 101)
#    define HEDLEYX_PREFETCH(addr, rw, locality) __pldx(rw, 0U, HEDLEY_STATIC_CAST(unsigned int, ((locality) < 2)))
#  else
#    define HEDLEYX_PREFETCH(addr, rw, locality) __pld((((void) rw), ((void) locality), (addr)))
#  endif
#elif HEDLEY_PGI_VERSION_CHECK(10,0,0)
#  define HEDLEYX_PREFETCH(addr, rw, locality) \
    HEDLEY_DIAGNOSTIC_PUSH \
    _Pragma("diag_suppress 177,550") \
    (__extension__ ({ \
      (void) locality; \
      (void) rw; \
      const void* hedley_addr_ = (addr); \
      _Pragma(HEDLEY_STRINGIFY(mem prefetch hedley_addr_)) \
    })) \
    HEDLEY_DIAGNOSTIC_POP
#elif HEDLEY_CRAY_VERSION_CHECK(8,1,0)
#  define HEDLEYX_PREFETCH(addr, rw, locality) (__extension__ ({ \
      const void* hedley_addr_ = (addr); \
      if (rw) { \
        if (locality < 2) { \
          _Pragma(HEDLEY_STRINGIFY(_CRI prefetch (write, nt) hedley_addr_)) \
        } else { \
          _Pragma(HEDLEY_STRINGIFY(_CRI prefetch (write) hedley_addr_)) \
        } \
      } else { \
        if (locality < 2) { \
          _Pragma(HEDLEY_STRINGIFY(_CRI prefetch (nt) hedley_addr_)) \
        } else { \
          _Pragma(HEDLEY_STRINGIFY(_CRI prefetch hedley_addr_)) \
        } \
      } \
    }))
#elif HEDLEY_SUNPRO_VERSION_CHECK(5,10,0)
#  include <sun_prefetch.h>
#  define HEDLEYX_PREFETCH(addr, rw, locality) ((rw) ? ((locality < 2) ? (sun_prefetch_write_once(addr)) : (sun_prefetch_write_many(addr))) : ((locality < 2) ? (sun_prefetch_read_once(addr)) : (sun_prefetch_read_many(addr))))
#elif HEDLEY_IBM_VERSION_CHECK(11,0,0)
#  define HEDLEYX_PREFETCH(addr, rw, locality) __prefetch_by_load((((void) rw), ((void) locality), (addr)))
#elif defined(__SSE__)
#  include <xmmintrin.h>
#  define HEDLEYX_PREFETCH(addr, rw, locality) (((void) (rw)), _mm_prefetch(HEDLEY_REINTERPRET_CAST(char const*, (addr)), (locality)))
#elif defined(_M_IX86_FP) /* Microsoft doesn't define __SSE__. */
#  if (_M_IX86_FP >= 1)
#    include <xmmintrin.h>
#    define HEDLEYX_PREFETCH(addr, rw, locality) (((void) (rw)), _mm_prefetch(HEDLEY_REINTERPRET_CAST(char const*, (addr)), (locality)))
#  endif
#elif defined(_M_ARM64)
#  define HEDLEYX_PREFETCH(addr, rw, locality) (((void) (locality)), ((void) (rw)), __prefetch2((addr), ((locality) > 1)))
#elif defined(_M_ARM)
#  define HEDLEYX_PREFETCH(addr, rw, locality) (((void) (locality)), ((void) (rw)), __prefetch((addr)))
#endif
#if !defined(HEDLEYX_PREFETCH)
#  define HEDLEYX_PREFETCH(addr, rw, locality) (((void) (locality)), ((void) (rw)), ((void) (addr)))
#endif




static int x[4096] = { 0 };

int main(void) {
  HEDLEYX_PREFETCH(x, 0, 0);

  return x[0];
}