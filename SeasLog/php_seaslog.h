
#ifndef PHP_SEASLOG_H
#define PHP_SEASLOG_H

extern zend_module_entry seaslog_module_entry;
#define phpext_seaslog_ptr &seaslog_module_entry

#ifdef PHP_WIN32
#	define PHP_SEASLOG_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_SEASLOG_API __attribute__ ((visibility("default")))
#else
#	define PHP_SEASLOG_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define SEASLOG_VERSION                     "0.22"
#define SEASLOG_AUTHOR                      "neeke@php.net"

#define SEASLOG_TYPE_INFO                   (1<<0)
#define SEASLOG_TYPE_WARN                   (1<<1)
#define SEASLOG_TYPE_ERRO                   (1<<1) + 1

#define SEASLOG_TYPE_INFO_STR                       "INFO"
#define SEASLOG_TYPE_WARN_STR                       "WARN"
#define SEASLOG_TYPE_ERRO_STR                       "ERRO"

PHP_MINIT_FUNCTION(seaslog);
PHP_MSHUTDOWN_FUNCTION(seaslog);
PHP_RINIT_FUNCTION(seaslog);
PHP_RSHUTDOWN_FUNCTION(seaslog);
PHP_MINFO_FUNCTION(seaslog);

PHP_FUNCTION(seaslog_set_basepath);
PHP_FUNCTION(seaslog_get_basepath);
PHP_FUNCTION(seaslog_set_logger);
PHP_FUNCTION(seaslog_get_lastlogger);
PHP_FUNCTION(seaslog);
PHP_FUNCTION(seaslog_analyzer_count);
PHP_FUNCTION(seaslog_analyzer_detail);
PHP_FUNCTION(seaslog_get_buffer);

ZEND_BEGIN_MODULE_GLOBALS(seaslog)
	char *default_basepath;
	char *default_logger;
	char *logger;
	char *last_logger;
	char *base_path;
    zend_bool disting_type;
    zend_bool disting_by_hour;
    zend_bool use_buffer;
ZEND_END_MODULE_GLOBALS(seaslog)

/* In every utility function you add that needs to use variables 
   in php_seaslog_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as SEASLOG_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define SEASLOG_G(v) TSRMG(seaslog_globals_id, zend_seaslog_globals *, v)
#else
#define SEASLOG_G(v) (seaslog_globals.v)
#endif

#endif	/* PHP_SEASLOG_H */

