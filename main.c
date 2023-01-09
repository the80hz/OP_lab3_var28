#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD 50

int minus(const char *str){
    if (str[0] != '-')
        return 0;
    return 1;
}

int plus(const char *str){
    if (str[0] != '+')
        return 0;
    return 1;
}

char* check_type(char* str, int *type){
    int i = 0;
    // check int or short or long

    if (str[i] == 'i' && str[i + 1] == 'n' && str[i + 2] == 't' && str[i + 3] == ' '){
        str += 4;
        *type = 1;
    }
    if (str[i] == 's' && str[i + 1] == 'h' && str[i + 2] == 'o' && str[i + 3] == 'r' && str[i + 4] == 't' && str[i + 5] == ' '){
        str += 6;
        *type = 2;
    }
    if (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'n' && str[i + 3] == 'g' && str[i + 4] == ' '){
        str += 5;
        *type = 1;
    }
    return str;
}

int number(const char *str){
    int i = 0;
    while (str[i] != '\0' && str[i] != ';' && str[i] != '\n'){
        if (!isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}

char* get_word(char* str, char* word) {
    int i = 0;
    while (isspace(*str))
        str++;
    while (!isspace(*str) && *str != '\0')
        word[i++] = *str++;
    word[i] = '\0';
    return str;
}

char* check_ses(char* str){
    // check " = "
    if (str[0] == ' ' && str[1] == '=' && str[2] == ' '){
        str += 3;
        return str;
    }
    return NULL;
}

int main() {
    int type = 0;
    char str[WORD] = {0};
    printf("Enter the value:\n");

    fgets(str, WORD, stdin);
    printf("str: %s", str);
    char* str2;

    // check of type variable
    str2 = check_type(str, &type);
    if (type == 0){
        printf("Error: type is not defined.\n");
        return -1;
    }

    // check of name variable
    str2 = get_word(str2, str);
    for(int i = 0; i < strlen(str); i++){
        if (!isalpha(str[i])){
            printf("Error: name is not defined.\n");
            return -1;
        }
    }

    // check of " = "
    str2 = check_ses(str2);
    if (str2 == NULL){
        printf("Error: \" = \" is not defined.\n");
        return -1;
    }


    // with minus or plus symbol
    if (minus(str2) || plus(str2)){
        // if 12th symbol not '\0' or '\n' or ';'
        if (str2[11] != '\n' && str2[11] != '\0' && str2[11] != ';'){
            printf("\nIncorrect value");
            return -1;
        }
        // delete first symbol
        char *str3 = str2 + 1;

        // check if the number correct
        if (!number(str3)){
            printf("\nIncorrect value");
            return -1;
        }
    }
    else{
        // if 12th symbol not '\0' or '\n'
        if (str2[10] != '\n' && str2[10] != '\0'  && str2[10] != ';'){
            printf("\nIncorrect value");
            return -1;
        }
        // check if the number correct
        if (!number(str2)){
            printf("\nIncorrect value");
            return -1;
        }
    }

    // convert string to double
    double num = atof(str2);

    // check if the number is in the range
    if (type == 1){
        if (num < -2147483648 || num > 2147483647){
            printf("\nOut of range");
            return -1;
        }
    }
    if (type == 2){
        if (num < -32768 || num > 32767){
            printf("\nOut of range");
            return -1;
        }
    }
    // check ; symbol in the end
    if (str2[strlen(str2) - 2] != ';'){
        printf("\nMissing symbol ;");
        return -1;
    }

    printf("\nnum: %f", num);

    return 0;
}
