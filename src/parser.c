//
// Created by duguying on 16/8/18.
//

#include <parser.h>

enum SState syntax_state = STAT_NONE;
int has_point = 0;
char* value_keyword[] = {"true", "false"};

int read_token(){
    char* content = "; ini 配置文件解析测试"                      "\n"
                    "mode = dev"                                "\n"
                    "port=80"                                   "\n"
                    "host=192.168.1.11    ; 主机地址"           "\n"
                    "[mysql]"                                   "\n"
                    "host=\"192.168.1.16\""                     "\n"
                    "port=3306"                                 "\n"
                    "user=root"                                 "\n"
                    "password=lijun        # 密码"              "\n"
                    "[redis]        ; redis 服务器的配置"        "\n"
                    "host=192.168.1.14"                         "\n"
                    "# 字符串块测试"                              "\n"
                    "procode = `int main(){"                    "\n"
                    "               printf(\"hello world\");"   "\n"
                    "           }`"                             "\n"
                    "debug = true"                              "\n";

    for (int i = 0; i < strlen(content); ++i) {
        read_char(content[i]);
    }

    return 0;
}

#define COLOR_NONE      "\033[0m"
#define COLOR_GREEN     "\033[0;32m"
#define COLOR_YELLOW    "\033[1;33m"
#define COLOR_BLUE      "\033[0;34m"
#define COLOR_PINK      "\033[0;35m"
#define COLOR_CYAN      "\033[0;36m"

void read_char(char c){
    char buf[30];
    int i = 0;

    switch(syntax_state){
        case STAT_NONE:
        {
            if (c=='['){
                syntax_state = STAT_GROUP;
                printf(COLOR_CYAN);
                printf("%c",c);
            }else if (c==';' || c=='#'){
                syntax_state = STAT_COMMENT;
                printf(COLOR_GREEN);
                printf("%c",c);
            }else if (!isspace(c)){
                syntax_state = STAT_KEY;
                printf("%c",c);
            }else{
                printf("%c",c);
            }
            break;
        }
        case STAT_COMMENT:
        {
            if (c=='\n'){
                syntax_state = STAT_NONE;
                printf("%c",c);
                printf(COLOR_NONE);
            }else{
                printf("%c",c);
            }
            break;
        }
        case STAT_GROUP:
        {
            if (c==']' || c=='\n'){
                syntax_state = STAT_NONE;
                printf("%c",c);
                printf(COLOR_NONE);
            }else{
                printf("%c",c);
            }
            break;
        }
        case STAT_KEY:
        {
            if (c=='='){
                syntax_state = STAT_VALUE;
                printf(COLOR_YELLOW);
                printf("%c",c);
                printf(COLOR_NONE);
            }else{
                printf("%c",c);
            }
            break;
        }
        case STAT_VALUE:
        {
            if (c=='\n'){
                syntax_state = STAT_NONE;
                printf("%c",c);
                printf(COLOR_NONE);
            }else if (c=='`'){
                syntax_state = STAT_VALUE_STRING_BLOCK;
                printf(COLOR_BLUE);
                printf("%c",c);
            }else if (c==';' || c=='#') {
                syntax_state = STAT_VALUE_INLINE_COMMENT;
                printf(COLOR_GREEN);
                printf("%c",c);
            }else if (('a'<=c && 'z'>=c) || ('A'<=c && 'Z'>=c)){
                syntax_state = STAT_VALUE_IDENT;
                printf("%c",c);
            }else if ('0'<=c && '9'>=c){
                syntax_state = STAT_VALUE_NUMBER;
                has_point = 0;
                printf(COLOR_PINK);
                printf("%c",c);
            }else if (c=='"'){
                syntax_state = STAT_VALUE_STRING;
                printf(COLOR_BLUE);
                printf("%c",c);
            }else{
                printf("%c",c);
            }
            break;
        }
        case STAT_VALUE_STRING:
        {
            if (c=='"'){
                syntax_state = STAT_NONE;
                printf("%c",c);
                printf(COLOR_NONE);
            } else{
                printf("%c",c);
            }
            break;
        }
        case STAT_VALUE_NUMBER:
        {
            if (c=='\n'){
                syntax_state = STAT_NONE;
                printf("%c",c);
                printf(COLOR_NONE);
            }else if (c==';' || c=='#') {
                syntax_state = STAT_VALUE_INLINE_COMMENT;
                printf(COLOR_GREEN);
                printf("%c",c);
            }else if ('0'<=c && '9'>=c){
                printf("%c",c);
            }else if (c=='.'){
                if(has_point==0){
                    has_point = 1;
                    printf("%c",c);
                }else{
                    syntax_state = STAT_VALUE;
                    printf(COLOR_NONE);
                    printf("%c",c);
                }
            }else{
                syntax_state = STAT_VALUE;
                printf(COLOR_NONE);
                printf("%c",c);
            }
            break;
        }
        case STAT_VALUE_IDENT:
        {
            if (c=='\n'){
                syntax_state = STAT_NONE;
                printf("%c",c);
                printf(COLOR_NONE);
            }else if (c==';' || c=='#') {
                syntax_state = STAT_VALUE_INLINE_COMMENT;
                printf(COLOR_GREEN);
                printf("%c",c);
            }else{
                printf("%c",c);
            }
            break;
        }
        case STAT_VALUE_STRING_BLOCK:
        {
            if (c=='`'){
                syntax_state = STAT_VALUE;
                printf("%c",c);
                printf(COLOR_NONE);
            }else{
                printf("%c",c);
            }
            break;
        }
        case STAT_VALUE_INLINE_COMMENT:
        {
            if (c=='\n'){
                syntax_state = STAT_NONE;
                printf("%c",c);
                printf(COLOR_NONE);
            } else{
                printf("%c",c);
            }
            break;
        }
        default:
        {
            printf("%c",c);
        }
    }



}
