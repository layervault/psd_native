#include "psd_native_ext.h"

void Init_psd_native() {
  VALUE PSDNative = rb_define_module("PSDNative");
  VALUE ImageMode = rb_define_module_under(PSDNative, "ImageMode");

  VALUE ImageMode_RGB = rb_define_module_under(ImageMode, "RGB");
  rb_define_private_method(ImageMode_RGB, "combine_rgb_channel", psd_native_combine_rgb_channel, 0);

  printf("NATIVE ENABLED\n");
}