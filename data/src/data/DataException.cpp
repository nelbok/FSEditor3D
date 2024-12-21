#include <fsd/data/DataException.hpp>

#include <string>

namespace fsd {

std::string convert(DataException::Error error) {
	switch (error) {
		case DataException::Error::ModelTypeError:
			return "Incorrect attempt to modify model type";
		case DataException::Error::ShapeModelError:
			return "Incorrect attempt to assign a model";
		default:
			return "Unknown error";
	}
}

DataException::DataException(DataException::Error error)
	: std::runtime_error(convert(error)) {}

} // namespace fsd
