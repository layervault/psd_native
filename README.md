# PSDNative

A gem that includes multiple mixins that speed up [PSD.rb](https://github.com/layervault/psd.rb) by delegating certain parts of the library to native C code. This library allows for PSD.rb to function as a pure Ruby library, while allowing for optional native code speed improvements. It overwrites specific methods within PSD.rb transparently, so you can use PSD.rb as you normally would.

Currently, PSDNative replaces these sections of PSD.rb with native code:

* RGB processing
* RLE decoding (disabled; needs optimization)

## Installation

Add this line to your application's Gemfile:

    gem 'psd_native'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install psd_native

## Usage

``` ruby
require 'psd_native'

psd = PSD.new("path/to/file.psd")
psd.parse!
```

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request
