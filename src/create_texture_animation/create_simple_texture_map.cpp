extern "C" {
  #include "stb_image.h"
  #include "stb_image_write.h"
}
#include <cassert>
#include <cstdint>
#include <cstdlib>

typedef struct {
    uint32_t *pixels;
    uint32_t width, height, stride;
} Img;

typedef struct {
    float *items;
    uint32_t width, height, stride;
} Mat;

Mat mat_malloc(uint32_t width, uint32_t height)
{
    Mat mat = {0};
    float* items = (float*)malloc(sizeof(float)*width*height);
    assert(items != NULL);
    return (Mat) {
      .items = items,
      .width = width,
      .height = height,
      .stride = width,
    };
}

void calc_luminescence(Img* rgb_image, Mat* lum_mat) {
  for(unsigned int i = 0; i< rgb_image->width* rgb_image->height; i++) {
    float r = ((rgb_image->pixels[i] >> (8 * 0)) & 0xFF) / 255.0;
    float g = ((rgb_image->pixels[i] >> (8*1)) & 0xFF)/255.0;
    float b = ((rgb_image->pixels[i] >> (8*2)) & 0xFF)/255.0;
    lum_mat->items[i] =  0.2126*r + 0.7152*g + 0.0722*b;
  }
}

void calc_sobel_filter(Mat lum_mat, Mat sobel_mat){
  //TODO
}

int main (){
  char file_path[] = "test_img.png";
  int width_ = 0;
  int height_ = 0;
  uint32_t *pixels_ = (uint32_t*)stbi_load(file_path, &width_, &height_, NULL, 4);
  if (pixels_ == NULL) {
    fprintf(stderr, "ERROR: could not read %s\n", file_path);
    return 1;
  }
  Img img = {
    .pixels = pixels_,
    .width = (uint32_t)width_,
    .height = (uint32_t)height_,
    .stride = (uint32_t) width_,
  };
  Mat lum_mat = mat_malloc(width_, height_);
  calc_luminescence(&img, &lum_mat);

  delete pixels_;
  delete lum_mat.items;
}
