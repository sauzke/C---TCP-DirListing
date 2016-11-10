#include <stdio.h>
#include <string.h>
#include "dir.h"

Dir::Dir(){}

Dir::~Dir(){}

void Dir::GetPaths(char* input, char* out){
    dirp = opendir(input);
    if (dirp == NULL) {
        perror("openning dir");
    }
    while (d = readdir(dirp)) {
        strcat(out,d->d_name);
        strcat(out,"\n");
    }
    closedir (dirp);
}