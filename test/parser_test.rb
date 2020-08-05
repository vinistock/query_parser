# frozen_string_literal: true

require "test_helper"

class ParserTest < Minitest::Test
  def test_initialize
    assert_kind_of RagelQueryParser::Parser, RagelQueryParser::Parser.new
  end

  def test_simple_parse
    parser = RagelQueryParser::Parser.new
    parser.parse("?param_1=value_1&param_2=value%202")

    assert_equal "value_1", parser.parameters[:param_1]
    assert_equal "value 2", parser.parameters[:param_2]
  end

  def test_custom_unescaper
    parser = RagelQueryParser::Parser.new
    parser.parse("?param_1=value_1&param_2=value%202") { |s| s.upcase.gsub("%20", " ") }

    assert_equal "value_1", parser.parameters[:param_1]
    assert_equal "VALUE 2", parser.parameters[:param_2]
  end
end
