#ifndef __PATHFINDING_H__
#define __PATHFINDING_H__
#include "gf2d_vector.h"
#include "tilemap.h"

typedef struct intVec2_s
{
	int row;
	int column;
}intVec2;

int RowFromIndex(int index);

int ColumnFromIndex(int index);

int MatrixToIndex(int row, int column);

int TileAbove(int index);
int TileRight(int index);
int TileDown(int index);
int TileLeft(int index);

#endif // ! __PATHFINDING_H__

