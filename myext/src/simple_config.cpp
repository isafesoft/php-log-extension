/*
 * simple_config.cpp
 *
 *  Created on: 20160526
 *      Author: MarkX
 */
#include <fstream>
#include <sstream>
#include <errno.h>
#include "simple_config.h"

int get_config_map(const char *config_file, std::map<std::string, std::string> &configs) {
    std::ifstream fs(config_file);
    if(!fs.is_open()) {
        return (errno << 16) | ERR_OPENFILE;
    }

    while(fs.good()) {
        std::string line;
        std::getline(fs, line);

        if (line[0] == '#') {
            continue;
        }
        std::stringstream ss;
        ss << line;
        std::string key, value;
        std::getline(ss, key, '=');
        std::getline(ss, value, '=');

        configs[key] = value;
    }
    fs.close();
    return ERR_OK;
}
