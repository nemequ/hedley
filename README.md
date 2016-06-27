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
