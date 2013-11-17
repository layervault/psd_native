#include "psd_native_ext.h"

VALUE psd_native_cmyk_to_rgb(VALUE self, VALUE c, VALUE m, VALUE y, VALUE k) {
  int r, g, b;

  r = psd_clamp_int((65535 - (FIX2INT(c) * (255 - FIX2INT(k)) + (FIX2INT(k) << 8))) >> 8, 0, 255);
  g = psd_clamp_int((65535 - (FIX2INT(m) * (255 - FIX2INT(k)) + (FIX2INT(k) << 8))) >> 8, 0, 255);
  b = psd_clamp_int((65535 - (FIX2INT(y) * (255 - FIX2INT(k)) + (FIX2INT(k) << 8))) >> 8, 0, 255);

  VALUE result = rb_hash_new();
  rb_hash_aset(result, ID2SYM(rb_intern("r")), INT2FIX(r));
  rb_hash_aset(result, ID2SYM(rb_intern("g")), INT2FIX(g));
  rb_hash_aset(result, ID2SYM(rb_intern("b")), INT2FIX(b));

  return result;
}

int psd_clamp_int(int n, int low, int high) {
  return n < low ? low : (n > high ? high : n);
}

int opaque(uint32_t color) {
  return a(color) == 0x000000ff;
}

int transparent(uint32_t color) {
  return a(color) == 0x00000000;
}

uint32_t r(uint32_t color) {
  return (color & 0xff000000) >> 24;
}

uint32_t g(uint32_t color) {
  return (color & 0x00ff0000) >> 16;
}

uint32_t b(uint32_t color) {
  return (color & 0x0000ff00) >> 8;
}

uint32_t a(uint32_t color) {
  return color & 0x000000ff;
}

uint32_t rgba(uint32_t r, uint32_t g, uint32_t b, uint32_t a) {
  return r << 24 | g << 16 | b << 8 | a;
}