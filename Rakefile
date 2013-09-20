require "bundler/gem_tasks"
require "rake/extensiontask"

Rake::ExtensionTask.new('psd_native') do |ext|
  ext.lib_dir = File.join('lib', 'psd_native')
  ext.config_options = '--with-cflags="-std=c99"'
end
