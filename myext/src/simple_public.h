/*
#include <time.h>
 * simple_public.h
 *	public head files
 *  Created on: May 31, 2016
 *      Author: jw
 */

#ifndef SRC_SIMPLE_PUBLIC_H_
#define SRC_SIMPLE_PUBLIC_H_

#include <cstring>
#include <string>
#include <map>
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <iostream>
#include <sys/syscall.h>//Linux system call for thread id
#include <pthread.h>
#include <vector>
typedef std::vector<std::string> vstring;

#define PIN
#define POUT
#define PINOUT

#define STR_SP_LOGFIELD '#'
#define STR_SP_LINEHEAD "=>"
#define STR_LOG_ENDTAG '\n'

//default log configuration file path
#define STR_CONFIG_PATH "/tmp/moshConfig"
#define STR_CONFIG_FILENAME "moshlog.conf"




#endif /* SRC_SIMPLE_PUBLIC_H_ */
