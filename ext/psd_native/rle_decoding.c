#include "psd_native_ext.h"

VALUE psd_native_decode_rle_channel(VALUE self) {
  int bytes, len, val;
  int i, j, k;

  int height = FIX2INT(rb_funcall(self, rb_intern("height"), 0));
  VALUE channel_data = rb_iv_get(self, "@channel_data");
  VALUE* byte_counts = RARRAY_PTR(rb_iv_get(self, "@byte_counts"));
  int line_index = FIX2INT(rb_iv_get(self, "@line_index"));
  int chan_pos = FIX2INT(rb_iv_get(self, "@chan_pos"));

  for (i = 0; i < height; i++) {
    bytes = FIX2INT(byte_counts[line_index + i]);

    for (j = 0; j < bytes;) {
      len = FIX2INT(psd_file_read_byte(self));
      j++;

      if (len < 128) {
        len++;
        for (k = chan_pos; k < chan_pos + len; k++) {
          rb_ary_store(channel_data, k, psd_file_read_byte(self));
        }

        chan_pos += len;
        j += len;
      } else if (len > 128) {
        len ^= 0xff;
        len += 2;

        val = psd_file_read_byte(self);
        for (k = chan_pos; k < chan_pos + len; k++) {
          rb_ary_store(channel_data, k, val);
        }

        chan_pos += len;
        j++;
      }
    }
  }

  rb_iv_set(self, "@chan_pos", INT2FIX(chan_pos));
  return Qnil;
}

VALUE psd_file_read_byte(VALUE self) {
  // @file.read(1).bytes[0]
  VALUE data = rb_funcall(psd_file(self), rb_intern("read"), 1, INT2FIX(1));
  return RARRAY_PTR(rb_funcall(data, rb_intern("bytes"), 0))[0];
}