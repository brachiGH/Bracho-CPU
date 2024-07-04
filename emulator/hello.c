#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define EMSCRIPTEN_KEEPALIVE_FUNC EMSCRIPTEN_KEEPALIVE
#else
#define EMSCRIPTEN_KEEPALIVE_FUNC
#endif

// Define the function and mark it as EMSCRIPTEN_KEEPALIVE when compiling with Emscripten
EMSCRIPTEN_KEEPALIVE_FUNC void myFunction() {
    printf("MyFunction Called\n");
}
