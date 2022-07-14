#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    // x = column coordinate y = row coordinate c = channel number
    int columns = im.w;
    int rows = im.h;
    int channels = im.c;

    if(x < columns){
        if(x <= 0){
            x = 0;
        }
    }
    else{
        x = columns - 1;
    }

    if(y < rows){if(y <= 0){ y = 0;}}
    else{y = rows - 1;}

    if(c < channels){if(c <= 0){c = 0;}}
    else{c = channels - 1;}

    float pixel_value = im.data[x + y*columns + c*columns*rows]; // data array stores floating pixel values

    return pixel_value;
}

void set_pixel(image im, int x, int y, int c, float v)
{
    int columns = im.w;
    int rows = im.h;
    int channels = im.c;
    int column_assertion = 1;
    int row_assertion = 1;
    int channel_assertion = 1;

    // 0: Out of bounds 1: Within limits
    if(x >= 0 && x < columns) column_assertion = 0;
    if(y >= 0 && y < rows) row_assertion = 0;
    if(c >=0 && c < channels) channel_assertion = 0;

    if(column_assertion){
        printf("Column index is out of bounds");
        return;
    }

    if(row_assertion){
        printf("Row index is out of bound   ");
        return;
    }

    if(channel_assertion){
        printf("Channel index is out of bound");
        return;
    }

    im.data[x + y*columns + c*columns*rows] = v;
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    for(int i=0; i<im.w*im.h*im.c; i++){
        copy.data[i] = im.data[i];
    }
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    float weight_r = 0.299;
    float weight_g = 0.587;
    float weight_b = 0.114;

    for(int i=0; i<gray.h*gray.w*gray.c; i++) {
        gray.data[i] = weight_r*im.data[i] + weight_g*im.data[i + im.h*im.w] + weight_b*im.data[i + 2*im.h*im.w];
    }
    return gray;
}

void shift_image(image im, int c, float v)
{
    for(int i=0; i<im.h*im.w; i++) {
        im.data[i + c*im.h*im.w] = v + im.data[i + c*im.h*im.w];
    }
}

void clamp_image(image im)
{
    for(int i=0; i<im.h*im.w*im.c; i++) {
        if(im.data[i] < 0) im.data[i] = 0;
        else if(im.data[i] > 1) im.data[i] = 1;
    }
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    float r, g, b, C, V, S, H_prime, H, m;
    for(int i=0; i<im.h*im.w; i++) {
        r = im.data[i];
        g = im.data[i + im.h*im.w];
        b = im.data[i + 2*im.h*im.w];

        V = three_way_max(r,g,b); // Value
        m = three_way_min(r, g, b);
        C = V - m;

        if(V != 0) {
            S = C/V; // Saturation
        }
        else S = 0;

        if (C == 0) H_prime = 0.0;
        else if(V == r) H_prime = (g-b)/C;
        else if(V == g) H_prime = (b-r)/C + 2;
        else if(V == b) H_prime = (r-g)/C + 4;

        if(H_prime < 0) H = H_prime/6 + 1;
        else H = H_prime/6;

        im.data[i] = H;
        im.data[i + im.h*im.w] = S;
        im.data[i + 2*im.h*im.w] = V;
    }
}

void hsv_to_rgb(image im)
{

}
