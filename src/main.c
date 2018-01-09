#include <stdio.h>
#include "main.h"

void set_lang(void);

int main()
{
    printf("Hello World");
    set_lang();
}

void set_lang(void)
{
    int i;
    for (i = 0; i < 27; ++i) {
      lunmanP[i] = lunmanT[i];
    }
    for (i = 0; i < 27; ++i) {
      yogaP[i] = yogaT[i];
    }
    for (i = 0; i < 11; ++i) {
      byedP[i] = byedT[i];
    }
}
