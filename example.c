#include<stdio.h>
int main()
{
    printf("BEFORE USING ANSI escape codes\n");
    printf("TEXT WITH DEFAULT COLOUR\n");
    printf("AFTER USING ANSI escape codes\n");
    printf("\033[1;31mThis is Red text\033[0m\n");
    printf("\033[1;32mThis is Green text\033[0m\n");
    printf("\033[1;34mThis is Blue text\033[0m\n");
}