#include "psd_native_ext.h"

VALUE psd_native_build_preview_blend_pixels(
  VALUE self, 
  VALUE blending_mode, 
  VALUE layer, 
  VALUE base, 
  VALUE other, 
  VALUE r_offset_x, 
  VALUE r_offset_y) {

  int x, y, base_x, base_y, offset_x, offset_y;
  uint32_t width, height, base_width, base_height;
  VALUE color;
  VALUE Compose = rb_const_get(rb_const_get(rb_cObject, rb_intern("PSD")), rb_intern("Compose"));
  // char * blend_mode = StringValueCStr(blending_mode);

  psd_logger("debug", "BLENDING PIXELS NATIVELY");

  width = FIX2UINT(rb_funcall(other, rb_intern("width"), 0));
  height = FIX2UINT(rb_funcall(other, rb_intern("height"), 0));
  base_width = FIX2UINT(rb_funcall(base, rb_intern("width"), 0));
  base_height = FIX2UINT(rb_funcall(base, rb_intern("height"), 0));
  offset_x = FIX2INT(r_offset_x);
  offset_y = FIX2INT(r_offset_y);
  
  VALUE opacity = rb_hash_new();
  rb_hash_aset(
    opacity, 
    ID2SYM(rb_intern("opacity")),
    rb_funcall(layer, rb_intern("opacity"), 0)
  );

  rb_hash_aset(
    opacity,
    ID2SYM(rb_intern("fill_opacity")),
    rb_funcall(layer, rb_intern("fill_opacity"), 0)
  );

  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      base_x = x + offset_x;
      base_y = y + offset_y;

      if (base_x < 0 || base_y < 0 || base_x >= base_width || base_y >= base_height) continue;

      color = rb_funcall(
        Compose,
        rb_intern_str(blending_mode),
        3,
        rb_funcall(other, rb_intern("[]"), 2, INT2FIX(x), INT2FIX(y)),
        rb_funcall(base, rb_intern("[]"), 2, INT2FIX(base_x), INT2FIX(base_y)),
        opacity
      );

      rb_funcall(base, rb_intern("[]="), 3, INT2FIX(base_x), INT2FIX(base_y), color);
    }
  }

  return Qnil;
}