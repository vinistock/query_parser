# QueryParser

A fast and robust query string parser compatible with Rack's default query parser built with [Ragel].

Not yet ready for usage, but getting there.

## Installation

Add this line to your application's Gemfile:

```ruby
gem "query_parser"
```

And then execute:

    $ bundle install

Or install it yourself as:

    $ gem install query_parser

## Usage

For usage with frameworks based on Rack (such as Rails), simply override the default query parser.
```ruby
QueryParser.override_rack
```

It can also be used on its own to parse query strings.
```ruby
parser = QueryParser::Parser.make_default(65_536, 32)

parser.parse_query("my_query=string&with_many=cool_params")
=> #<QueryParser::Params:0x00007fb3cf0e80f0 @limit=65536, @size=17, @params={"my_query"=>"string", "with_many"=>"cool_params"}>
```

## Benchmarks

Coming soon.

## Contributing

After checking out the repo, run `bin/setup` to install dependencies. If you don't have [Ragel] installed, you can use the available Brewfile to install it or refer to the tool's homepage for instructions.

[Ragel]: https://github.com/adrian-thurston/ragel
