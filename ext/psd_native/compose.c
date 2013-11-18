#include "psd_native_ext.h"

AlphaValues alpha;

VALUE psd_native_compose_normal(VALUE self, VALUE r_fg, VALUE r_bg, VALUE opts) {
  PIXEL fg = FIX2UINT(r_fg);
  PIXEL bg = FIX2UINT(r_bg);
  PIXEL new_r, new_g, new_b;

  if (OPAQUE(fg) || TRANSPARENT(bg)) return r_fg;
  if (TRANSPARENT(fg)) return r_bg;

  calculate_alphas(fg, bg, &opts);

  new_r = BLEND_CHANNEL(R(bg), R(fg), alpha.mix);
  new_g = BLEND_CHANNEL(G(bg), G(fg), alpha.mix);
  new_b = BLEND_CHANNEL(B(bg), B(fg), alpha.mix);

  return INT2FIX(BUILD_PIXEL(new_r, new_g, new_b, alpha.dst));
}

VALUE psd_native_compose_darken(VALUE self, VALUE r_fg, VALUE r_bg, VALUE opts) {
  PIXEL fg = FIX2UINT(r_fg);
  PIXEL bg = FIX2UINT(r_bg);
  PIXEL new_r, new_g, new_b;

  if (TRANSPARENT(bg)) return r_fg;
  if (TRANSPARENT(fg)) return r_bg;

  calculate_alphas(fg, bg, &opts);

  new_r = R(fg) <= R(bg) ? BLEND_CHANNEL(R(bg), R(fg), alpha.mix) : R(bg);
  new_g = G(fg) <= G(bg) ? BLEND_CHANNEL(G(bg), G(fg), alpha.mix) : G(bg);
  new_b = B(fg) <= B(bg) ? BLEND_CHANNEL(B(bg), B(fg), alpha.mix) : B(bg);

  return INT2FIX(BUILD_PIXEL(new_r, new_g, new_b, alpha.dst));
}

VALUE psd_native_compose_multiply(VALUE self, VALUE r_fg, VALUE r_bg, VALUE opts) {
  PIXEL fg = FIX2UINT(r_fg);
  PIXEL bg = FIX2UINT(r_bg);
  PIXEL new_r, new_g, new_b;

  if (TRANSPARENT(bg)) return r_fg;
  if (TRANSPARENT(fg)) return r_bg;

  calculate_alphas(fg, bg, &opts);

  new_r = BLEND_CHANNEL(R(bg), R(fg) * R(bg) >> 8, alpha.mix);
  new_g = BLEND_CHANNEL(G(bg), G(fg) * G(bg) >> 8, alpha.mix);
  new_b = BLEND_CHANNEL(B(bg), B(fg) * B(bg) >> 8, alpha.mix);

  return INT2FIX(BUILD_PIXEL(new_r, new_g, new_b, alpha.dst));
}

VALUE psd_native_compose_color_burn(VALUE self, VALUE r_fg, VALUE r_bg, VALUE opts) {
  PIXEL fg = FIX2UINT(r_fg);
  PIXEL bg = FIX2UINT(r_bg);
  PIXEL new_r, new_g, new_b;

  if (TRANSPARENT(bg)) return r_fg;
  if (TRANSPARENT(fg)) return r_bg;

  calculate_alphas(fg, bg, &opts);

  new_r = BLEND_CHANNEL(R(bg), color_burn_foreground(R(bg), R(fg)), alpha.mix);
  new_g = BLEND_CHANNEL(G(bg), color_burn_foreground(G(bg), G(fg)), alpha.mix);
  new_b = BLEND_CHANNEL(B(bg), color_burn_foreground(B(bg), B(fg)), alpha.mix);

  return INT2FIX(BUILD_PIXEL(new_r, new_g, new_b, alpha.dst));
}

PIXEL color_burn_foreground(PIXEL b, PIXEL f) {
  if (f > 0) {
    f = ((255 - b) << 8) / f;
    return f > 255 ? 0 : (255 - f);
  } else {
    return b;
  }
}

VALUE psd_native_compose_linear_burn(VALUE self, VALUE r_fg, VALUE r_bg, VALUE opts) {
  PIXEL fg = FIX2UINT(r_fg);
  PIXEL bg = FIX2UINT(r_bg);
  PIXEL new_r, new_g, new_b;

  if (TRANSPARENT(bg)) return r_fg;
  if (TRANSPARENT(fg)) return r_bg;

  calculate_alphas(fg, bg, &opts);

  new_r = BLEND_CHANNEL(R(bg), (R(fg) < (255 - R(bg))) ? 0 : R(fg) - (255 - R(bg)), alpha.mix);
  new_g = BLEND_CHANNEL(G(bg), (G(fg) < (255 - G(bg))) ? 0 : G(fg) - (255 - G(bg)), alpha.mix);
  new_b = BLEND_CHANNEL(B(bg), (B(fg) < (255 - B(bg))) ? 0 : B(fg) - (255 - B(bg)), alpha.mix);

  return INT2FIX(BUILD_PIXEL(new_r, new_g, new_b, alpha.dst));
}

VALUE psd_native_compose_lighten(VALUE self, VALUE r_fg, VALUE r_bg, VALUE opts) {
  PIXEL fg = FIX2UINT(r_fg);
  PIXEL bg = FIX2UINT(r_bg);
  PIXEL new_r, new_g, new_b;

  if (TRANSPARENT(bg)) return r_fg;
  if (TRANSPARENT(fg)) return r_bg;

  calculate_alphas(fg, bg, &opts);

  new_r = (R(fg) >= R(bg)) ? BLEND_CHANNEL(R(bg), R(fg), alpha.mix) : R(bg);
  new_g = (G(fg) >= G(bg)) ? BLEND_CHANNEL(G(bg), G(fg), alpha.mix) : G(bg);
  new_b = (B(fg) >= B(bg)) ? BLEND_CHANNEL(B(bg), B(fg), alpha.mix) : B(bg);

  return INT2FIX(BUILD_PIXEL(new_r, new_g, new_b, alpha.dst));
}

VALUE psd_native_compose_screen(VALUE self, VALUE r_fg, VALUE r_bg, VALUE opts) {
  PIXEL fg = FIX2UINT(r_fg);
  PIXEL bg = FIX2UINT(r_bg);
  PIXEL new_r, new_g, new_b;

  if (TRANSPARENT(bg)) return r_fg;
  if (TRANSPARENT(fg)) return r_bg;

  calculate_alphas(fg, bg, &opts);

  new_r = BLEND_CHANNEL(R(bg), 255 - ((255 - R(bg)) * (255 - R(fg)) >> 8), alpha.mix);
  new_g = BLEND_CHANNEL(G(bg), 255 - ((255 - G(bg)) * (255 - G(fg)) >> 8), alpha.mix);
  new_b = BLEND_CHANNEL(B(bg), 255 - ((255 - B(bg)) * (255 - B(fg)) >> 8), alpha.mix);

  return INT2FIX(BUILD_PIXEL(new_r, new_g, new_b, alpha.dst));
}

VALUE psd_native_compose_color_dodge(VALUE self, VALUE r_fg, VALUE r_bg, VALUE opts) {
  PIXEL fg = FIX2UINT(r_fg);
  PIXEL bg = FIX2UINT(r_bg);
  PIXEL new_r, new_g, new_b;

  if (TRANSPARENT(bg)) return r_fg;
  if (TRANSPARENT(fg)) return r_bg;

  calculate_alphas(fg, bg, &opts);

  new_r = BLEND_CHANNEL(R(bg), color_dodge_foreground(R(bg), R(fg)), alpha.mix);
  new_g = BLEND_CHANNEL(G(bg), color_dodge_foreground(G(bg), G(fg)), alpha.mix);
  new_b = BLEND_CHANNEL(B(bg), color_dodge_foreground(B(bg), B(fg)), alpha.mix);

  return INT2FIX(BUILD_PIXEL(new_r, new_g, new_b, alpha.dst));
}

PIXEL color_dodge_foreground(PIXEL b, PIXEL f) {
  if (f < 255) {
    return CLAMP_PIXEL((b << 8) / (255 - f));
  } else {
    return b;
  }
}

VALUE psd_native_compose_linear_dodge(VALUE self, VALUE r_fg, VALUE r_bg, VALUE opts) {
  PIXEL fg = FIX2UINT(r_fg);
  PIXEL bg = FIX2UINT(r_bg);
  PIXEL new_r, new_g, new_b;

  if (TRANSPARENT(bg)) return r_fg;
  if (TRANSPARENT(fg)) return r_bg;

  calculate_alphas(fg, bg, &opts);

  new_r = BLEND_CHANNEL(R(bg), (R(bg) + R(fg)) > 255 ? 255 : R(bg) + R(fg), alpha.mix);
  new_g = BLEND_CHANNEL(G(bg), (G(bg) + G(fg)) > 255 ? 255 : G(bg) + G(fg), alpha.mix);
  new_b = BLEND_CHANNEL(B(bg), (B(bg) + B(fg)) > 255 ? 255 : B(bg) + B(fg), alpha.mix);

  return INT2FIX(BUILD_PIXEL(new_r, new_g, new_b, alpha.dst));
}

void calculate_alphas(PIXEL fg, PIXEL bg, VALUE *opts) {
  uint32_t opacity = calculate_opacity(opts);
  uint32_t src_alpha = A(fg) * opacity >> 8;

  alpha.dst = A(bg);
  alpha.mix = (src_alpha << 8) / (src_alpha + ((256 - src_alpha) * alpha.dst >> 8));
  alpha.dst = alpha.dst + ((256 - alpha.dst) * src_alpha >> 8);
}

uint32_t calculate_opacity(VALUE *opts) {
  uint32_t opacity = FIX2UINT(rb_hash_aref(*opts, ID2SYM(rb_intern("opacity"))));
  uint32_t fill_opacity = FIX2UINT(rb_hash_aref(*opts, ID2SYM(rb_intern("fill_opacity"))));

  return opacity * fill_opacity / 255;
}