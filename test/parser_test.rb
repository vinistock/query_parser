# frozen_string_literal: true

require "test_helper"

class ParserTest < Minitest::Test
  def test_initialize
    assert_kind_of RagelQueryParser::Parser, RagelQueryParser::Parser.new
  end

  def test_parse
    parser = RagelQueryParser::Parser.new
    parser.parse("?name=value")

    assert_equal "value", parser.parameters[:name]
  end
end
