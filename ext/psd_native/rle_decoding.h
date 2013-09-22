#ifndef PSD_NATIVE_RLE_DECODING
#define PSD_NATIVE_RLE_DECODING

VALUE psd_native_decode_rle_channel(VALUE self);
int psd_byte_count(VALUE self, int line);
VALUE psd_file_read_byte(VALUE self);
int psd_chan_pos(VALUE self);

#endif