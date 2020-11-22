#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <regex.h>

struct string_mx {
    size_t size;
    size_t maxsize;
    char *cstr;
};

typedef int errno_t;
typedef struct string_mx string_mx;

extern errno_t strcopy_m(string_mx*, string_mx *);
extern string_mx* strcreate_m(char*, int);

int main(int argc, char **argv) 
{   
    string_mx *str = NULL;
    string_mx *bufStr = NULL;
    char buffer[256];    
    if(argc != 2) 
    {   
        exit(0);    
    }

    if (strlen(argv[1]) == 0 || strlen(argv[1]) >= sizeof(buffer)) {
        printf("lmaoxd\n");
        exit(0);
    }

    //lexical check
    regex_t reg;
    int ret = regcomp(&reg, "[a-zA-Z0-9]", 0); //whitelist alpha-numeric characters
    ret = regexec(&reg, argv[1], 0 , NULL, 0);
    if (ret == REG_NOMATCH) {
        printf("bad input\n");
        exit(0);
    }

    //assert check
    assert(sizeof(buffer) > strlen(argv[1]));

    //secure types, enforce security checks
    str = strcreate_m(argv[1], strlen(argv[1])+1); //null terminator
    bufStr = strcreate_m(buffer, sizeof(buffer));
    
    printf("%p\n", bufStr->cstr);   
    //checks whether source string fits exactly into dest string
    if (strcopy_m(str, bufStr) == 0) {
        printf("pass\n");
    }
    else {
        printf("fail\n");
    }

    printf("%s\n", bufStr->cstr);    
    //strcpy_s(buffer, argv[1]);    

    //frees
    free(str);
    free(bufStr); 
    return 0;
}

extern errno_t strcopy_m(string_mx *source, string_mx *dest) {
    //force checks whether input is larger than the buffersize 
    if (source->size >= dest->maxsize) {
        return -1;
    }
    else {
        strcpy(dest->cstr, source->cstr);
        return 0;
    }
}

extern string_mx* strcreate_m(char* string, int max) {
    string_mx *str = (string_mx*) malloc(sizeof(string_mx));
    str->maxsize = max;
    str->size = strlen(string);
    str->cstr = string;

    return str;
}











