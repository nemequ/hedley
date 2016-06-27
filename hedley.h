/* Hedley - https://github.com/nemequ/hedley
 * Copyright (c) 2016 Evan Nemerson <evan@nemerson.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#if !defined(HEDLEY_VERSION) || (HEDLEY_VERSION < 1)
#if defined(HEDLEY_VERSION)
#  undef HEDLEY_VERSION
#endif
#define HEDLEY_VERSION 1

/* HEDLEY_VERSION(major,minor,patch):
 *
 * This macro is used to encode semantic version information into a
 * single value which can easily be tested in other macros.  It
 * assumes each part of the version fits in 8-bits.
 */
#if defined(HEDLEY_ENCODE_VERSION)
#  undef HEDLEY_ENCODE_VERSION
#endif
#define HEDLEY_ENCODE_VERSION(major,minor,revision) ((major << 24) | (minor << 8) | (revision))

/* HEDLEY_GCC_VERSION_CHECK(major,minor,patch):
 *
 * Check whether your compiler is (pretending to be) a version of GCC
 * greater than or equal to the specified value.
 */
#if defined(HEDLEY_GCC_VERSION_CHECK)
#  undef HEDLEY_GCC_VERSION_CHECK
#endif
#if !defined(__GNUC__)
#  define HEDLEY_GCC_VERSION_CHECK(major,minor,patch) 0
#else
#  if defined(__GNUC_PATCHLEVEL__)
#    define HEDLEY_GCC_VERSION_CHECK(major,minor,patch) (HEDLEY_ENCODE_VERSION(major,minor,patch) >= HEDLEY_ENCODE_VERSION(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__))
#  else
#    define HEDLEY_GCC_VERSION_CHECK(major,minor,patch) (HEDLEY_ENCODE_VERSION(major,minor,patch) >= HEDLEY_ENCODE_VERSION(__GNUC__, __GNUC_MINOR__, 0))
#  endif
#endif

/* HEDLEY_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch):
 *
 * Like HEDLEY_GCC_VERSION_CHECK, but defined to 0 for clang.
 *
 * This is important because we might want to do something like
 * HEDLEY_HAS_ATTRIBUTE(foo) || HEDLEY_GCC_VERSION_CHECK(x,y,z), and
 * if the first part fails but the second part returns true it could
 * result in bad code.
 *
 * Instead, most checks in Hedley use something like
 * HEDLEY_HAS_ATTRIBUTE(foo) || HEDLEY_GCC_NOT_CLANG_VERSION_CHECK(x,y,z).
 */
#if defined(HEDLEY_GCC_NOT_CLANG_VERSION_CHECK)
#  undef HEDLEY_GCC_NOT_CLANG_VERSION_CHECK
#endif
#if defined(__clang__)
#  define HEDLEY_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch) 0
#else
#  define HEDLEY_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch) HEDLEY_GCC_VERSION_CHECK(major,minor,patch)
#endif

/* HEDLEY_MSVC_VERSION_CHECK(major,minor,patch):
 *
 * Check whether your compiler is a version of MSVC greater than or
 * equal to the specified value.
 */
#if defined(HEDLEY_MSVC_VERSION_CHECK)
#  undef HEDLEY_GCC_VERSION_CHECK
#endif
#if !defined(_MSC_VER)
#  define HEDLEY_MSVC_VERSION_CHECK(major,minor,patch) 0
#if _MSC_VER >= 1400
#  define HEDLEY_MSVC_VERSION_CHECK(major,minor,patch) (((major * 1000000) + (minor * 10000) + (patch)) >= _MSC_FULL_VER)
#elif _MSC_VER >= 1200
#  define HEDLEY_MSVC_VERSION_CHECK(major,minor,patch) (((major * 100000) + (minor * 1000) + (patch)) >= _MSC_FULL_VER)
#else
#  define HEDLEY_MSVC_VERSION_CHECK(major,minor,patch) (((major * 100) + (minor)) >= _MSC_VER)
#endif

/* HEDLEY_CLANG_HAS_ATTRIBUTE(attribute):
 * HEDLEY_CLANG_HAS_BUILTIN(builtin):
 * HEDLEY_CLANG_HAS_FEATURE(feature):
 * HEDLEY_CLANG_HAS_EXTENSION(extension):
 * HEDLEY_CLANG_HAS_DECLSPEC_ATTRIBUTE(attribute):
 *
 * Defined to the relevant __has_* macro if the compiler is clang, or
 * 0 for other compilers.  This should generally be used for feature
 * detection on clang instead of the version numbers, especially since
 * Apple ships a version of clang with higher version numbers...
 */
#if defined(HEDLEY_CLANG_HAS_ATTRIBUTE)
#  undef HEDLEY_CLANG_HAS_ATTRIBUTE
#endif
#if defined(HEDLEY_CLANG_HAS_BUILTIN)
#  undef HEDLEY_CLANG_HAS_BUILTIN
#endif
#if defined(HEDLEY_CLANG_HAS_FEATURE)
#  undef HEDLEY_CLANG_HAS_FEATURE
#endif
#if defined(HEDLEY_CLANG_HAS_EXTENSION)
#  undef HEDLEY_CLANG_HAS_EXTENSION
#endif
#if defined(HEDLEY_CLANG_HAS_DECLSPEC_ATTRIBUTE)
#  undef HEDLEY_CLANG_HAS_DECLSPEC_ATTRIBUTE
#endif
#if defined(__clang__) && defined(__has_attribute)
#  define HEDLEY_CLANG_HAS_ATTRIBUTE(attribute) __has_attribute(attribute)
#else
#  define HEDLEY_CLANG_HAS_ATTRIBUTE(attribute) 0
#endif
#if defined(__clang__) && defined(__has_builtin)
#  define HEDLEY_CLANG_HAS_BUILTIN(builtin) __has_builtin(builtin)
#else
#  define HEDLEY_CLANG_HAS_BUILTIN(builtin) 0
#endif
#if defined(__clang__) && defined(__has_feature)
#  define HEDLEY_CLANG_HAS_FEATURE(feature) __has_feature(feature)
#else
#  define HEDLEY_CLANG_HAS_FEATURE(feature) 0
#endif
#if defined(__clang__) && defined(__has_extension)
#  define HEDLEY_CLANG_HAS_EXTENSION(extension) __has_extension(extension)
#else
#  define HEDLEY_CLANG_HAS_EXTENSION(extension) 0
#endif
#if defined(__clang__) && defined(__has_declspec_attribute)
#  define HEDLEY_CLANG_HAS_DECLSPEC_ATTRIBUTE(attribute) __has_declspec_attribute(attribute)
#else
#  define HEDLEY_CLANG_HAS_DECLSPEC_ATTRIBUTE(attribute) 0
#endif

/* HEDLEY_GCC_HAS_ATTRIBUTE(attribute,major,minor,patch)
 * HEDLEY_GCC_HAS_BUILTIN(builtin,major,minor,patch)
 * HEDLEY_GCC_HAS_FEATURE(feature,major,minor,patch)
 * HEDLEY_GCC_HAS_DECLSPEC_ATTRIBUTE(attribute,major,minor,patch)
 *
 * These macros are just a shortcut for writing:
 *
 *   HEDLEY_CLANG_HAS_*(foo) || HEDLEY_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch)
 */
#if defined(HEDLEY_GCC_HAS_ATTRIBUTE)
#  undef HEDLEY_GCC_HAS_ATTRIBUTE
#endif
#if defined(HEDLEY_GCC_HAS_BUILTIN)
#  undef HEDLEY_GCC_HAS_BUILTIN
#endif
#if defined(HEDLEY_GCC_HAS_FEATURE)
#  undef HEDLEY_GCC_HAS_FEATURE
#endif
#if defined(HEDLEY_GCC_HAS_DECLSPEC_ATTRIBUTE)
#  undef HEDLEY_GCC_HAS_DECLSPEC_ATTRIBUTE
#endif
#define HEDLEY_GCC_HAS_ATTRIBUTE(attribute,major,minor,patch) (HEDLEY_CLANG_HAS_ATTRIBUTE(attribute) || HEDLEY_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch))
#define HEDLEY_GCC_HAS_BUILTIN(builtin,major,minor,patch) (HEDLEY_CLANG_HAS_BUILTIN(builtin) || HEDLEY_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch))
#define HEDLEY_GCC_HAS_FEATURE(feature,major,minor,patch) (HEDLEY_CLANG_HAS_FEATURE(feature) || HEDLEY_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch))
#define HEDLEY_GCC_HAS_DECLSPEC_ATTRIBUTE(attribute,major,minor,patch) (HEDLEY_CLANG_HAS_DECLSPEC_ATTRIBUTE(attribute) || HEDLEY_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch))

/* HEDLEY_DEPRECATED(since):
 * HEDLEY_DEPRECATED_FOR(since, replacement):
 *
 * These are used to mark functions as deprecated.
 */
#if defined(HEDLEY_DEPRECATED)
#  undef HEDLEY_DEPRECATED
#endif
#if defined(HEDLEY_DEPRECATED_FOR)
#  undef HEDLEY_DEPRECATED_FOR
#endif
#if HEDLEY_CLANG_HAS_EXTENSION(attribute_deprecated_with_message) || HEDLEY_GCC_NOT_CLANG_VERSION_CHECK(4,5,0)
#  define HEDLEY_DEPRECATED(since) __attribute__((__deprecated__("Since " #since)))
#  define HEDLEY_DEPRECATED_FOR(since, replacement) __attribute__((__deprecated__("Since " #since "; use " #replacement)))
#elif HEDLEY_GCC_HAS_ATTRIBUTE(deprcated,4,0,0)
#  define HEDLEY_DEPRECATED(since) __attribute__((__deprecated__))
#  define HEDLEY_DEPRECATED_FOR(since, replacement) __attribute__((__deprecated__))
#elif HEDLEY_MSVC_VERSION_CHECK(14,0,0)
#  define HEDLEY_DEPRECATED(since) __declspec(deprecated("Since " # since))
#  define HEDLEY_DEPRECATED(since, replacement) __declspec(deprecated("Since " #since "; use " #replacement))
#elif HEDLEY_MSVC_VERSION_CHECK(13,10,0) /* MSDN only goes back to VS 2003, so this may be pessimistic. */
#  define HEDLEY_DEPRECATED(since) _declspec(deprecated)
#  define HEDLEY_DEPRECATED_FOR(since, replacement) __declspec(deprecated)
#else
#  define HEDLEY_DEPRECATED(since)
#  define HEDLEY_DEPRECATED_FOR(since, replacement)
#endif

/* HEDLEY_UNAVAILABLE(target_version, available_since):
 *
 * Warn that the function is not available until available_since.
 */
#if defined(HEDLEY_UNAVAILABLE)
#  undef HEDLEY_UNAVAILABLE
#endif
#if HEDLEY_GCC_HAS_ATTRIBUTE(warning,4,3,0)
#  define HEDLEY_UNAVAILABLE(available_since) __attribute__((warning("Not available until " #available_since)))
#else
#  define HEDLEY_UNAVAILABLE(available_since)
#endif

HEDLEY_UNAVAILABLE(FOO_TARGET_VERSION, FOO_VERSION)

/* HEDLEY_WARN_UNUSED_RESULT:
 *
 * Function attribute which will cause supported compilers to warn if
 * the result of the function is not used.
 */
#if defined(HEDLEY_WARN_UNUSED_RESULT)
#  undef HEDLEY_WARN_UNUSED_RESULT
#endif
#if HEDLEY_GCC_HAS_ATTRIBUTE(warn_unused_result,3,4,0)
#  define HEDLEY_WARN_UNUSED_RESULT __attribute__((__warn_unused_result__))
#else
#  define HEDLEY_WARN_UNUSED_RESULT
#endif

/* HEDLEY_SENTINEL(position):
 *
 * Function attribute which annotates a function requires an explicit
 * NULL to denote the end of a variadic argument list.
 */
#if defined(HEDLEY_SENTINEL)
#  undef HEDLEY_SENTINEL
#endif
#if HEDLEY_GCC_HAS_ATTRIBUTE(sentinel,4,0,0)
#  define HEDLEY_SENTINEL(position) __attribute__((__sentinel__(position)))
#else
#  define HEDLEY_SENTINEL(position)
#endif

/* HEDLEY_NO_RETURN:
 *
 * Function attribute to indicate that the function will never return.
 */
#if defined(HEDLEY_NO_RETURN)
#  undef HEDLEY_NO_RETURN
#endif
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#  define HEDLEY_NO_RETURN _Noreturn
#elif HEDLEY_GCC_HAS_ATTRIBUTE(noreturn,3,2,0)
#  define HEDLEY_NO_RETURN __attribute__((__noreturn__))
#elif HEDLEY_MSVC_VERSION_CHECK(13,10,0)
#  define HEDLEY_NO_RETURN __declspec(noreturn)
#else
#  define HEDLEY_NO_RETURN
#endif

/* HEDLEY_UNREACHABLE():
 *
 * Tells supported compilers that the code should never be reached.
 */
#if defined(HEDLEY_UNREACHABLE)
#  undef HEDLEY_UNREACHABLE
#endif
#if HEDLEY_GCC_HAS_BUILTIN(unreachable,4,5,0)
#  define HEDLEY_UNREACHABLE() __builtin_unreachable()
#elif HEDLEY_MSVC_VERSION_CHECK(13,10,0)
#  define HEDLEY_UNREACHABLE() __assume(0)
#elif defined(assert)
#  define HEDLEY_UNREACHABLE() assert(0)
#else
#  define HEDLEY_UNREACHABLE()
#endif

/* HEDLEY_NON_NULL(param...):
 *
 * Function attribute which tells supported compilers that values
 * passed to the listed parameters (identified by position number)
 * should never be NULL.
 */
#if defined(HEDLEY_NON_NULL)
#  undef HEDLEY_NON_NULL
#endif
#if HEDLEY_GCC_HAS_ATTRIBUTE(nonnull,3,3,0)
#  define HEDLEY_NON_NULL(...) __attribute__((__nonnull__(__VA_ARGS__)))
#else
#  define HEDLEY_NON_NULL(...)
#endif

/* HEDLEY_MALLOC:
 *
 * Tells the compiler that the returned value cannot alias anything.
 */
#if defined(HEDLEY_MALLOC)
#  undef HEDLEY_MALLOC
#endif
#if HEDLEY_GCC_HAS_ATTRIBUTE(malloc,3,1,0)
#  define HEDLEY_MALLOC __attribute__((__malloc__))
#elif HEDLEY_MSVC_VERSION_CHECK(14,0,0)
#  DEFINE HEDLEY_MALLOC __declspec(noalias)
#else
#  define HEDLEY_MALLOC
#endif

/* HEDLEY_PRINTF_FORMAT(string_idx,first_to_check):
 *
 * Tells the compiler that the function takes a printf-style format
 * string so it can be checked at compile time.
 */
#if defined(HEDLEY_PRINTF_FORMAT)
#  undef HEDLEY_PRINTF_FORMAT
#endif
#if HEDLEY_GCC_HAS_ATTRIBUTE(format,3,1,0)
#  if HEDLEY_GCC_VERSION_CHECK(4,4,0) && defined(__MINGW32__) && !defined(__USE_MINGW_ANSI_STDIO)
#    define HEDLEY_PRINTF_FORMAT(string_idx,first_to_check) __attribute__((__format__(ms_printf, string, first_to_check)))
#  elif HEDLEY_GCC_VERSION_CHECK(4,4,0)
#    define HEDLEY_PRINTF_FORMAT(string_idx,first_to_check) __attribute__((__format__(gnu_printf, string, first_to_check)))
#  elif defined(__MINGW32__)
#    define HEDLEY_PRINTF_FORMAT(string_idx,first_to_check)
#  else
#    define HEDLEY_PRINTF_FORMAT(string_idx,first_to_check) __attribute__((__format__(printf, string, first_to_check)))
#  endif
#else
#  define HEDLEY_PRINTF_FORMAT(string_idx,first_to_check)
#endif

/* HEDLEY_LIKELY(expr):
 * HEDLEY_UNLIKELY(expr):
 *
 * Used to inform the compiler that the expression is likely (or
 * unlikely) to evaluate to true.
 *
 * Note that these macros will always return 0 (if the expression
 * evaluates to 0) or 1 (for everything else).
 */
#if defined(HEDLEY_LIKELY)
#  undef HEDLEY_LIKELY
#endif
#if defined(HEDLEY_UNLIKELY)
#  undef HEDLEY_UNLIKELY
#endif
#if HEDLEY_GCC_HAS_BUILTIN(expect,3,0,0)
#  define HEDLEY_LIKELY(expr) __builtin_expect(((expr) != 0), 1)
#  define HEDLEY_UNLIKELY(expr) __builtin_expect(((expr) == 0), 1)
#else
#  define HEDLEY_LIKELY(expr) ((expr) != 0)
#  define HEDLEY_UNLIKELY(expr) ((expr) == 0)
#endif

/* HEDLEY_INLINE:
 * HEDLEY_ALWAYS_INLINE:
 * HEDLEY_NEVER_INLINE:
 *
 * HEDLEY_INLINE asks the compiler to inline, but leaves the final
 * decision up to the compiler (like "inline" in the C99 standard).
 * HEDLEY_ALWAYS inline takes it a step further and tells the compiler
 * to *always* inline the function, and HEDLEY_NEVER_INLINE tells the
 * compiler *never* to inline the function.
 *
 * Note that not all of these are supported by every compiler.  Most
 * compilers, however, should behave.
 */
#if defined(HEDLEY_INLINE)
#  undef HEDLEY_INLINE
#endif
#if defined(HEDLEY_ALWAYS_INLINE)
#  undef HEDLEY_ALWAYS_INLINE
#endif
#if defined(HEDLEY_NEVER_INLINE)
#  undef HEDLEY_NEVER_INLINE
#endif
/* HEDLEY_INLINE */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#  define HEDLEY_INLINE inline
#elif defined(__GNUC_STDC_INLINE__)
#  define HEDLEY_INLINE __inline__
#elif defined(_MSC_VER)
#  define HEDLEY_INLINE __inline
#else
#  define HEDLEY_INLINE
#endif
/* HEDLEY_ALWAYS_INLINE */
#if HEDLEY_GCC_HAS_ATTRIBUTE(always_inline,4,0,0)
#  define HEDLEY_ALWAYS_INLINE __attribute__((__always_inline__))
#elif HEDLEY_MSVC_VERSION_CHECK(12,0,0)
#  define HEDLEY_ALWAYS_INLINE __forceinline
#else
#  define HEDLEY_ALWAYS_INLINE HEDLEY_INLINE
#endif
/* HEDLEY_NEVER_INLINE */
#if HEDLEY_GCC_HAS_ATTRIBUTE(never_inline,4,0,0)
#  define HEDLEY_NEVER_INLINE __attribute__((__noinline__))
#elif HEDLEY_MSVC_VERSION_CHECK(13,10,0)
#  define HEDLEY_NEVER_INLINE __declspec(noinline)
#else
#  define HEDLEY_NEVER_INLINE HEDLEY_INLINE
#endif

/* HEDLEY_INTERNAL:
 * HEDLEY_EXTERNAL:
 * HEDLEY_IMPORT:
 *
 * These can/should be used by libraries to specify which symbols are
 * publicly visible.  Note, however, that they shouldn't be used
 * directly, at least in public headers.
 */
#if defined(HEDLEY_INTERNAL)
#  undef HEDLEY_INTERNAL
#endif
#if defined(HEDLEY_EXTERNAL)
#  undef HEDLEY_EXTERNAL
#endif
#if defined(HEDLEY_IMPORT)
#  undef HEDLEY_IMPORT
#endif
#if defined(_WIN32) || defined(__CYGWIN__)
#  define HEDLEY_PRIVATE
#  define HEDLEY_PUBLIC   __declspec(dllexport)
#  define HEDLEY_IMPORT   __declspec(dllimport)
#else
#  if HEDLEY_GCC_VERSION_CHECK(4,2,0)
#    define HEDLEY_PRIVATE __attribute__ ((visibility ("hidden")))
#    define HEDLEY_PUBLIC  __attribute__ ((visibility ("default")))
#  else
#    define HEDLEY_PRIVATE
#    define HEDLEY_PUBLIC
#  endif
#  define HEDLEY_IMPORT    extern
#endif

/* HEDLEY_NO_THROW:
 *
 * Tell the compiler that this function will never throw a C++
 * exception.
 */
#if defined(HEDLEY_NO_THROW)
#  undef HEDLEY_NO_THROW
#endif
#if HEDLEY_CLANG_HAS_ATTRIBUTE(nothrow,3,3,0)
#  define HEDLEY_NO_THROW __attribute__((__nothrow__))
#elif HEDLEY_MSVC_VERSION_CHECK(13,1,0)
#  define HEDLEY_NO_THROW __declspec(nothrow)
#else
#  define HEDLEY_NO_THROW
#endif

/* HEDLEY_ARRAY_PARAM(param):
 *
 * Used for conformant array parameters (see
 * https://www.securecoding.cert.org/confluence/display/c/API05-C.+Use+conformant+array+parameters
 * for details).
 */
#if defined(HEDLEY_ARRAY_PARAM)
#  undef HEDLEY_ARRAY_PARAM
#endif
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) && !defined(__cplusplus)
#  define HEDLEY_ARRAY_PARAM(name) name
#else
#  define HEDLEY_ARRAY_PARAM(name)
#endif

#endif /* !defined(HEDLEY_VERSION) || (HEDLEY_VERSION < X) */
