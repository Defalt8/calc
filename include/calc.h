#pragma once
#ifndef __calc_h__
#define __calc_h__

#define CALCAPI extern

#ifdef __cplusplus
extern "C" {
#endif

CALCAPI const int CALC_VERSION_MAJOR, CALC_VERSION_MINOR, CALC_VERSION_PATCH;
CALCAPI double calcEvaluate(const char* expression);

#ifdef __cplusplus
}
#endif

#endif // __calc_h__