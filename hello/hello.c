#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // hello world
    printf("hello, world \n");

    // define variable and ask name to user
    string name = get_string("What is your name? \n");

    // print a greeting message
    printf("hello, %s \n", name);
}