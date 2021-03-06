#ifndef LOG_G_INCLUDED
#define LOG_G_INCLUDED

#include <stdio.h>
#include <stdarg.h>

enum LOG_MSG_TYPE {
    LOG_MSG_INFO, LOG_MSG_WARNING, LOG_MSG_ERROR, LOG_MSG_FATAL
};

enum LOG_FORMAT {
    LOG_FORMAT_RAW, LOG_FORMAT_HTML,  
};

struct LoggerContext {
    LOG_MSG_TYPE lvl;
    const char  *file_name;  //  NULL - log to stderr 
    LOG_FORMAT   format;    
};

struct Logger {
    const LoggerContext context;
    FILE * const output;
};

void log_set_context_lvl (LOG_MSG_TYPE log_lvl);
void log_set_context_file_name (const char *file_name);
void log_set_context_format (LOG_FORMAT fmt);

Logger *log_instance();

struct LoggerLocation {
    int         nline;
    const char *file;
    const char *func;
};

void log_msg (LoggerLocation loc, LOG_MSG_TYPE type, const char *msg, ...);
void log_msg_varg (LoggerLocation loc, LOG_MSG_TYPE type, const char *msg, va_list *args);

#ifdef DO_LOGS
    #define LOG_SET_CONTEXT_LVL( lvl )              log_set_context_lvl (lvl)
    #define LOG_SET_CONTEXT_FILE_NAME( file_name )  log_set_context_file_name (file_name)
    #define LOG_SET_CONTEXT_FORMAT( format)         log_set_context_format (format)

    #define LOG_INFO( ... )     log_msg ({ __LINE__, __FILE__, __FUNCTION__ }, LOG_MSG_INFO, __VA_ARGS__)
    #define LOG_WARNING( ... )  log_msg ({ __LINE__, __FILE__, __FUNCTION__ }, LOG_MSG_WARNING, __VA_ARGS__)
    #define LOG_ERROR( ... )    log_msg ({ __LINE__, __FILE__, __FUNCTION__ }, LOG_MSG_ERROR, __VA_ARGS__)
    #define LOG_FATAL( ... )    log_msg ({ __LINE__, __FILE__, __FUNCTION__ }, LOG_MSG_FATAL, __VA_ARGS__)
#else
    #define LOG_SET_CONTEXT_LVL( lvl )              ;
    #define LOG_SET_CONTEXT_FILE_NAME( file_name )  ;
    #define LOG_SET_CONTEXT_FORMAT( format )        ;

    #define LOG_INFO( ... )     ;
    #define LOG_WARNING( ... )  ;
    #define LOG_ERROR( ... )    ;
    #define LOG_FATAL( ... )    ;
#endif 

#endif // LOG_G_INCLUDED