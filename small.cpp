#include <iostream>
using namespace std;

// typedef struct {
//     int w;
//     int h;
//     int c;
//     // float *data;
// } img;


// void increase(img *image)
// {
//     *image.h = *image.h + 1;
//     *image.w = *image.w + 1;
//     *image.c = *image.c + 1;
// }

// void replace(char *choices)
// {
//     &choices[0][0] = 'n';
// }

void change_bool(bool *b)
{
    *b = true;
}

int main () {

    bool b = false;
    change_bool(&b);

    // char **choices = (char *[]){ "New Game", "Continue Game", "Exit" };
    // replace(choices);
    // img im = { 4, 3, 3 };
    // cout << im.w << " " << im.h << " " << im.c << endl;
    // increase(&im);
    // cout << im.w << " " << im.h << " " << im.c << endl;
    // cout << choices[0] << endl;
    cout << 416 * 2 / 3 << endl;
    return 1;
}

// #include <stdio.h>
// void discount(float *a);
// int main()
// {
//  float price = 42.99;
//  printf("The item costs $%.2fn",price);
//  discount(&price);
//  printf("With the discount, that's $%.2fn",price);
//  return(0);
// }
// void discount(float *a)
// {
//  *a = *a * 0.90;
// }