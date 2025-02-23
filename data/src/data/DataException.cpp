#include <fsd/data/DataException.hpp>

namespace fsd {

QString convert(DataException::Error error) {
	switch (error) {
		case DataException::Error::ModelTypeError:
			return "Incorrect attempt to modify model type";
		case DataException::Error::ShapeModelError:
			return "Incorrect attempt to assign a model";
		default:
			return "Unknown error";
	}
}

DataException::DataException(const QString& objectName, DataException::Error error)
	: std::runtime_error((objectName + ": " + convert(error)).toStdString()) {}

} // namespace fsd
