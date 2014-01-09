#include "psd_native_ext.h"

VALUE psd_native_blender_compose_bang(VALUE self) {
  psd_logger("debug", "Composing with native code");

  VALUE Compose = rb_const_get(
    rb_const_get(rb_cObject, rb_intern("PSD")),
    rb_intern("Compose")
  );
  
  VALUE fg = rb_iv_get(self, "@fg");
  VALUE bg = rb_iv_get(self, "@bg");
  VALUE bg_canvas = rb_funcall(bg, rb_intern("canvas"), 0);

  int offset_x = psd_clamp_int(
    FIX2INT(rb_funcall(fg, rb_intern("left"), 0)) -
    FIX2INT(rb_funcall(bg, rb_intern("left"), 0)),
    0,
    FIX2INT(rb_funcall(bg, rb_intern("width"), 0))
  );

  int offset_y = psd_clamp_int(
    FIX2INT(rb_funcall(fg, rb_intern("top"), 0)) -
    FIX2INT(rb_funcall(bg, rb_intern("top"), 0)),
    0,
    FIX2INT(rb_funcall(bg, rb_intern("height"), 0))
  );

  int fg_height = FIX2INT(rb_funcall(fg, rb_intern("height"), 0));
  int fg_width = FIX2INT(rb_funcall(fg, rb_intern("width"), 0));
  int bg_height = FIX2INT(rb_funcall(bg, rb_intern("height"), 0));
  int bg_width = FIX2INT(rb_funcall(bg, rb_intern("width"), 0));

  VALUE blending_mode = rb_funcall(rb_funcall(fg, rb_intern("node"), 0), rb_intern("blending_mode"), 0);
  VALUE* fg_pixels = psd_canvas_to_pixel_array(fg);
  VALUE* bg_pixels = psd_canvas_to_pixel_array(bg);
  VALUE options = rb_funcall(self, rb_intern("compose_options"), 0);

  int x, y, base_x, base_y;
  VALUE color;
  for (y = 0; y < fg_height; y++) {
    for (x = 0; x < fg_width; x++) {
      base_x = x + offset_x;
      base_y = y + offset_y;

      if (base_x < 0 || base_y < 0 || base_x >= bg_width || base_y >= bg_height) {
        continue;
      }

      color = rb_funcall(
        Compose,
        rb_intern_str(blending_mode),
        3,
        fg_pixels[y * fg_width + x],
        bg_pixels[base_y * bg_width + base_x],
        options
      );

      rb_funcall(
        bg_canvas, 
        rb_intern("[]="),
        3,
        INT2FIX(base_x),
        INT2FIX(base_y),
        color
      );
    }
  }

  return Qnil;
}