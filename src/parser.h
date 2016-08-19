//
// Created by duguying on 16/8/18.
//

#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>

enum SState{
    STAT_NONE = 0,
    STAT_GROUP,
    STAT_KEY,
    STAT_VALUE,
    STAT_VALUE_STRING_BLOCK,
    STAT_COMMENT
};



int read_token();
void read_char(char c);

#endif //INI_PARSER_H
