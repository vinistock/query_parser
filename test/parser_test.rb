# frozen_string_literal: true

require "test_helper"

class ParserTest < Minitest::Test
  def setup
    @parser = RagelQueryParser::Parser.new
  end

  def test_initialize
    assert_kind_of RagelQueryParser::Parser, RagelQueryParser::Parser.new
  end

  def test_single_param_parse
    assert_equal({ param_1: "value_1" }, @parser.parse_query("param_1=value_1"))
  end

  def test_two_param_parse
    assert_equal(
      { param_1: "value_1", param_2: "value 2" },
      @parser.parse_query("param_1=value_1&param_2=value%202")
    )
  end

  def test_semicolon_separator
    assert_equal(
      { param_1: "value_1", param_2: "value 2" },
      @parser.parse_query("param_1=value_1;param_2=value%202")
    )
  end

  def test_array_parameters
    assert_equal(
      { countries: %w[BR US ES], languages: %w[PT EN ES] },
      @parser.parse_query("countries[]=BR,US,ES&languages[]=PT,EN,ES")
    )
  end

  def test_custom_unescaper
    assert_equal(
      { param_1: "value_1", param_2: "VALUE 2" },
      @parser.parse_query("param_1=value_1&param_2=value%202") { |s| s.upcase.gsub("%20", " ") }
    )
  end

  def test_combined_scenarios
    assert_equal(
      { country: "BR", language: "PT", tags: %w[webdev ruby rails] },
      @parser.parse_query("country=BR&language=PT&tags[]=webdev,ruby,rails")
    )
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
    assert_raises(ArgumentError) { @parser.parse_query("%a") }
    assert_raises(ArgumentError) { @parser.parse_query("x%a_") }
  end

  private

  def unescape(string)
    RagelQueryParser::Parser.unescape(string)
  end
end
