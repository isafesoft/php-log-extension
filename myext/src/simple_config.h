/*
 * simple_config.h
 *
 *  Created on: 20160526
 *      Author: MarkX
 */

#ifndef SIMPLE_CONFIG_H_
#define SIMPLE_CONFIG_H_


#include "simple_public.h"
#include "simple_log.h"

int get_config_map(const char *config_file, std::map<std::string, std::string> &configs);

#endif /* SIMPLE_CONFIG_H_ */
