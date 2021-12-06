/**
 * \file IslandOrBridge.h
 * \brief Used to convert board coordinates into usable ones
 * \author Théotime Maillarbaux
 * \date 06/12/2021
 */

#ifndef ISLANDORBRIDGE_H
#define ISLANDORBRIDGE_H

#include "model/Coord.h"

/**
 * \enum EntityType
 * \brief Indicates which entity was clicked.
 */
typedef enum {
	WATER, ///< Nothing in particular was clicked
	ISLAND, ///< An Island was clicked
	VBRIDGE, ///< A vertical bridge was clicked
	HBRIDGE ///< A horizontal bridge was clicked
} EntityType;

/**
 * \struct IslandOrBridge
 * \brief Represents a set of coordinates coherent with the CoordType.
 */
typedef struct {
	int x; ///< The coordinate on the X-axis.
	int y; ///< The coordinate on the Y-axis.
	EntityType type; ///< The type of the entity clicked.
} IslandOrBridge;

/**
 * \brief Converts a set of board coordinates into a usable set of coordinates.
 * \param[in] c The set of board coordinates.
 * \return An IslandOrBridge struct with coherent coordinates with the type of entity.
 */
IslandOrBridge coordToEntity(Coord c);

#endif // ISLANDORBRIDGE_H

