#include "psd_native_ext.h"

VALUE psd_native_clipping_mask_apply(VALUE self) {
  VALUE layer = rb_iv_get(self, "@layer");
  if (rb_funcall(layer, rb_intern("clipped?"), 0) == Qfalse) {
    return rb_iv_get(self, "@png");
  }

  psd_logger("debug", "Applying clipping mask with native code");

  VALUE *dim = RARRAY_PTR(rb_funcall(layer, rb_intern("document_dimensions"), 0));
  VALUE full_png = rb_funcall(self, rb_intern("compose_to_full"), 0);

  uint32_t width = FIX2UINT(dim[0]);
  uint32_t height = FIX2UINT(dim[1]);
  VALUE mask = rb_funcall(self, rb_intern("mask"), 0);
  VALUE pixel_data = rb_funcall(rb_funcall(mask, rb_intern("image"), 0), rb_intern("pixel_data"), 0);
  VALUE pixel;
  uint32_t color;
  int mask_top = FIX2INT(rb_funcall(mask, rb_intern("top"), 0)),
      mask_bottom = FIX2INT(rb_funcall(mask, rb_intern("bottom"), 0)),
      mask_left = FIX2INT(rb_funcall(mask, rb_intern("left"), 0)),
      mask_right = FIX2INT(rb_funcall(mask, rb_intern("right"), 0)),
      mask_width = FIX2INT(rb_funcall(mask, rb_intern("width"), 0)),
      alpha = 0,
      mask_x, mask_y;

  int x, y;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      if (y < mask_top || y > mask_bottom || x < mask_left || x > mask_right) {
        alpha = 0;
      } else {
        mask_x = x - mask_left;
        mask_y = y - mask_top;

        pixel = rb_ary_entry(pixel_data, mask_y * mask_width + mask_x);
        if (pixel == Qnil) {
          alpha = 0;
        } else {
          alpha = A(FIX2UINT(pixel));
        }
      }

      color = FIX2UINT(rb_funcall(full_png, rb_intern("[]"), 2, INT2FIX(x), INT2FIX(y)));
      color = (color & 0xffffff00) | (A(color) * alpha / 255);
      rb_funcall(full_png, rb_intern("set_pixel"), 3, INT2FIX(x), INT2FIX(y), INT2FIX(color));
    }
  }

  return rb_funcall(
    full_png,
    rb_intern("crop!"),
    4,
    rb_funcall(layer, rb_intern("left"), 0),
    rb_funcall(layer, rb_intern("top"), 0),
    rb_funcall(layer, rb_intern("width"), 0),
    rb_funcall(layer, rb_intern("height"), 0)
  );
}