/**
 * \file Bridge.h
 * \brief Bridge
 * \autor Martin Roualt, Jacques Thomas
 * \date 13/12/2021
 */

#ifndef BRIDGE_INCLUDED
#define BRIDGE_INCLUDED

#include "model/Island.h"

/**
 * \struct Bridge
 * \brief Represents a bridge which is two island
 */
typedef struct {
    Island islandA;///< Horizontal : left to islandB, Vertical : up to islandB
    Island islandB;///< Horizontal : right to islandA, Vertical : down to islandA
} Bridge;

#endif //BRIDGE_INCLUDED