#include "../hedley.h"

#ifdef __cplusplus
struct Empty2 {};
struct Empty3 {};
struct HEDLEY_EMPTY_BASES Derived3 : Empty2, Empty3
{
  char c;
};
#if !defined(HEDLEY_MSVC_VERSION) || HEDLEY_MSVC_VERSION_CHECK(19,0,23918)
HEDLEY_STATIC_ASSERT(sizeof(Derived3) == sizeof(Empty2), "empty base optimization failed");
#endif
#endif /* __cplusplus */

int main(void) {
  return 0;
}
