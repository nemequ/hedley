#include "../hedley.h"

/* !!! WORK IN PROGRESS !!!
 *
 * This is a macro I'd like to merge into Hedley at some point, but it
 * needs a lot more work and testing first.
 *
 * Notes:
 *
 * For C++2a, it may be possible to use std::assume_aligned.
 *
 * I really don't like the idea of actually generating code from the
 * header instead of just creating macros, but I can't think of
 * another way to get MSVC to work and unfortunately I think MSVC
 * support is pretty much required for this macro.  I'm particulary
 * worried about the implications of someone doing something like:
 *
 * namespace Foo {
 * #include <hedley.h>
 * }
 *
 * It might be a handy to have a macro like
 *
 * #if defined(__cplusplus)
 * #  define HEDLEY_CSTD(sym) std::sym
 * #else
 * #  define HEDLEY_CSTD(sym) sym
 * #endif
 *
 * To make it easy to do stuff like
 * HEDLEY_REINTERPRET_CAST(HEDLEY_CSTD(uintptr_t), expr), which could
 * compile to ((uintptr_t) (expr)) or
 * reinterpret_cast<std::uintptr_t>(expr).
 *
 * I'm guessing there is a lot of overlap between support for
 * statement expressions and __UINTPTR_TYPE__, which should let us
 * avoid including stdint.h.  If only MSVC supported
 * __UINTPTR_TYPE__... */
#if defined(HEDLEY_ASSUME_ALIGNED)
#  undef HEDLEY_ASSUME_ALIGNED
#endif
#if HEDLEY_HAS_BUILTIN(__builtin_assume_aligned) || HEDLEY_GCC_VERSION_CHECK(4,7,0) || HEDLEY_INTEL_VERSION_CHECK(16,0,0)
#  define HEDLEY_ASSUME_ALIGNED(ptr, align) ((__typeof__(ptr)) __builtin_assume_aligned(ptr, align))
#elif HEDLEY_INTEL_VERSION_CHECK(13,0,0)
#  define HEDLEY_ASSUME_ALIGNED(ptr, align) (__extension__ ({ __typeof__(ptr) ptr_ = (ptr); __assume_aligned(ptr_, align); ptr_; }))
#elif HEDLEY_MSVC_VERSION_CHECK(16,0,0) /* TODO: could be 13.10 if not for uintptr_t */
#  if defined(__cplusplus)
#    include <cstdint>
#    if __cplusplus >= 201402L
#      define HEDLEY_ASSUME_ALIGNED(ptr, align) (([](auto ptr_, auto align_){ __assume((reinterpret_cast<std::uintptr_t>(ptr_) & ((1 << align_) - 1)) == 0); return ptr_; })(ptr, align))
#    else
#      include <cstdint>
       template <int align_, typename T> HEDLEY_ALWAYS_INLINE HEDLEY_CONSTEXPR T* HEDLEY_CONCAT(HEDLEY_ASSUME_ALIGNED_impl_, HEDLEY_VERSION)(T* ptr_) { __assume((reinterpret_cast<uintptr_t>(ptr_) & ((1 << align_) - 1)) == 0); return ptr_; }
#      define HEDLEY_ASSUME_ALIGNED(ptr, align) (HEDLEY_CONCAT(HEDLEY_ASSUME_ALIGNED_impl_, HEDLEY_VERSION)<align>(ptr))
#    endif
#  else
#    include <stdint.h>
     static HEDLEY_ALWAYS_INLINE void* HEDLEY_CONCAT(HEDLEY_ASSUME_ALIGNED_impl_, HEDLEY_VERSION)(void* ptr_, int align_) { __assume((((uintptr_t) ptr_) & ((1 << align_) - 1)) == 0); return ptr_; }
#    define HEDLEY_ASSUME_ALIGNED(ptr, align) HEDLEY_CONCAT(HEDLEY_ASSUME_ALIGNED_impl_, HEDLEY_VERSION)(ptr, align)
#  endif
#elif defined(__UINTPTR_TYPE__) && 0 /* TODO: compiler supports statement expressions & __typeof__ */
#  define HEDLEY_ASSUME_ALIGNED(ptr, align) (__extension__ ({ __typeof__(ptr) ptr_ = (ptr); HEDLEY_ASSUME((HEDLEY_REINTERPRET_CAST(__UINTPTR_TYPE__, ptr_) & ((1 << align_) - 1)) == 0); ptr_; }))
#elif defined(__UINTPTR_TYPE__) && 0 /* TODO: C compiler supports statement expressions */
#  define HEDLEY_ASSUME_ALIGNED(ptr, align) (__extension__ ({ void* ptr_ = (ptr); HEDLEY_ASSUME((((__UINTPTR_TYPE__) ptr_) & ((1 << align_) - 1)) == 0); ptr_; }))
#endif
#if !defined(HEDLEY_ASSUME_ALIGNED)
#  define HEDLEY_ASSUME_ALIGNED(ptr, align) (ptr)
#endif

/* Test stolen from GCC */
void test (double *out1, double *out2, double *out3, double *in1, double *in2, int len);

void test (double *out1, double *out2, double *out3, double *in1, double *in2, int len) {
  int i;
  double * HEDLEY_RESTRICT o1 = HEDLEY_ASSUME_ALIGNED(out1, 16);
  double * HEDLEY_RESTRICT o2 = HEDLEY_ASSUME_ALIGNED(out2, 16);
  double * HEDLEY_RESTRICT o3 = HEDLEY_ASSUME_ALIGNED(out3, 16);
  double * HEDLEY_RESTRICT i1 = HEDLEY_ASSUME_ALIGNED( in1, 16);
  double * HEDLEY_RESTRICT i2 = HEDLEY_ASSUME_ALIGNED( in2, 16);
  for (i = 0; i < len; ++i)
    {
      o1[i] = i1[i] * i2[i];
      o2[i] = i1[i] + i2[i];
      o3[i] = i1[i] - i2[i];
    }
}

int main(void) {
  return 0;
}
