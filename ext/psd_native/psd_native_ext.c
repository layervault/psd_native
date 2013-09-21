#include "psd_native_ext.h"

void Init_psd_native() {
  VALUE PSDNative = rb_define_module("PSDNative");
  VALUE ImageMode = rb_define_module_under(PSDNative, "ImageMode");

  VALUE ImageMode_RGB = rb_define_module_under(ImageMode, "RGB");
  rb_define_private_method(ImageMode_RGB, "combine_rgb_channel", psd_native_combine_rgb_channel, 0);

  psd_logger("info", "PSD native mixins enabled!");
}

VALUE psd_class() {
  return rb_const_get(rb_cObject, rb_intern("PSD"));
}

void psd_logger(char* level, char* message) {
  rb_funcall(rb_funcall(psd_class(), rb_intern("logger"), 0), rb_intern(level), 1, rb_str_new2(message));
}