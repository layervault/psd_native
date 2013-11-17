#ifndef PSD_NATIVE_COMPOSE
#define PSD_NATIVE_COMPOSE

typedef struct AlphaValues {
  int mix;
  int dst;
} AlphaValues;

VALUE psd_native_compose_normal(VALUE self, VALUE fg, VALUE bg, VALUE opts);
void calculate_alphas(uint32_t fg, uint32_t bg, VALUE opts);
uint32_t calculate_opacity(VALUE opts);
uint32_t blend_channel(uint32_t bg, uint32_t fg, uint32_t a);

#endif