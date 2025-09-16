#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <chrono>
#include <iomanip>

#ifdef __linux__
#include <execinfo.h>
#include <cxxabi.h>
#include <memory>
#include <cstdlib>
#endif

inline bool Debug()
{
#ifdef DEBUG
    return true;
#else
    return false;
#endif
}

inline std::string getCurrentTimestamp()
{
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  now.time_since_epoch()) %
              1000;

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%H:%M:%S");
    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

#ifdef __linux__
inline std::string demangle(const char *symbol)
{
    int status = 0;
    std::unique_ptr<char, void (*)(void *)> res{
        abi::__cxa_demangle(symbol, nullptr, nullptr, &status),
        std::free};
    return (status == 0) ? res.get() : symbol;
}

inline std::string caller_info(int skip = 1)
{
    void *callstack[10];
    int frames = backtrace(callstack, 10);
    char **strs = backtrace_symbols(callstack, frames);

    std::string result = "unknown";

    if (frames > skip)
    {
        std::string raw(strs[skip]);
        // extract function name between '(' and '+'
        auto begin = raw.find('(');
        auto plus = raw.find('+', begin);
        if (begin != std::string::npos && plus != std::string::npos)
        {
            std::string mangled = raw.substr(begin + 1, plus - begin - 1);
            result = demangle(mangled.c_str());
        }
    }
    free(strs);
    return result;
}

inline std::pair<std::string, std::string> get_caller_class_method(int skip = 2)
{
    std::string caller = caller_info(skip);
    size_t colon_pos = caller.find("::");
    if (colon_pos != std::string::npos)
    {
        std::string class_name = caller.substr(0, colon_pos);
        std::string method_name = caller.substr(colon_pos + 2);
        // remove ()
        size_t paren_pos = method_name.find('(');
        if (paren_pos != std::string::npos)
        {
            method_name = method_name.substr(0, paren_pos);
        }
        return {class_name, method_name};
    }
    else
    {
        // global function
        size_t paren_pos = caller.find('(');
        std::string method_name = (paren_pos != std::string::npos) ? caller.substr(0, paren_pos) : caller;
        return {"global", method_name};
    }
}
#else
// Windows fallback - use compiler intrinsics for better caller info
inline std::pair<std::string, std::string> get_caller_class_method(int skip = 2)
{
    // On Windows, we can't easily get stack trace without additional libs
    // Return empty strings to signal we should use __FUNCTION__ instead
    return {"", ""};
}
#endif

#ifdef DEBUG
// Use different approaches for Linux vs Windows
#ifdef __linux__
#define DEBUG_LOG(message)                                                                                              \
    do                                                                                                                  \
    {                                                                                                                   \
        auto caller = get_caller_class_method();                                                                        \
        std::stringstream ss;                                                                                           \
        ss << "[" << getCurrentTimestamp() << "] [" << caller.first << "::" << caller.second << "]: " << message; \
        std::cout << ss.str() << std::endl;                                                                             \
    } while (0)
#else
// Windows version - use __FUNCTION__ for better caller info
#define DEBUG_LOG(message)                                                                     \
    do                                                                                         \
    {                                                                                          \
        std::stringstream ss;                                                                  \
        ss << "[" << getCurrentTimestamp() << "] [" << __FUNCTION__ << "]: " << message; \
        std::cout << ss.str() << std::endl;                                                    \
    } while (0)
#endif
#else
#define DEBUG_LOG(message)
#endif

#endif
