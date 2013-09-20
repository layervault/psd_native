#include "psd_native_ext.h"

VALUE psd_native_combine_rgb_channel(VALUE self) {
  printf("PROCESSING RGB\n");

  int num_pixels = FIX2INT(rb_iv_get(self, "@num_pixels"));
  int pixel_step = FIX2INT(rb_funcall(self, rb_intern("pixel_step"), 0));

  VALUE channels_info = rb_iv_get(self, "@channels_info");
  VALUE channel_data = rb_iv_get(self, "@channel_data");
  int channel_count = FIX2INT(rb_funcall(channels_info, rb_intern("length"), 0));
  int channel_length = FIX2INT(rb_iv_get(self, "@channel_length"));
  
  VALUE channel;

  int i, j, r, g, b, a, val;

  // Loop through every pixel in the image
  for (i = 0; i < num_pixels; i += pixel_step) {
    r = g = b = 0;
    a = 255;

    // And every channel for every pixel
    for (j = 0; j < channel_count; j++) {
      val = FIX2INT(rb_ary_entry(channel_data, i + (channel_length * j)));

      // Get the hash containing channel info
      channel = rb_ary_entry(channels_info, j);
      switch (FIX2INT(rb_hash_aref(channel, rb_intern("id")))) {
        case -1: a = val; break;
        case 0:  r = val; break;
        case 1:  g = val; break;
        case 2:  b = val; break;
      }
    }

    rb_ary_push(rb_iv_get(self, "@pixel_data"), BUILD_PIXEL(r, g, b, a));
  }

  return Qnil;
}