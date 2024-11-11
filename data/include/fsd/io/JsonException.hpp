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

class FSDATA_EXPORT JsonException : public std::runtime_error {
public:
	enum class Error {
		UnknownKey,
		InvalidDocument,
		InvalidObject,
		InvalidArray,
		InvalidString,
		InvalidInteger,
		InvalidDouble,
		InvalidBoolean,
		InvalidUrl,
		InvalidUuid,
		InvalidColor,
	};

	explicit JsonException(JsonException::Error error);
	~JsonException() override = default;
};

} // namespace fsd
