//
// Created by duguying on 16/8/18.
//

#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>

enum SState{
    STAT_NONE = 0,              // 初始状态
    STAT_GROUP,                 // 组名状态
    STAT_KEY,                   // 键状态
    STAT_VALUE,                 // 值状态
    STAT_VALUE_STRING,          // 字符串
    STAT_VALUE_STRING_BLOCK,    // 值字符串块状态
    STAT_VALUE_INLINE_COMMENT,  // 值行内注释状态
    STAT_VALUE_IDENT,           // 值标识符状态
    STAT_VALUE_NUMBER,          // 值数字状态
    STAT_COMMENT                // 注释状态
};



int read_token();
void read_char(char c);

#endif //INI_PARSER_H
