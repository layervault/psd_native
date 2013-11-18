require 'psd'
require 'psd_native/psd_native'

class PSD
  module Compose
    IMPLEMENTED = [
      :normal,
      :darken,
      :multiply,
      :color_burn,
      :linear_burn,
      :lighten,
      :screen
    ]

    IMPLEMENTED.each do |meth|
      define_method(meth) do |*args|
        do_blend meth, *args
      end
    end

    private

    def do_blend(blend, fg, bg, opts={})
      opts = DEFAULT_OPTS.merge(opts)
      PSDNative::Compose.send(blend, fg, bg, opts)
    end
  end
end