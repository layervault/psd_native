#ifndef PSD_NATIVE_COLOR
#define PSD_NATIVE_COLOR

VALUE psd_native_cmyk_to_rgb(VALUE self, VALUE c, VALUE m, VALUE y, VALUE k);
int psd_clamp_int(int n, int low, int high);

#endif