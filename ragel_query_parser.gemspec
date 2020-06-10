# frozen_string_literal: true

require_relative "lib/ragel_query_parser/version"

Gem::Specification.new do |spec|
  spec.name          = "ragel_query_parser"
  spec.version       = RagelQueryParser::VERSION
  spec.authors       = ["Vinicius Stock"]
  spec.email         = ["vinicius.stock@outlook.com"]

  spec.summary       = "A query parser made with Ragel."
  spec.description   = "A query parser made with Ragel."
  spec.homepage      = "https://github.com/vinistock/ragel_query_parser"
  spec.license       = "MIT"
  spec.required_ruby_version = Gem::Requirement.new(">= 2.3.0")

  spec.metadata["homepage_uri"] = spec.homepage
  spec.metadata["source_code_uri"] = "https://github.com/vinistock/ragel_query_parser"
  spec.metadata["changelog_uri"] = "https://github.com/vinistock/ragel_query_parser/blob/master/CHANGELOG.md"

  spec.files = Dir.chdir(File.expand_path(__dir__)) do
    `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  end
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]
  spec.extensions    = ["ext/ragel_query_parser/extconf.rb"]

  spec.add_development_dependency "byebug"
  spec.add_development_dependency "minitest"
  spec.add_development_dependency "purdytest"
  spec.add_development_dependency "rake"
  spec.add_development_dependency "rake-compiler"
  spec.add_development_dependency "rubocop"
  spec.add_development_dependency "rubocop-minitest"
  spec.add_development_dependency "rubocop-performance"
end
