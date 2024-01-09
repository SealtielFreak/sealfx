#include "ustr.h"

#include <ctype.h>
#include <string.h>

int findchr(char *str, char chr) {
    int indice = 0;

    while (str[indice] != '\0') {

        if (str[indice] == chr) {
            return indice;
        }

        indice++;
    }

    return -1;
}

void tolower_str(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
}