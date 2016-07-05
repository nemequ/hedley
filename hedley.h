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

#if defined(HEDLEY_ENCODE_VERSION)
#  undef HEDLEY_ENCODE_VERSION
#endif
#define HEDLEY_ENCODE_VERSION(major,minor,revision) (((major & 0xff) << 16) | ((minor & 0xff) << 8) | (revision & 0xff))

#if defined(HEDLEY_GCC_VERSION_CHECK)
#  undef HEDLEY_GCC_VERSION_CHECK
#endif
#if !defined(__GNUC__)
#  define HEDLEY_GCC_VERSION_CHECK(major,minor,patch) 0
#else
#  if defined(__GNUC_PATCHLEVEL__)
#    define HEDLEY_GCC_VERSION_CHECK(major,minor,patch) (HEDLEY_ENCODE_VERSION(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__) >= HEDLEY_ENCODE_VERSION(major,minor,patch))
#  else
#    define HEDLEY_GCC_VERSION_CHECK(major,minor,patch) (HEDLEY_ENCODE_VERSION(__GNUC__, __GNUC_MINOR__, 0) >= HEDLEY_ENCODE_VERSION(major,minor,patch))
#  endif
#endif

#if defined(HEDLEY_GCC_NOT_CLANG_VERSION_CHECK)
#  undef HEDLEY_GCC_NOT_CLANG_VERSION_CHECK
#endif
#if defined(__clang__)
#  define HEDLEY_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch) 0
#else
#  define HEDLEY_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch) HEDLEY_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(HEDLEY_MSVC_VERSION_CHECK)
#  undef HEDLEY_GCC_VERSION_CHECK
#endif
#if !defined(_MSC_VER)
#  define HEDLEY_MSVC_VERSION_CHECK(major,minor,patch) 0
#elif defined(_MSC_VER) && (_MSC_VER >= 1400)
#  define HEDLEY_MSVC_VERSION_CHECK(major,minor,patch) (_MSC_FULL_VER >= ((major * 1000000) + (minor * 10000) + (patch)))
#elif defined(_MSC_VER) && (_MSC_VER >= 1200)
#  define HEDLEY_MSVC_VERSION_CHECK(major,minor,patch) (_MSC_FULL_VER >= ((major * 100000) + (minor * 1000) + (patch)))
#else
#  define HEDLEY_MSVC_VERSION_CHECK(major,minor,patch) (_MSC_VER >= ((major * 100) + (minor)))
#endif

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

#if defined(HEDLEY_UNAVAILABLE)
#  undef HEDLEY_UNAVAILABLE
#endif
#if HEDLEY_GCC_HAS_ATTRIBUTE(warning,4,3,0)
#  define HEDLEY_UNAVAILABLE(available_since) __attribute__((warning("Not available until " #available_since)))
#else
#  define HEDLEY_UNAVAILABLE(available_since)
#endif

#if defined(HEDLEY_WARN_UNUSED_RESULT)
#  undef HEDLEY_WARN_UNUSED_RESULT
#endif
#if HEDLEY_GCC_HAS_ATTRIBUTE(warn_unused_result,3,4,0)
#  define HEDLEY_WARN_UNUSED_RESULT __attribute__((__warn_unused_result__))
#elif HEDLEY_MSVC_VERSION_CHECK(17,0,0)
#  define HEDLEY_WARN_UNUSED_RESULT _Check_return_
#else
#  define HEDLEY_WARN_UNUSED_RESULT
#endif

#if defined(HEDLEY_SENTINEL)
#  undef HEDLEY_SENTINEL
#endif
#if HEDLEY_GCC_HAS_ATTRIBUTE(sentinel,4,0,0)
#  define HEDLEY_SENTINEL(position) __attribute__((__sentinel__(position)))
#else
#  define HEDLEY_SENTINEL(position)
#endif

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

#if defined(HEDLEY_UNREACHABLE)
#  undef HEDLEY_UNREACHABLE
#endif
#if HEDLEY_GCC_HAS_BUILTIN(unreachable,4,5,0)
#  define HEDLEY_UNREACHABLE() __builtin_unreachable()
#elif HEDLEY_MSVC_VERSION_CHECK(13,10,0)
#  define HEDLEY_UNREACHABLE() __assume(0)
#elif defined(EXIT_FAILURE)
#  define HEDLEY_UNREACHABLE() abort()
#elif defined(assert)
#  define HEDLEY_UNREACHABLE() assert(0)
#else
#  define HEDLEY_UNREACHABLE()
#endif

#if defined(HEDLEY_NON_NULL)
#  undef HEDLEY_NON_NULL
#endif
#if HEDLEY_GCC_HAS_ATTRIBUTE(nonnull,3,3,0)
#  define HEDLEY_NON_NULL(...) __attribute__((__nonnull__(__VA_ARGS__)))
#else
#  define HEDLEY_NON_NULL(...)
#endif

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

#if defined(HEDLEY_LIKELY)
#  undef HEDLEY_LIKELY
#endif
#if defined(HEDLEY_UNLIKELY)
#  undef HEDLEY_UNLIKELY
#endif
#if HEDLEY_GCC_HAS_BUILTIN(expect,3,0,0)
#  define HEDLEY_LIKELY(expr) __builtin_expect(((expr) != 0), 1)
#  define HEDLEY_UNLIKELY(expr) __builtin_expect(((expr) != 0), 0)
#else
#  define HEDLEY_LIKELY(expr) ((expr) != 0)
#  define HEDLEY_UNLIKELY(expr) ((expr) != 0)
#endif

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
#elif HEDLEY_MSVC_VERSION_CHECK(12,0,0)
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

#if defined(HEDLEY_PRIVATE)
#  undef HEDLEY_PRIVATE
#endif
#if defined(HEDLEY_PUBLIC)
#  undef HEDLEY_PUBLIC
#endif
#if defined(HEDLEY_IMPORT)
#  undef HEDLEY_IMPORT
#endif
#if defined(_WIN32) || defined(__CYGWIN__)
#  if HEDLEY_GCC_VERSION_CHECK(4,2,0)
#    define HEDLEY_PRIVATE __attribute__((visibility ("hidden")))
#  else
#    define HEDLEY_PRIVATE
#  endif
#  define HEDLEY_PUBLIC   __declspec(dllexport)
#  define HEDLEY_IMPORT   __declspec(dllimport)
#else
#  if HEDLEY_GCC_VERSION_CHECK(4,2,0)
#    define HEDLEY_PRIVATE __attribute__((visibility ("hidden")))
#    define HEDLEY_PUBLIC  __attribute__((visibility ("default")))
#  else
#    define HEDLEY_PRIVATE
#    define HEDLEY_PUBLIC
#  endif
#  define HEDLEY_IMPORT    extern
#endif

#if defined(HEDLEY_NO_THROW)
#  undef HEDLEY_NO_THROW
#endif
#if HEDLEY_GCC_HAS_ATTRIBUTE(nothrow,3,3,0)
#  define HEDLEY_NO_THROW __attribute__((__nothrow__))
#elif HEDLEY_MSVC_VERSION_CHECK(13,1,0)
#  define HEDLEY_NO_THROW __declspec(nothrow)
#else
#  define HEDLEY_NO_THROW
#endif

#if defined(HEDLEY_ARRAY_PARAM)
#  undef HEDLEY_ARRAY_PARAM
#endif
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) && !defined(__cplusplus)
#  define HEDLEY_ARRAY_PARAM(name) name
#else
#  define HEDLEY_ARRAY_PARAM(name)
#endif

#if defined(HEDLEY_BEGIN_C_DECLS)
#  undef HEDLEY_BEGIN_C_DECLS
#endif
#if defined(HEDLEY_END_C_DECLS)
#  undef HEDLEY_END_C_DECLS
#endif
#if defined(HEDLEY_C_DECL)
#  undef HEDLEY_C_DECL
#endif
#if defined(__cplusplus)
#  define HEDLEY_BEGIN_C_DECLS extern "C" {
#  define HEDLEY_END_C_DECLS }
#  define HEDLEY_C_DECL extern "C"
#else
#  define HEDLEY_BEGIN_C_DECLS
#  define HEDLEY_END_C_DECLS
#  define HEDLEY_C_DECL
#endif

#if defined(HEDLEY_STATIC_ASSERT)
#  undef HEDLEY_STATIC_ASSERT
#endif
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#  define HEDLEY_STATIC_ASSERT(expr, message) _Static_assert(expr, message)
#elif HEDLEY_GCC_HAS_FEATURE(c_static_assert,4,6,0)
#  define HEDLEY_STATIC_ASSERT(expr, message) _Static_assert(expr, message)
#elif HEDLEY_MSVC_VERSION_CHECK(16,0,0)
#  define HEDLEY_STATIC_ASSERT(expr, message) static_assert(expr, message)
#else
#  define HEDLEY_STATIC_ASSERT(expr, message)
#endif

#endif /* !defined(HEDLEY_VERSION) || (HEDLEY_VERSION < X) */
