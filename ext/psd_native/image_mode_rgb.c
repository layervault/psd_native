#include "psd_native_ext.h"

VALUE psd_native_combine_rgb_channel(VALUE self) {
  psd_logger("debug", "Beginning RGB processing");
  
  uint32_t num_pixels = FIX2UINT(rb_iv_get(self, "@num_pixels"));
  uint32_t pixel_step = FIX2UINT(rb_funcall(self, rb_intern("pixel_step"), 0));

  VALUE* channels_info = RARRAY_PTR(rb_iv_get(self, "@channels_info"));
  VALUE* channel_data = RARRAY_PTR(rb_iv_get(self, "@channel_data"));
  uint32_t channel_length = FIX2UINT(rb_iv_get(self, "@channel_length"));
  int channel_count = RARRAY_LENINT(rb_iv_get(self, "@channels_info"));

  int i, j;
  uint32_t val, r, g, b, a;

  int channel_ids[channel_count];
  for (i = 0; i < channel_count; i++) {
    channel_ids[0] = FIX2INT(rb_hash_aref(channels_info[i], ID2SYM(rb_intern("id"))));
  }

  // Loop through every pixel in the image
  for (i = 0; i < num_pixels; i += pixel_step) {
    r = g = b = 0;
    a = 255;

    // And every channel for every pixel
    for (j = 0; j < channel_count; j++) {
      val = FIX2UINT(channel_data[i + (channel_length * j)]);

      // Get the hash containing channel info
      switch (channel_ids[j]) {
        case -1: a = val; break;
        case 0:  r = val; break;
        case 1:  g = val; break;
        case 2:  b = val; break;
      }
    }

    rb_ary_push(rb_iv_get(self, "@pixel_data"), INT2FIX(BUILD_PIXEL(r, g, b, a)));
  }

  return Qnil;
}