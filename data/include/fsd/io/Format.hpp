/*
 * Copyright (c) 2024 Foxxy Soft.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution
 */

#pragma once

namespace fsd {

/**
 * @brief All the keys used to write or read the Json file.
 */
namespace Format {
/** @name Entity keys
 * @sa Entity
 * @{
 */
constexpr auto lUuid = "uuid";
constexpr auto lName = "name";
/** @} */

/** @name Geometry keys
 * @sa Geometry
 * @{
 */
constexpr auto lPosition = "position";
constexpr auto lRotation = "rotation";
constexpr auto lScale = "scale";
/** @} */

/** @name Link keys
 * @sa Link
 * @{
 */
constexpr auto lLink = "link";
/** @} */

/** @name Model keys
 * @sa Model
 * @{
 */
constexpr auto lSourcePath = "sourcePath";
constexpr auto lQmlName = "qmlName";
constexpr auto lModelType = "modelType";
/** @} */

/** @name Placement keys
 * @sa Placement
 * @{
 */
constexpr auto lPlace = "place";
/** @} */

/** @name Project keys
 * @sa Project
 * @{
 */
constexpr auto lDefaultPlaces = "defaultPlace";
constexpr auto lEntryPoints = "entryPoints";
constexpr auto lLinks = "links";
constexpr auto lModels = "models";
constexpr auto lObjects = "objects";
constexpr auto lPlaces = "places";
/** @} */

/** @name Shape keys
 * @sa Shape
 * @{
 */
constexpr auto lModel = "model";
/** @} */
}; // namespace Format

} // namespace fsd
