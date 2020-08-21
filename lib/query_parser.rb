# frozen_string_literal: true

require "query_parser/version"
require "query_parser/query_parser"

module QueryParser # :nodoc:
  class << self
    # Override Rack's default query parser
    def override_rack
      Rack::Utils.default_query_parser = QueryParser::Parser.new
    end
  end
end
