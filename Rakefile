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

  %W[#{ext_path}/parse_query.rl #{ext_path}/parse_nested.rl].each do |ragel_file|
    compiled_path = ragel_file.gsub(".rl", ".c")
    system("ragel #{ragel_file} -C -G2 -I ext/query_parser -o #{compiled_path}")
  end

  abort unless $?.success? # rubocop:disable Style/SpecialGlobalVars
end

task make: %i[clobber ragel compile]
task build: %i[compile]

Rake::ExtensionTask.new("query_parser") do |ext|
  ext.lib_dir = "lib/query_parser"
end

task default: %i[clobber ragel compile test]
task ci: %i[compile test]
