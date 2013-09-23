#ifndef PSD_NATIVE_EXT
#define PSD_NATIVE_EXT

#include "ruby.h"

#define RSTRING_NOT_MODIFIED

// Pixels use 32 bits unsigned integers
// We borrow this from OilyPNG
typedef uint32_t PIXEL;

// Our native mixins
#include "image_mode_rgb.h"
#include "rle_decoding.h"
#include "color.h"

void Init_psd_native();
VALUE psd_class();
void psd_logger(char* level, char* message);
VALUE psd_file(VALUE self);
int psd_file_tell(VALUE self);

#endif