#include "ustr.h"

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