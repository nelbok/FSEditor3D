/*
 * Copyright (c) 2024 Foxxy Soft.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution
 */

#pragma once

#include <fsd/data/FSDataExport.h>

#include <stdexcept>

namespace fsd {

class FSDATA_EXPORT DataException : public std::runtime_error {
public:
	enum class Error {
		ModelTypeError,
		ShapeModelError,
	};

	explicit DataException(DataException::Error error);
	~DataException() override = default;
};

} // namespace fsd
