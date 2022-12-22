/* Определить, является ли заданный текст корректным синтаксисом определения целочисленной переменной.
 *
 * [-2 147 483 648, +2 147 483 647]
 * -2147483648
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX 13

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

int number(const char *str){
    int i = 0;
    while (str[i] != '\0'){
        if (!isdigit(str[i]) && str[i] != '\n')
            return 0;
        i++;
    }
    return 1;
}

int main() {
    setlocale(LC_ALL, "Russian");

    printf("Enter the value:\n");
    char str[MAX] = {0};
    
    fgets(str, MAX, stdin);
    printf("str: %s", str);
    
    // with minus or plus symbol
    if (minus(str) || plus(str)){
        // if 12th symbol not '\0' or '\n'
        if (str[11] != '\n' && str[11] != '\0'){
            printf("\nIncorrect value");
            return 0;
        }
        // delete first symbol
        char *str1 = str + 1;

        // check if the number correct
        if (!number(str1)){
            printf("\nIncorrect value");
            return 0;
        }
    }
    else{
        // if 12th symbol not '\0' or '\n'
        if (str[10] != '\n' && str[10] != '\0'){
            printf("\nIncorrect value");
            return 0;
        }
        // check if the number correct
        if (!number(str)){
            printf("\nIncorrect value");
            return 0;
        }
    }
    // convert string to double
    double num = atof(str);
    printf("\nnum: %lf", num);

    // check if the number in range
    if (num < -2147483648 || num > 2147483647){
        printf("\nIncorrect value");
        return 0;
    }
    printf("\nCorrect value");

    return 0;
}
