# frozen_string_literal: true

require "bundler/inline"

gemfile(true) do
  source "https://rubygems.org"
  git_source(:github) { |repo| "https://github.com/#{repo}.git" }

  gem "benchmark-ips"
  gem "benchmark-memory", require: "benchmark/memory"
  gem "rack", github: "rack/rack"
  gem "query_parser", path: "../query_parser"
end

require "rack/query_parser"

query_string = (0..1000).map { |i| i % 5 ? "param#{i}=value%20#{i}" : "param#{i}=value_#{i}" }.join("&")
ragel_parser = QueryParser::Parser.make_default(65_536, 32)
rack_parser = Rack::QueryParser.make_default(65_536, 32)

Benchmark.ips do |x|
  x.report("ragel") { ragel_parser.parse_query(query_string) }
  x.report("rack") { rack_parser.parse_query(query_string) }
  x.compare!
end

Benchmark.memory do |x|
  x.report("ragel") { ragel_parser.parse_query(query_string) }
  x.report("rack") { rack_parser.parse_query(query_string) }
  x.compare!
end
