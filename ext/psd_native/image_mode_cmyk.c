#include "psd_native_ext.h"

VALUE psd_native_combine_cmyk_channel(VALUE self) {
  psd_logger("debug", "Beginning CMYK processing");
  
  uint32_t num_pixels = FIX2UINT(rb_iv_get(self, "@num_pixels"));
  uint32_t pixel_step = FIX2UINT(rb_funcall(self, rb_intern("pixel_step"), 0));

  VALUE* channel_data = RARRAY_PTR(rb_iv_get(self, "@channel_data"));
  uint32_t channel_length = FIX2UINT(rb_iv_get(self, "@channel_length"));
  uint32_t channel_count = FIX2UINT(rb_funcall(self, rb_intern("channels"), 0));

  int i;
  uint32_t r, g, b;
  VALUE a, c, m, y, k, rgb;

  // Loop through every pixel in the image
  for (i = 0; i < num_pixels; i += pixel_step) {
    if (channel_count == 5) {
      a = channel_data[i];
      c = channel_data[i + channel_length];
      m = channel_data[i + channel_length * 2];
      y = channel_data[i + channel_length * 3];
      k = channel_data[i + channel_length * 4];
    } else {
      a = 255;
      c = channel_data[i];
      m = channel_data[i + channel_length];
      y = channel_data[i + channel_length * 2];
      k = channel_data[i + channel_length * 3];
    }

    rgb = psd_native_cmyk_to_rgb(
      self, 
      INT2FIX(255 - FIX2INT(c)), 
      INT2FIX(255 - FIX2INT(m)), 
      INT2FIX(255 - FIX2INT(y)),
      INT2FIX(255 - FIX2INT(k))
    );


    r = FIX2UINT(rb_hash_aref(rgb, ID2SYM(rb_intern("r"))));
    g = FIX2UINT(rb_hash_aref(rgb, ID2SYM(rb_intern("g"))));
    b = FIX2UINT(rb_hash_aref(rgb, ID2SYM(rb_intern("b"))));

    rb_ary_push(rb_iv_get(self, "@pixel_data"), INT2FIX(BUILD_PIXEL(r, g, b, a)));
  }

  return Qnil;
}