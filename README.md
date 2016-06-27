# Hedley

**HEDLEY IS NOT READY FOR USE YET**.  Really, I haven't even tried to
compile anything with it yet.  I'm posting it very early in hopes that
I'll get some feedback from C developers.  If you have any thougts or
ideas, *please* use the issue tracker, or just e-mail me.  If you like
the idea but don't really have anything to contribute, just star the
repo on GitHub so I know there is interest.

Hedley is C a header file designed to smooth over some
platform-specific annoyances.  The idea is to get rid of a bunch of
the #ifdefs in your code, and put them in Hedley instead.

You can safely use Hedley in your *public* API.  If someone else
includes a newer version of Hedley later on, the newer Hedley will
just redefine everything, and if someone includes an older version it
will simply be ignored.

It should be safe to use any of Hedley's features; if the platform
doesn't support the feature it will be silently ignored.  The only
required feature we can't really ifdef around is variadic macros,
which are part of C99, but have been supported in virtually every
compiler as an extension for much longer…  the only time you're likely
to notice anything is if you're using C < C99 or C++ < C++11 and
compiling with `-Wpedantic` (or something similar).

## Usage

First, include the Hedley header:

```c
#include "hedley/hedley.h"
```

If your API isn't public, that's it.  If it is public, that *can* be
it, but we suggest you do a bit more…  see the "Public API in
Libraries" section for details.

Once you include the Hedley header, you'll have access to lots of
macros which are defined differently depending on your platform.  For
example, there is a `HEDLEY_NON_NULL` macro which can be used to
indicate that specific function parameters should never be NULL.

### Versioning Macros

#### `HEDLEY_ENCODE_VERSION(major, minor, revision)`

This macro is used to encode semantic version information into a
single value which can easily be tested in other macros.  It assumes
each part of the version fits in 8-bits.

### Compiler Versions and Feature Checking

#### `HEDLEY_GCC_VERSION_CHECK`

Check whether your compiler is (pretending to be) a version of GCC
greater than or equal to the specified value.

#### `HEDLEY_GCC_NOT_CLANG_VERSION_CHECK`

Like HEDLEY_GCC_VERSION_CHECK, but defined to 0 for clang.

This is important because we might want to do something like
`HEDLEY_HAS_ATTRIBUTE(foo) || HEDLEY_GCC_VERSION_CHECK(x,y,z)`, and if
the first part fails but the second part returns true it could result
in bad code.

#### `HEDLEY_GCC_VERSION_CHECK`

Check whether your compiler is a version of MSVC greater than or equal
to the specified value.

#### `HEDLEY_CLANG_HAS_X(y)`

Where X is one of:

 * ATTRIBUTE
 * BUILTIN
 * FEATURE
 * EXTENSION
 * DECLSPEC_ATTRIBUTE

Defined to the relevant __has_* macro if the compiler is clang, or 0
for other compilers.  This should generally be used for feature
detection on clang instead of the version numbers, especially since
Apple ships a version of clang with higher version numbers...

#### `HEDLEY_GCC_HAS_X(y, major, minor, patch)`

These macros are just a shortcut for writing:

```c
HEDLEY_CLANG_HAS_*(y) || HEDLEY_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch)
```

### For Public APIs

#### `HEDLEY_DEPRECATED(since)`

Mark a symbol as deprecated since `since` (currently a string,
debating using a version encoded with `HEDLEY_VERSION_ENCODE`
instead).

This is meant to be used in conjuction with a header file like that
descibed later on, in the "Public API in Libraries" section.

#### `HEDLEY_DEPRECATED_FOR(since, replacement)`

Like `HEDLEY_DEPRECATED`, but also tell the consumer what the
replacement is.

This is meant to be used in conjuction with a header file like that
descibed later on, in the "Public API in Libraries" section.

#### `HEDLEY_UNAVAILABLE(available_since)`

Emit a warning that the symbol is only available in `available_since`
and up.

This is meant to be used in conjuction with a header file like that
descibed later on, in the "Public API in Libraries" section.

#### `HEDLEY_INTERNAL`/`HEDLEY_EXTERNAL`/`HEDLEY_IMPORT`

These can/should be used by libraries to specify which symbols are
publicly visible.  Note, however, that they shouldn't be used
directly, at least in public headers.

This is meant to be used in conjuction with a header file like that
descibed later on, in the "Public API in Libraries" section.

### Trigger Warnings on API Misuse

#### `HEDLEY_ARRAY_PARAM(param)`

Used for
[conformant array parameters](https://www.securecoding.cert.org/confluence/display/c/API05-C.+Use+conformant+array+parameters).

#### `HEDLEY_WARN_UNUSED_RESULT`

Function attribute which will cause supported compilers to warn if the
result of the function is not used.

#### `HEDLEY_SENTINEL(position)`

Function attribute which annotates a function requires an explicit
NULL to denote the end of a variadic argument list.  Counting starts
at 0 from the last (right-most) parameter.

#### `HEDLEY_NO_RETURN`

Function attribute to indicate that the function will never return.

#### `HEDLEY_UNREACHABLE()`

Tells supported compilers that the code should never be reached.

#### `HEDLEY_NON_NULL(param...)`

Function attribute which tells supported compilers that values passed
to the listed parameters (identified by position number) should never
be NULL.

#### `HEDLEY_PRINTF_FORMAT(string_idx, first_to_check)`

Tells the compiler that the function takes a printf-style format
string so it can be checked at compile time.

### Performance Optimizations

#### `HEDLEY_MALLOC`

Tells the compiler that the returned value cannot alias anything.

#### `HEDLEY_LIKELY/UNLIKELY(expr)`

Used to inform the compiler that the expression is likely (or
unlikely) to evaluate to true.

Note that these macros will always return 0 (if the expression
evaluates to 0) or 1 (for everything else).

#### `HEDLEY_INLINE`/`HEDLEY_ALWAYS_INLINE`/`HEDLEY_NEVER_INLINE`

HEDLEY_INLINE asks the compiler to inline, but leaves the final
decision up to the compiler (like "inline" in the C99 standard).
`HEDLEY_ALWAYS_INLINE` takes it a step further and tells the compiler
to *always* inline the function, and `HEDLEY_NEVER_INLINE` tells the
compiler *never* to inline the function.

Note that not all of these are supported by every compiler.  Most
compilers, however, should behave.

#### `HEDLEY_NO_THROW`

Tell the compiler that this function will never throw a C++ exception.

That's right, C++ screws everything up even when the API is written in
pure C.

### Public API in Libraries

If you're writing something with a public API, I strongly recommend
using quotes instead of angled brackets, and using the relative path
to a header you distribute.  Otherwise, you may be including an older
version from another library which doesn't have all the features you
need.

If you want to use certain optional features in you API, there is a
bit more work to do:

#### Versioning

GLib's version macros are the best I've seen.  Hedley does what it can
to help you replicate the experience, but there is still a bit for you
to do.

```c
#include "hedley/hedley.h"

/* Define these to whatever your version number is. */
#define FOO_VERSION_MAJOR X
#define FOO_VERSION_MINOR Y
#define FOO_VERSION_REVISION Z

#define FOO_VERSION HEDLEY_VERSION_ENCODE(FOO_VERSION_MAJOR, FOO_VERSION_MINOR, FOO_VERSION_REVISION)

#if !defined(FOO_TARGET_VERSION)
#  define FOO_TARGET_VERSION FOO_VERSION
#endif

/* Define one of these for each version you add API in, then add
 * FOO_AVAILABLE_IN_X_Y to your functions.  If the consumer is
 * targeting an older version of your library and uses a function
 * marked with this, Hedley will try to emit a warning.
 *
 * Obviously, you can use X_Y_Z, or whatever you want, but if you
 * don't add API in revisions X_Y is sufficient, and it helps keep
 * the number of macros manageable. */
#if FOO_VERSION < HEDLEY_VERSION_ENCODE(x,y,0)
#  define FOO_AVAILABLE_IN_X_Y HEDLEY_UNAVAILABLE("x.y")
#else
#  define FOO_AVAILABLE_IN_X_Y
#endif

/* Similar to the above, except this warns if consumers attempt to
 * use a function which has been deprecated in the release they are
 * targeting. */
#if FOO_VERSION > HEDLEY_VERSION_ENCODE(x,y,0)
#  define FOO_DEPRECATED_SINCE_X_Y HEDLEY_DEPRECATED("x.y")
#  define FOO_DEPERCATED_SINCE_X_Y_FOR(replacement) HEDLEY_DEPRECATED_FOR("x.y", replacement)
#else
#  endif FOO_DEPRECATED_SINCE_X_Y
#  endif FOO_DEPRECATED_SINCE_X_Y_FOR(replacement)
#endif
```

At some point, I'll probably put together a script to automate this.

Once you have your library-specific version header, you can start
using it to declare your API:

```c
FOO_AVAILABLE_IN_1_0
void i_am_available_in_version_one_point_zero (void);

FOO_AVAILABLE_IN_1_0
FOO_DEPRECATED_SINCE_1_2_FOR(better_function)
void you_should_not_use_me (void);

FOO_AVAILABLE_IN_1_2
void better_function (void);
```

When someone uses your API, if they just include your header then it
is assumed that they are targeting the latest version of your API.
Attempting to use `you_should_not_use_me` will result in a warning
about the function being deprecated, but using `better_function` will
get rid of the warning.

However, if they want to target an earlier version (for example, maybe
they want to make sure their code works with an LTS version of
Ubuntu), all they need to do is something like:

```c
#define FOO_TARGET_VERSION HEDLEY_VERSION_ENCODE(1,1,0)

#include <your-header.h>
```

Now, when they try to use `better_function`, they'll see a warning
message saying `better_function` isn't available in 1.1.0, but if they
use `you_should_not_use_me` it will compile cleanly.

#### Function Visibility

Function visibility is simpler than versioning.  You really just need
to define a couple simple macros:

```c
#if defined(FOO_COMPILATION)
#  define FOO_API HEDLEY_PUBLIC
#else
#  define FOO_API HEDLEY_IMPORT
#endif
```

Then, add `-DFOO_COMPILATION` (or whatever your compiler wants) in the
C flags you use to build your library, but *not* in the C flags people
use to build *against* your library.

If you compile with `-fvisibility=hidden`, only symbols annotated with
`FOO_API` will be visible.  If you'd like to avoid adding the
visibility flag but still want the same effect, just annotate your
internal functions with `HEDLEY_PRIVATE`.

## FAQ

### "Hedley"?

It's named after a character from
[Blazing Saddles](http://www.imdb.com/title/tt0071230/) named "Hedley
Lamarr", who is named after
[Hedy Lamarr](https://en.wikipedia.org/wiki/Hedy_Lamarr).  While
better known as an actress, Hedy Lamarr was also an inventor (of,
among other things, frequency-hopping spread spectrum radios).
