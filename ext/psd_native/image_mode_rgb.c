#include "psd_native_ext.h"

VALUE psd_native_combine_rgb_channel(VALUE self) {
  printf("PROCESSING RGB\n");

  uint32_t num_pixels = FIX2UINT(rb_iv_get(self, "@num_pixels"));
  uint32_t pixel_step = FIX2UINT(rb_funcall(self, rb_intern("pixel_step"), 0));

  // printf("PIXELS = %d, STEP = %d\n", num_pixels, pixel_step);

  VALUE channels_info = rb_iv_get(self, "@channels_info");
  VALUE channel_data = rb_iv_get(self, "@channel_data");
  uint32_t channel_length = FIX2UINT(rb_iv_get(self, "@channel_length"));

  // printf("CHANNELS = %d\n", channel_length);
  
  VALUE channel;

  int i, j, r, g, b, a;
  uint32_t val;

  // Loop through every pixel in the image
  for (i = 0; i < num_pixels; i += pixel_step) {
    r = g = b = 0;
    a = 255;

    // printf("%d\n", i);

    // And every channel for every pixel
    for (j = 0; j < channel_length; j++) {
      val = FIX2UINT(rb_ary_entry(channel_data, i + (channel_length * j)));
      // printf("%d\n", val);

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