
#pragma once

#ifndef COMMON_H
#define COMMON_H

#ifdef _WIN32
#define OS_WIN
#elif __APPLE__
#define OS_APPLE
#elif __linux__
#define OS_LINUX
#warning Linux
#elif __unix__
#define OS_UNIX
#else
#error Unsupported Operating System
#endif

#include "util.h"

#endif
