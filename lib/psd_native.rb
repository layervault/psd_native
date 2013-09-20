require "psd"
require "psd_native/version"
require "psd_native/psd_native"

module PSDNative
  def self.included(base)
    base::Image.send(:include, PSDNative::ImageMode::RGB)
  end
end

PSD.send :include, PSDNative