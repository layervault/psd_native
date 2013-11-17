#ifndef PSD_NATIVE_COLOR
#define PSD_NATIVE_COLOR

VALUE psd_native_cmyk_to_rgb(VALUE self, VALUE c, VALUE m, VALUE y, VALUE k);
int psd_clamp_int(int n, int low, int high);
int opaque(uint32_t color);
int transparent(uint32_t color);
uint32_t r(uint32_t color);
uint32_t g(uint32_t color);
uint32_t b(uint32_t color);
uint32_t a(uint32_t color);
uint32_t rgba(uint32_t r, uint32_t g, uint32_t b, uint32_t a);

#endif