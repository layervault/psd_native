#ifndef PSD_NATIVE_COLOR
#define PSD_NATIVE_COLOR

#define BUILD_PIXEL(r, g, b, a) (((PIXEL) (r) << 24) + ((PIXEL) (g) << 16) + ((PIXEL) (b) << 8) + (PIXEL) (a))
#define R(color) ((PIXEL) (color) & 0xff000000) >> 24
#define G(color) ((PIXEL) (color) & 0x00ff0000) >> 16
#define B(color) ((PIXEL) (color) & 0x0000ff00) >> 8
#define A(color) ((PIXEL) (color) & 0x000000ff)

VALUE psd_native_cmyk_to_rgb(VALUE self, VALUE c, VALUE m, VALUE y, VALUE k);
int psd_clamp_int(int n, int low, int high);
int opaque(uint32_t color);
int transparent(uint32_t color);

#endif