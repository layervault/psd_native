#include "psd_native_ext.h"

VALUE psd_native_decode_rle_channel(VALUE self) {
  int bytes, finish, len, val;

  int height = FIX2INT(rb_funcall(self, rb_intern("height"), 0));
  VALUE* channel_data = RARRAY_PTR(rb_iv_get(self, "@channel_data"));
  VALUE* byte_counts = RARRAY_PTR(rb_iv_get(self, "@byte_counts"));
  int line_index = FIX2INT(rb_iv_get(self, "@line_index"));
  int chan_pos = FIX2INT(rb_iv_get(self, "@chan_pos"));

  for (int i = 0; i < height; i++) {
    bytes = FIX2INT(byte_counts[line_index + i]);
    finish = psd_file_tell(self) + bytes;

    for (int j = 0; j < bytes;) {
      len = FIX2INT(psd_file_read_byte(self));
      j++;

      if (len < 128) {
        len++;
        for (int j = chan_pos; j < chan_pos + len; j++) {
          channel_data[j] = psd_file_read_byte(self);
        }

        chan_pos += len;
        j += len;
      } else if (len > 128) {
        len ^= 0xff;
        len += 2;

        val = psd_file_read_byte(self);
        for (int j = chan_pos; j < chan_pos + len; j++) {
          channel_data[j] = val;
        }

        chan_pos += len;
        j++;
      }
    }

    rb_iv_set(self, "@chan_pos", INT2FIX(chan_pos));
  }

  return Qnil;
}

VALUE psd_file_read_byte(VALUE self) {
  VALUE data = rb_funcall(psd_file(self), rb_intern("read"), 1, INT2FIX(1));
  VALUE bytes = rb_funcall(data, rb_intern("bytes"), 0);
  return rb_ary_entry(rb_funcall(bytes, rb_intern("to_a"), 0), 0);
}