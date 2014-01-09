#include "psd_native_ext.h"

VALUE psd_native_initialize_canvas(VALUE self) {
  psd_logger("debug", "Initializing canvas with native code");
  
  VALUE canvas = rb_iv_get(self, "@canvas");
  VALUE* pixel_data = RARRAY_PTR(rb_iv_get(self, "@pixel_data"));
  uint32_t width = FIX2UINT(rb_funcall(self, rb_intern("width"), 0));
  uint32_t height = FIX2UINT(rb_funcall(self, rb_intern("height"), 0));
  int x, y;

  int i = 0;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      rb_funcall(
        canvas, 
        rb_intern("[]="), 
        3, 
        INT2FIX(x), INT2FIX(y), pixel_data[i]
      );
      
      i++;
    }
  }

  rb_iv_set(self, "@pixel_data", Qnil);

  return Qnil;
}