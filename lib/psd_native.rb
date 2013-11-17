require "psd"

module PSDNative
  def self.included(base)
    base::Image.send(:include, PSDNative::ImageMode::RGB)
    base::Image.send(:include, PSDNative::ImageMode::CMYK)
    base::Image.send(:include, PSDNative::ImageMode::Greyscale)
    base::Image.send(:include, PSDNative::ImageFormat::RLE)
    base::Color.send(:include, PSDNative::Color)

    base::ClippingMask.class_eval do
      remove_method :apply
    end
    base::ClippingMask.send(:include, PSDNative::ClippingMask)
  end
end

require "psd_native/version"
require "psd_native/psd_native"
require "psd_native/compose"

PSD.send :include, PSDNative