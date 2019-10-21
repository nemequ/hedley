#include "../hedley.h"

int main(int argc, char* argv[HEDLEY_ARRAY_PARAM(argc)]) {
  int foo = 0;

  HEDLEY_STATIC_CAST(void, argv);

  switch (argc) {
    case 2:
      foo = 1;
      break;
    case 1:
      foo = 2;
      HEDLEY_FALL_THROUGH;
    default:
      foo = 3;
      break;
  }

  return foo;
}
