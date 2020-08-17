# frozen_string_literal: true

require "ragel_query_parser/version"
require "ragel_query_parser/ragel_query_parser"

module RagelQueryParser # :nodoc:
  class << self
    # Override Rack's default query parser
    def override_rack
      Rack::Utils.default_query_parser = RagelQueryParser::Parser.new
    end
  end
end
