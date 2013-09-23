#include "psd_native_ext.h"

void Init_psd_native() {
  VALUE PSDNative = rb_define_module("PSDNative");
  VALUE ImageMode = rb_define_module_under(PSDNative, "ImageMode");

  // RGB Processing
  VALUE ImageMode_RGB = rb_define_module_under(ImageMode, "RGB");
  rb_define_private_method(ImageMode_RGB, "combine_rgb_channel", psd_native_combine_rgb_channel, 0);

  // CMYK Processing
  VALUE ImageMode_CMYK = rb_define_module_under(ImageMode, "CMYK");
  rb_define_private_method(ImageMode_CMYK, "combine_cmyk_channel", psd_native_combine_cmyk_channel, 0);

  // RLE decoding
  VALUE ImageFormat = rb_define_module_under(PSDNative, "ImageFormat");
  VALUE RLE = rb_define_module_under(ImageFormat, "RLE");
  rb_define_private_method(RLE, "decode_rle_channel", psd_native_decode_rle_channel, 0);

  // Color functions
  VALUE Color = rb_define_module_under(PSDNative, "Color");
  rb_define_singleton_method(Color, "cmyk_to_rgb", psd_native_cmyk_to_rgb, 4);

  psd_logger("info", "PSD native mixins enabled!");
}

VALUE psd_class() {
  return rb_const_get(rb_cObject, rb_intern("PSD"));
}

void psd_logger(char* level, char* message) {
  rb_funcall(rb_funcall(psd_class(), rb_intern("logger"), 0), rb_intern(level), 1, rb_str_new2(message));
}

VALUE psd_file(VALUE self) {
  return rb_iv_get(self, "@file");
}

int psd_file_tell(VALUE self) {
  return FIX2INT(rb_funcall(psd_file(self), rb_intern("tell"), 0));
}