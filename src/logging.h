//================================================================
//Author: Sanskar Chand <sanskarchand@gmail.com>
//Date  : 2021-09-17
//================================================================
#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>
#include <string.h>

#define SEPLINE0     "################"         //16 chars
#define SEPLINE1     "================"
#define SEPLINE_USED SEPLINE1

// C will merge adjacent literals
#define SEPLINE     (SEPLINE_USED SEPLINE_USED SEPLINE_USED SEPLINE_USED SEPLINE_USED)    

#define LOG_DEF_FILENAME "murchhserv.log"

#define __FILENAME__ ( strrchr(__FILE__, '/') ? \
        strrchr(__FILE__, '/') + 1 : __FILE__ )

#define LL_INFO     "INFO"
#define LL_DEBUG    "DEBUG"
#define LL_ERROR    "ERROR"


#define LOG_INIT_STDOUT()     \
    _log_stream = stdout;  \
    LOG_INIT()

#define LOG_INIT_FILE()      \
    _log_stream = fopen(LOG_DEF_FILENAME, "a"); \
    LOG_INIT()

#define LOG_INIT_FILENAME(fname) \
    _log_stream = fopen(fname, "a"); \
    LOG_INIT()

#define LOG_CLOSE()     fclose(_log_stream); 

#define LOG(level, ...) \
    fprintf(_log_stream, "[%s] %s|%s (%s:%d:%s): ", level, __DATE__, \
            __TIME__, __FILENAME__, __LINE__, __func__); \
    fprintf(_log_stream, __VA_ARGS__); \
    fputc('\n', _log_stream); \
    fflush(_log_stream);

#define LOG_INIT() \
    fprintf(_log_stream, "%s\n", SEPLINE); \
    LOG_INFO("Log started");


#define LOG_INFO(...) LOG(LL_INFO, __VA_ARGS__)
#define LOG_ERROR(...) LOG(LL_ERROR, __VA_ARGS__)


//initialize this in main.c
extern FILE *_log_stream;

//only for __GNUCC_ char _log_linebuf[64] = {[0 ... 64] = SEP_CHAR};

#endif //LOGGING_H
