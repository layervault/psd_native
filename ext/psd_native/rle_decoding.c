#include "psd_native_ext.h"

VALUE psd_native_decode_rle_channel(VALUE self) {
  int height = FIX2INT(rb_funcall(self, rb_intern("height"), 0));
  VALUE channel_data = rb_iv_get(self, "@channel_data");
  int bytes, finish, len, val;

  for (int i = 0; i < height; i++) {
    bytes = psd_byte_count(self, i);
    finish = psd_file_tell(self) + bytes;

    while (psd_file_tell(self) < finish) {
      len = FIX2INT(psd_file_read_byte(self));

      if (len < 128) {
        len++;
        for (int j = psd_chan_pos(self); j < psd_chan_pos(self) + len; j++) {
          rb_ary_store(channel_data, j, psd_file_read_byte(self));
        }

        rb_iv_set(self, "@chan_pos", INT2FIX(psd_chan_pos(self) + len));
      } else if (len > 128) {
        len ^= 0xff;
        len += 2;

        val = psd_file_read_byte(self);
        for (int j = psd_chan_pos(self); j < psd_chan_pos(self) + len; j++) {
          rb_ary_store(channel_data, j, val);
        }

        rb_iv_set(self, "@chan_pos", INT2FIX(psd_chan_pos(self) + len));
      }
    }
  }

  return Qnil;
}

int psd_byte_count(VALUE self, int line) {
  return FIX2INT(
    rb_ary_entry(
      rb_iv_get(self, "@byte_counts"), 
      FIX2INT(rb_iv_get(self, "@line_index")) + line
    )
  );
}

VALUE psd_file_read_byte(VALUE self) {
  VALUE data = rb_funcall(psd_file(self), rb_intern("read"), 1, INT2FIX(1));
  VALUE bytes = rb_funcall(data, rb_intern("bytes"), 0);
  return rb_ary_entry(rb_funcall(bytes, rb_intern("to_a"), 0), 0);
}

int psd_chan_pos(VALUE self) {
  return FIX2INT(rb_iv_get(self, "@chan_pos"));
}