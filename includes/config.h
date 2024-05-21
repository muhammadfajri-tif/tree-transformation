#if !defined(config_H)
#define config_H

// Setup for OS
#if defined(_WIN32)
#define PLATFORM_NAME "windows" // Windows
#elif defined(_WIN64)
#define PLATFORM_NAME "windows" // Windows
#elif defined(__CYGWIN__) && !defined(_WIN32)
#define PLATFORM_NAME "windows" // Windows (Cygwin POSIX under Microsoft Window)
#elif defined(__ANDROID__)
#define PLATFORM_NAME "android" // load android first because it also linux
#elif defined(__linux__)
#define PLATFORM_NAME "linux" // linux
#elif defined(linux)
#define PLATFORM_NAME "linux" // linux
#elif defined(__linux)
#define PLATFORM_NAME "linux" // linux
#endif

// Setup for File configuration (used in file.h)
#define DEFAULT_TREE_FILE "tree.dat"
#endif // currentos_H
