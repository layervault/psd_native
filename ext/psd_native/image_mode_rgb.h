#ifndef PSD_NATIVE_RGB
#define PSD_NATIVE_RGB

#define BUILD_PIXEL(r, g, b, a)  (((PIXEL) (r) << 24) + ((PIXEL) (g) << 16) + ((PIXEL) (b) << 8) + (PIXEL) (a))

VALUE psd_native_combine_rgb_channel(VALUE self);

#endif