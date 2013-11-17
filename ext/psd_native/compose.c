#include "psd_native_ext.h"

AlphaValues alpha;

VALUE psd_native_compose_normal(VALUE self, VALUE r_fg, VALUE r_bg, VALUE opts) {
  uint32_t fg = FIX2UINT(r_fg);
  uint32_t bg = FIX2UINT(r_bg);
  uint32_t new_r, new_g, new_b;

  if (opaque(fg) || transparent(bg)) return INT2FIX(fg);
  if (transparent(fg)) return INT2FIX(bg);

  calculate_alphas(fg, bg, &opts);

  new_r = blend_channel(r(bg), r(fg), alpha.mix);
  new_g = blend_channel(g(bg), g(fg), alpha.mix);
  new_b = blend_channel(b(bg), b(fg), alpha.mix);

  return INT2FIX(rgba(new_r, new_g, new_b, alpha.dst));
}

void calculate_alphas(uint32_t fg, uint32_t bg, VALUE *opts) {
  uint32_t opacity = calculate_opacity(opts);
  uint32_t src_alpha = a(fg) * opacity >> 8;

  alpha.dst = a(bg);
  alpha.mix = (src_alpha << 8) / (src_alpha + ((256 - src_alpha) * alpha.dst >> 8));
  alpha.dst = alpha.dst + ((256 - alpha.dst) * src_alpha >> 8);
}

uint32_t calculate_opacity(VALUE *opts) {
  uint32_t opacity = FIX2UINT(rb_hash_aref(*opts, ID2SYM(rb_intern("opacity"))));
  uint32_t fill_opacity = FIX2UINT(rb_hash_aref(*opts, ID2SYM(rb_intern("fill_opacity"))));

  return opacity * fill_opacity / 255;
}

uint32_t blend_channel(uint32_t bg, uint32_t fg, uint32_t a) {
  return ((bg << 8) + (fg - bg) * a) >> 8;
}