#pragma once

#ifndef PI
#define PI 3.141592653589793238462643383279
#endif // PI

#ifndef PI2
#define PI2 6.283185307179586476925286766558
#endif // PI2

#ifndef RandF
#define RandF() ((float)rand() / (float)RAND_MAX)
#endif

#ifndef Debug
#ifdef DEBUG_BUILD
#include <iostream>
#define Debug(msg) std::cout << msg << std::endl
#else
#define Debug(msg) /**/
#endif
#endif
