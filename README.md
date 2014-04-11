# PSDNative

[![Travis CI](https://travis-ci.org/layervault/psd_native.png)](https://travis-ci.org/layervault/psd_native)

PSD Native is a native extension to PSD.rb that includes speed enhancements finely tuned for production environments. PSD Native introduces no new features to PSD.rb, only speed improvements via native C code. For most larger files, you will see speed increases of 50x or more.

The code in this repository is no longer updated, but is still available under the MIT license. If you are interested in licensing PSD Native for a monthly fee in order to access future updates, [please contact us](mailto:sales@layervault.com).

## Installation

Add this line to your application's Gemfile:

    gem 'psd_native'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install psd_native

## Usage

Simply require `psd_native` instead of `psd`, and you're good to go.

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
