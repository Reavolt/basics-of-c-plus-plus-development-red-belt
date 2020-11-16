#pragma once
#ifndef _PROFILE_H_
#define _PROFILE_H_

#include <chrono>
#include <iostream>
#include <string>

//-------------------------------------------------------------------------------------------------
class LogDuration
{
public:
    explicit LogDuration(const std::string& msg = "") :
            message(msg + " | "),
            start(std::chrono::steady_clock::now())
    {

    }

    ~LogDuration()
    {
        auto finish = std::chrono::steady_clock::now();
        auto duration = finish - start;

        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
        duration -= seconds;
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        duration -= milliseconds;
        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration);
        duration -= microseconds;
        auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
        duration -= nanoseconds;

        std::cerr << "================================================================================" << std::endl;
        std::cerr << message << std::endl;
        std::cerr << seconds.count() << " sec, " << std::endl;
        std::cerr << milliseconds.count() << " mils " << std::endl;
        std::cerr << microseconds.count() << " mics " << std::endl;
        std::cerr << nanoseconds.count() << " nans " << std::endl;
        std::cerr << "================================================================================" << std::endl;
    }
private:
    std::string message;
    std::chrono::steady_clock::time_point start;
};
//-------------------------------------------------------------------------------------------------
#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)
//-------------------------------------------------------------------------------------------------
#define LOG_DURATION(message) LogDuration UNIQ_ID(__LINE__) {message};
//-------------------------------------------------------------------------------------------------
#endif  //_PROFILE_H_