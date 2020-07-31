# frozen_string_literal: true

require "bundler/gem_tasks"
require "rake/testtask"

Rake::TestTask.new(:test) do |t|
  t.libs << "test"
  t.libs << "lib"
  t.test_files = FileList["test/**/*_test.rb"]
end

require "rake/extensiontask"

task :ragel do
  ext_path = "ext/ragel_query_parser"
  puts "Compiling Ragel..."
  system("ragel #{ext_path}/parser.rl -C -G2 -I ext/ragel_query_parser -o #{ext_path}/parser.c")
end

task make: %i[clobber ragel compile]
task build: %i[compile]

Rake::ExtensionTask.new("ragel_query_parser") do |ext|
  ext.lib_dir = "lib/ragel_query_parser"
end

task default: %i[clobber ragel compile test]
