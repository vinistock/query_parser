# frozen_string_literal: true

require "test_helper"

class ParserTest < Minitest::Test
  def test_initialize
    assert_kind_of RagelQueryParser::Parser, RagelQueryParser::Parser.new
  end

  def test_single_param_parse
    parser = RagelQueryParser::Parser.new
    parser.parse("param_1=value_1")

    assert_equal "value_1", parser.parameters[:param_1]
  end

  def test_two_param_parse
    parser = RagelQueryParser::Parser.new
    parser.parse("param_1=value_1&param_2=value%202")

    assert_equal "value_1", parser.parameters[:param_1]
    assert_equal "value 2", parser.parameters[:param_2]
  end

  def test_semicolon_separator
    parser = RagelQueryParser::Parser.new
    parser.parse("param_1=value_1;param_2=value%202")

    assert_equal "value_1", parser.parameters[:param_1]
    assert_equal "value 2", parser.parameters[:param_2]
  end

  def test_custom_unescaper
    parser = RagelQueryParser::Parser.new
    parser.parse("param_1=value_1&param_2=value%202") { |s| s.upcase.gsub("%20", " ") }

    assert_equal "value_1", parser.parameters[:param_1]
    assert_equal "VALUE 2", parser.parameters[:param_2]
  end

  def test_unescape_ruby_spec
    assert_equal(
      "  !\"\#$%&'()*+,-./09:;<=>?@AZ[\\]^_`az{|}~",
      unescape("%20+%21%22%23%24%25%26%27%28%29*%2B%2C-.%2F09%3A%3B%3C%3D%3E%3F%40AZ%5B%5C%5D%5E_%60az%7B%7C%7D%7E")
    )

    assert_equal(
      (+"\xE3\x81\x82\xE3\x81\x82").force_encoding("UTF-8"),
      unescape((+"\xE3\x81\x82%E3%81%82").force_encoding("UTF-8"))
    )
  end

  def test_invalid_encoded_content
    parser = RagelQueryParser::Parser.new

    assert_raises(ArgumentError) { parser.parse("%a") }
    assert_raises(ArgumentError) { parser.parse("x%a_") }
  end

  private

  def unescape(string)
    RagelQueryParser::Parser.unescape(string)
  end
end
