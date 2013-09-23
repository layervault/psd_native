require "psd"
require "psd_native/version"
require "psd_native/psd_native"

module PSDNative
  def self.included(base)
    base::Image.send(:include, PSDNative::ImageMode::RGB)
    base::Image.send(:include, PSDNative::ImageFormat::RLE)
  end
end

PSD.send :include, PSDNative