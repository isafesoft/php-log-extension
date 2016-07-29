/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */
extern "C" {
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
}

#include <sys/syscall.h>//Linux system call for thread id
#include <assert.h>
#include <pthread.h>
#include "php_myext.h"

//jw classes
#include "jwlog.cpp"
#include "src/simple_public.h"
#include "src/simple_log.h"
#include "src/simple_config.h"
#include "src/simple_log.cpp"
#include "src/simple_config.cpp"
#include "src/simple_tool.h"
#include "src/simple_tool.cpp"
/* If you declare any globals in php_myext.h uncomment this: */

ZEND_DECLARE_MODULE_GLOBALS(myext)

/* True global resources - no need for thread safety here */
static int le_myext;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("myext.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_myext_globals, myext_globals)
    STD_PHP_INI_ENTRY("myext.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_myext_globals, myext_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_myext_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_myext_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "myext", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_myext_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_myext_init_globals(zend_myext_globals *myext_globals)
{
	myext_globals->global_value = 0;
	myext_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(myext)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(myext)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(myext)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(myext)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(myext)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "myext support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ myext_functions[]
 *
 * Every user visible function must have an entry in myext_functions[].
 */
const zend_function_entry myext_functions[] = {
	PHP_FE(confirm_myext_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(php_mytest, NULL)
	PHP_FE(mlBeginSpan, NULL) //store current milli seconds, used by mlGetSpan
	PHP_FE(mlGetSpan, NULL) //get span from laster begin timer
	PHP_FE(mlGetUuid, NULL) //get span from laster begin timer
	PHP_FE(mlogDebug, NULL) //get span from laster begin timer
	PHP_FE(mlogInfo, NULL) //get span from laster begin timer
	PHP_FE(mlogError, NULL) //get span from laster begin timer
	PHP_FE(mlogCritical, NULL) //get span from laster begin timer
	PHP_FE(mlogEmergency, NULL) //get span from laster begin timer
	PHP_FE(mlogAlert, NULL) //get span from laster begin timer
	PHP_FE(mlGetConf, NULL) //get span from laster begin timer
	PHP_FE(mlGetConfPath, NULL) //get span from laster begin timer
	PHP_FE(mlGetSavePath, NULL) //get span from laster begin timer
	PHP_FE_END	/* Must be the last line in myext_functions[] */
};
/* }}} */

/* {{{ myext_module_entry
 */
zend_module_entry myext_module_entry = {
	STANDARD_MODULE_HEADER,
	"myext",
	myext_functions,
	PHP_MINIT(myext),
	PHP_MSHUTDOWN(myext),
	PHP_RINIT(myext),		/* Replace with NULL if there's nothing to do at request start */

	PHP_RSHUTDOWN(myext),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(myext),
	PHP_MYEXT_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MYEXT
ZEND_GET_MODULE(myext)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
//set timer begin
PHP_FUNCTION(mlBeginSpan)
{
 	MYEXT_G(g_startTimer)  = mlBeginSpan(); 
}

PHP_FUNCTION(mlGetSpan)
{
	int ms = mlGetSpan(MYEXT_G(g_startTimer));
        RETURN_LONG(ms);
	
}

#define PARSEPARAM(ttjw) \
	zval *arr, **data;\
    HashTable *arr_hash;\
    HashPosition pointer;\
    int array_count;\
\
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arr) == FAILURE) {\
\
        RETURN_NULL();\
\
    }\
	if(Z_TYPE_P(arr) == IS_ARRAY)\
	{\
		php_printf("array coming");\
	}\
\
	arr_hash = Z_ARRVAL_P(arr);\
	array_count = zend_hash_num_elements(arr_hash);\
	php_printf("array len: %d", array_count);\
\
	for(zend_hash_internal_pointer_reset_ex(arr_hash, &pointer); zend_hash_get_current_data_ex(arr_hash, (void**) &data, &pointer) == SUCCESS; zend_hash_move_forward_ex(arr_hash, &pointer)) \
	{\
		zval temp;\
	    char *key;\
	    uint key_len;\
	    ulong index;\
\
	    if (zend_hash_get_current_key_ex(arr_hash, &key, &key_len, &index, 0, &pointer) == HASH_KEY_IS_STRING) {\
		PHPWRITE(key, key_len);\
	    } else {\
		php_printf("%ld", index);\
	    }\
\
	    temp = **data;\
	    zval_copy_ctor(&temp);\
	    convert_to_string(&temp);\
	    ttjw.push_back(Z_STRVAL(temp));\
	}



PHP_FUNCTION(mlogDebug)
{
	vstring arrValue;
	PARSEPARAM(arrValue);
	std::string str = formatLogString(arrValue);
	int res =  log_debug(str.c_str());
	RETURN_LONG(res);
}

PHP_FUNCTION(mlogInfo)
{
	vstring arrValue;
	PARSEPARAM(arrValue);
	std::string str = formatLogString(arrValue);
	int res =  log_info(str.c_str());
	php_printf("log_err:%d", res);
	RETURN_LONG(res);
}

PHP_FUNCTION(mlogEmergency)
{
	vstring arrValue;
	PARSEPARAM(arrValue);
	std::string str = formatLogString(arrValue);
	int res =  log_emergency(str.c_str());
	php_printf("log_err:%d", res);
	RETURN_LONG(res);
}

PHP_FUNCTION(mlogCritical)
{
	vstring arrValue;
	PARSEPARAM(arrValue);
	std::string str = formatLogString(arrValue);
	int res =  log_critical(str.c_str());
	php_printf("log_err:%d", res);
	RETURN_LONG(res);
}


PHP_FUNCTION(mlogAlert)
{
	vstring arrValue;
	PARSEPARAM(arrValue);
	std::string str = formatLogString(arrValue);
	int res =  log_alert(str.c_str());
	php_printf("log_err:%d", res);
	RETURN_LONG(res);
}

PHP_FUNCTION(mlogError)
{
	vstring arrValue;
	PARSEPARAM(arrValue);
	std::string str = formatLogString(arrValue);
	int res =  log_error(str.c_str());
	php_printf("log_err:%d", res);
	RETURN_LONG(res);
/*

	zval *arr, **data;
    HashTable *arr_hash;
    HashPosition pointer;
    int array_count;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &arr) == FAILURE) {

        RETURN_NULL();

    }
	if(Z_TYPE_P(arr) == IS_ARRAY)
	{
		php_printf("array coming");
	}

	arr_hash = Z_ARRVAL_P(arr);
	array_count = zend_hash_num_elements(arr_hash);
	php_printf("array len: %d", array_count);

	for(zend_hash_internal_pointer_reset_ex(arr_hash, &pointer); zend_hash_get_current_data_ex(arr_hash, (void**) &data, &pointer) == SUCCESS; zend_hash_move_forward_ex(arr_hash, &pointer)) 
	{
		zval temp;
	    char *key;
	    uint key_len;
	    ulong index;

	    if (zend_hash_get_current_key_ex(arr_hash, &key, &key_len, &index, 0, &pointer) == HASH_KEY_IS_STRING) {
		PHPWRITE(key, key_len);
	    } else {
		php_printf("%ld", index);
	    }

	    php_printf(" => ");

	    temp = **data;
	    zval_copy_ctor(&temp);
	    convert_to_string(&temp);
	    PHPWRITE(Z_STRVAL(temp), Z_STRLEN(temp));
	    php_printf(",");
    		zval_dtor(&temp);	
	}//end for	
*/
	
}

PHP_FUNCTION(mlGetConf)
{
	std::string str;
	int res = getLogConf(str);
	RETURN_STRING(str.c_str(), str.length());
}

PHP_FUNCTION(mlGetConfPath)
{
	std::string str;
	int res = getLogConfPath(str);
	RETURN_STRING(str.c_str(), str.length());
	//RETURN_LONG(res);
}


PHP_FUNCTION(mlGetSavePath)
{
	std::string str;
	int res = getLogSavePath(str);
	RETURN_STRING(str.c_str(), str.length());
	//RETURN_LONG(res);
}

PHP_FUNCTION(mlGetUuid)
{
	char str[20] = "hi baby!";
	std::string uuid = mlGetUString();
	//php_printf(str);
	RETURN_STRING(uuid.c_str(), uuid.length());	
}

PHP_FUNCTION(php_mytest)
{
char *argv1= NULL ;
    char *argv2= NULL ; 
    int arg1_len, arg2_len;
if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &argv1, &arg1_len,&argv2,&arg2_len) == FAILURE) {
        return;
    }

	php_printf("<br>------<b>Log from internal Start</b>----<br>");
	php_printf("Thread Value: %d] :%d] inter_tid: %u]<br>", MYEXT_G(global_value), syscall(SYS_gettid),
	pthread_self());
	MYEXT_G(global_value) = MYEXT_G(global_value) + 1;	
	char szWorkDir[1024] = {0} ;  
    if(!getcwd(szWorkDir, 260))  
    {  
        return  ;  
    }  
	char szLogPath[1024] = "";
	char szLogConf[1024] = "";

	
 	std::string cfgPath = szWorkDir;
	cfgPath += "/conf";
     
       //int res = log_init(cfgPath.c_str(), "moshlog.conf");
	std::string path;
       int res = getLogConfPath(path);
	
	if( res)
	{
		php_printf("<br>%s log_init failed:0x%x, conf file  dir:%s <br>", getNowTimeString().c_str(), res, cfgPath.c_str());
		php_printf("err_msg: %s", strerror(res >> 16));
		return;
	}
	else
	{
		php_printf("<br>%s Read Log Configuration from %s<br>", getNowTimeString().c_str(), path.c_str());
	}
	res = getLogSavePath(path);
		
	//getLogConf(szLogConf, 1024);
	php_printf("<br>log Save Path:%s <br>------===<br>", path.c_str());

	res = getLogConf(path);

	php_printf("<br>log configuration:%s <br>------===<br>", path.c_str());

	res = logjw("%s", "this is a info jw  log");	
	php_printf("%s log write, ErrorCode: %x <br>", getNowTimeString().c_str(), res);
//	php_printf("argv1 :%s <br>", argv1);
//	php_printf("argv2 :%s\n", argv2);
	php_printf("<br>------<b>Log from internal END</b>----<br>");
double dValue = 3.3;
    RETURN_DOUBLE(dValue) ;
}
