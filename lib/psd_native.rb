require "psd"

module PSDNative
  def self.included(base)
    base::Image.send(:include, PSDNative::ImageMode::RGB)
    base::Image.send(:include, PSDNative::ImageMode::CMYK)
    base::Image.send(:include, PSDNative::ImageMode::Greyscale)
    base::Image.send(:include, PSDNative::ImageFormat::RLE)
  end
end

require "psd_native/version"
require "psd_native/psd_native"
require "psd_native/color"

PSD.send :include, PSDNative