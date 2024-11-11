#include <fsd/io/JsonException.hpp>

#include <string>

namespace fsd {

std::string convert(JsonException::Error error) {
	switch (error) {
		case JsonException::Error::UnknownKey:
			return "Unknown JSON key";
		case JsonException::Error::InvalidDocument:
			return "Invalid JSON document";
		case JsonException::Error::InvalidObject:
			return "The value isn't a valid object";
		case JsonException::Error::InvalidArray:
			return "The value isn't a valid array";
		case JsonException::Error::InvalidString:
			return "The value isn't a valid string";
		case JsonException::Error::InvalidInteger:
			return "The value isn't a valid integer";
		case JsonException::Error::InvalidDouble:
			return "The value isn't a valid double";
		case JsonException::Error::InvalidBoolean:
			return "The value isn't a valid boolean";
		case JsonException::Error::InvalidUrl:
			return "The value isn't a valid url";
		case JsonException::Error::InvalidUuid:
			return "The value isn't a valid uuid";
		case JsonException::Error::InvalidColor:
			return "The value isn't a valid color";
		default:
			return "Unknown error";
	}
}

JsonException::JsonException(JsonException::Error error)
	: std::runtime_error(convert(error)) {}

} // namespace fsd
