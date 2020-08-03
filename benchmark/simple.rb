# frozen_string_literal: true

require "bundler/inline"

gemfile(true) do
  source "https://rubygems.org"
  git_source(:github) { |repo| "https://github.com/#{repo}.git" }

  gem "benchmark-ips"
  gem "benchmark-memory", require: "benchmark/memory"
  gem "rack", github: "rack/rack"
  gem "ragel_query_parser", path: "../ragel_query_parser"
end

require "rack/query_parser"

query_string = "?" + (0..100).map { |i| "param#{i}=value#{i}" }.join("&")
ragel_parser = RagelQueryParser::Parser.new
rack_parser = Rack::QueryParser.make_default(65_536, 100)

Benchmark.ips do |x|
  x.report("ragel") { ragel_parser.parse(query_string) }
  x.report("rack") { rack_parser.parse_query(query_string) }
  x.compare!
end

Benchmark.memory do |x|
  x.report("ragel") { ragel_parser.parse(query_string) }
  x.report("rack") { rack_parser.parse_query(query_string) }
  x.compare!
end