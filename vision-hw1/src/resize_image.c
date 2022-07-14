#include <math.h>
#include "image.h"

float nn_interpolate(image im, float x, float y, int c)
{
   return get_pixel(im,round(x), round(y), c);
}

image nn_resize(image im, int w, int h)
{
    /*
     * Mapping equations
        * (scaling_factor) * x_top_left_corner_new + displacement_factor = x_top_left_corner_old
        * (scaling_factor) * x_bottom_right_corner_new + displacement_factor = x_bottom_right_corner_old
        * Find scaling_factor and displacement_factor using old_img and new_img corners
            * old_corners = (-0.5, -.0.5) and (im.w-0.5, im.h-0.5)
            * new_corners = (-0.5, -0.5) and (w-0.5, h-0.5)
     */
    image resized_img = make_image(w, h, im.c);
    float scaling_factor, displacement_factor, new_pixel_value;

    float x_top_left_corner_old = -0.5;
    float x_top_left_corner_new = -0.5;
    float x_bottom_right_corner_old = im.h-0.5;
    float x_bottom_right_corner_new = h-0.5;

    scaling_factor = (x_bottom_right_corner_old - x_top_left_corner_old)/(x_bottom_right_corner_new - x_top_left_corner_new);
    displacement_factor = x_bottom_right_corner_old - scaling_factor * x_bottom_right_corner_new;

    /*
     * Iterate over new pixels and interpolate the new pixel and set_pixel
     */

    for(int i=0; i<w; i++) {
       for(int j=0; j<h; j++) {
           for(int k=0; k<im.c; k++) {
               float x_new_to_old = scaling_factor * i + displacement_factor;
               float y_new_to_old = scaling_factor * j + displacement_factor;

               new_pixel_value = nn_interpolate(im,x_new_to_old,y_new_to_old,k);
               set_pixel(resized_img,i,j,k,new_pixel_value);
           }
       }
    }
    return resized_img;
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // TODO
    return 0;
}

image bilinear_resize(image im, int w, int h)
{
    // TODO
    return make_image(1,1,1);
}

