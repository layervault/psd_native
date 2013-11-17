require 'psd'
require 'psd_native/psd_native'

class PSD
  module Compose
    def normal(fg, bg, opts={})
      opts = DEFAULT_OPTS.merge(opts)
      PSDNative::Compose.normal(fg, bg, opts)
    end

    def darken(fg, bg, opts={})
      opts = DEFAULT_OPTS.merge(opts)
      PSDNative::Compose.darken(fg, bg, opts)
    end
  end
end