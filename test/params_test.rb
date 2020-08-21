# frozen_string_literal: true

require "test_helper"

class ParamsTest < Minitest::Test
  def setup
    @params = QueryParser::Params.new(10)
  end

  def test_accessors
    @params["key"] = "value"

    assert_equal "value", @params["key"]
  end

  def test_key
    @params["key"] = "value"

    assert 3, @params.instance_variable_get(:@size)
    assert @params.key?("key")
  end

  def test_exceeding_limit
    @params["key"] = "value"

    assert_raises(RangeError, "exceeded available parameter key space") do
      @params["huge_key_that_will_definitely_exceed_size"] = "value"
    end
  end

  def test_to_h
    params = QueryParser::Params.new(256)
    inner_params = QueryParser::Params.new(256)
    inner_params["some_key"] = "some_value"

    params["key"] = "value"
    params["itself"] = params
    params["array"] = [inner_params, "something_else"]

    expected = "{\"key\"=>\"value\", \"itself\"=>{...}, \"array\"=>[{\"some_key\"=>\"some_value\"}, \"something_else\"]}"
    assert_equal expected, params.to_h.to_s
  end
end
