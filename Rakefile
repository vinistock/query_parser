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
  ext_path = "ext/query_parser"
  puts "Compiling Ragel..."
  system("ragel #{ext_path}/parse_query.rl -C -G2 -I ext/query_parser -o #{ext_path}/parse_query.c")
  abort unless $?.success? # rubocop:disable Style/SpecialGlobalVars
end

task make: %i[clobber ragel compile]
task build: %i[compile]

Rake::ExtensionTask.new("query_parser") do |ext|
  ext.lib_dir = "lib/query_parser"
end

task default: %i[clobber ragel compile test]
task ci: %i[compile test]
