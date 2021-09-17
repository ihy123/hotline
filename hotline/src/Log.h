#pragma once
#include <stdlib.h>
#include <stdio.h>

#if defined(_DEBUG) || !defined(NDEBUG)
#define LOG_TRACE(format, ...) printf("TRACE: " format "\n", __VA_ARGS__)
#define LOG_INFO(format, ...) printf("INFO: " format "\n", __VA_ARGS__)
#else
#define LOG_TRACE(format, ...)
#define LOG_INFO(format, ...)
#endif

#define LOG_ERROR(format, ...) printf("ERROR: " format "\n", __VA_ARGS__)
#define LOG_CRITICAL(format, ...) printf("CRITICAL ERROR: " format "\n", __VA_ARGS__)
#define EXIT_CRITICAL(format, ...) { LOG_CRITICAL(format, __VA_ARGS__); exit(1); }
