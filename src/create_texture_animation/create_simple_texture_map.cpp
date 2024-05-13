#include <cstring>
extern "C" {
  #include "stb_image.h"
  #include "stb_image_write.h"
}
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <float.h>

typedef struct {
    uint32_t *pixels;
    uint32_t width, height, stride;
} Img;

typedef struct {
    float *items;
    uint32_t width, height, stride;
} Mat;

Mat mat_malloc(uint32_t width, uint32_t height) {
  float* items = (float*)malloc(sizeof(float)*width*height);
  assert(items != NULL);
  return (Mat) {
    .items = items,
    .width = width,
    .height = height,
    .stride = width,
  };
}

Img img_malloc(uint32_t width, uint32_t height) {
  uint32_t* pixels = (uint32_t*)malloc(sizeof(uint32_t)*width*height);
  assert(pixels != NULL);
  return (Img) {
    .pixels = pixels,
    .width = width,
    .height = height,
    .stride = width,
  };
}

void min_and_max(Mat mat_in, float *mn, float *mx)
{
  *mn = FLT_MAX;
  *mx = FLT_MIN;
  for (int i = 0; i < mat_in.height * mat_in.width; i++) {
    float value = mat_in.items[i];
    if (value < *mn) *mn = value;
    if (value > *mx) *mx = value;
  }
}

void mat_to_img(Mat mat_in, Img img_out) {
  float min, max = 0;
  min_and_max(mat_in, &min, &max);
  for (int i = 0; i < mat_in.height * mat_in.width; i++) {
    uint32_t value = (int)(255.0*(mat_in.items[i]-min)/(max-min));
    img_out.pixels[i] = 0xff000000 + value + (value << 8) + (value << (8*2));
  }
}

void calc_luminance(Img* rgb_image, Mat* lum_mat) {
  for(unsigned int i = 0; i< rgb_image->width* rgb_image->height; i++) {
    float r = ((rgb_image->pixels[i] >> (8 * 0)) & 0xFF) / 255.0;
    float g = ((rgb_image->pixels[i] >> (8*1)) & 0xFF)/255.0;
    float b = ((rgb_image->pixels[i] >> (8*2)) & 0xFF)/255.0;
    lum_mat->items[i] =  0.2126*r + 0.7152*g + 0.0722*b;
  }
}

void calc_sobel_filter(Mat *lum_mat, Mat *sobel_mat){
  assert(lum_mat->width == sobel_mat->width);
  assert(lum_mat->height == sobel_mat->height);

  static float kx[3][3] = {
    {1.0, 0.0, -1.0},
    {2.0, 0.0, -2.0},
    {1.0, 0.0, -1.0},
  };

  static float ky[3][3] = {
    {1.0, 2.0, 1.0},
    {0.0, 0.0, 0.0},
    {-1.0, -2.0, -1.0},
  };

  memset(sobel_mat->items, 0 , sobel_mat->width*sobel_mat->height*sizeof(float));
  for (int cy = 1; cy < lum_mat->height-1; cy++) {
    for (int cx = 1; cx < lum_mat->width-1; cx++) {
      float sx = 0.0;
      float sy = 0.0;

      for (int dkx = 0; dkx < 3; dkx++) {
        for (int dky = 0; dky < 3; dky++) {
          sx += lum_mat->items[(cy-1+dky)*lum_mat->width+(cx-1+dkx)] * kx[dky][dkx];
          sy += lum_mat->items[(cy-1+dky)*lum_mat->width+(cx-1+dkx)] * ky[dky][dkx];
        }
      }
      sobel_mat->items[cy * sobel_mat->width + cx] = sx*sx + sy*sy;
    }
  }
}

int main (){
  char file_in_path[] = "test_img.png";
  char lum_file_out_path[] = "lum_img.png";
  char sobel_file_out_path[] = "sobel_img.png";
  int width_ = 0;
  int height_ = 0;
  uint32_t *pixels_ = (uint32_t*)stbi_load(file_in_path, &width_, &height_, NULL, 4);
  if (pixels_ == NULL) {
    fprintf(stderr, "ERROR: could not read %s\n", file_in_path);
    return 1;
  }
  Img img = {
    .pixels = pixels_,
    .width = (uint32_t)width_,
    .height = (uint32_t)height_,
    .stride = (uint32_t) width_,
  };

  // calc lumance
  Mat lum_mat = mat_malloc(width_, height_);
  calc_luminance(&img, &lum_mat);

  Img lum_img = img_malloc(width_, height_);
  mat_to_img(lum_mat, lum_img);
  if (!stbi_write_png(lum_file_out_path, lum_img.width, lum_img.height, 4, lum_img.pixels, lum_img.stride*sizeof(uint32_t))) {
    fprintf(stderr, "ERROR: could not save lum_img to file %s\n", lum_file_out_path);
    return 1;
  }

  // calc sobel
  Mat sobel_mat = mat_malloc(width_, height_);
  calc_sobel_filter(&lum_mat, &sobel_mat);

  Img sobel_img = img_malloc(width_, height_);
  mat_to_img(sobel_mat, sobel_img);
  if (!stbi_write_png(sobel_file_out_path, sobel_img.width, sobel_img.height, 4, sobel_img.pixels, sobel_img.stride*sizeof(uint32_t))) {
    fprintf(stderr, "ERROR: could not save sobel_img to file %s\n", sobel_file_out_path);
    return 1;
  }

  delete pixels_;
  delete lum_mat.items;
  delete lum_img.pixels;
  delete sobel_mat.items;
  delete sobel_img.pixels;
  return 0;
}
