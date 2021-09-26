#pragma once
#include <stdlib.h>
#include <stdio.h>

// simple synchronous logging through printf()
#define _INTERNAL_LOG_PATTERN(severity, format, ...) printf("[" #severity "] {" __FILE__ ":%d} " format "\n", __LINE__, __VA_ARGS__)

#ifdef NDEBUG
#define LOG_TRACE(format, ...)
#define LOG_INFO(format, ...)
#else
#define LOG_TRACE(format, ...) _INTERNAL_LOG_PATTERN(TRACE, format, __VA_ARGS__)
#define LOG_INFO(format, ...) _INTERNAL_LOG_PATTERN(INFO, format, __VA_ARGS__)
#endif

#define LOG_ERROR(format, ...) _INTERNAL_LOG_PATTERN(ERROR, format, __VA_ARGS__)
#define LOG_CRITICAL(format, ...) _INTERNAL_LOG_PATTERN(CRITICAL ERROR, format, __VA_ARGS__)
#define EXIT_CRITICAL(format, ...) { LOG_CRITICAL(format, __VA_ARGS__); exit(1); }
