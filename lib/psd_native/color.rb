require 'psd'
require 'psd_native/psd_native'

class PSD
  class Color
    instance_eval do
      alias :old_cmyk_to_rgb :cmyk_to_rgb
      def cmyk_to_rgb(*args)
        PSDNative::Color.cmyk_to_rgb(*args)
      end
    end
  end
end