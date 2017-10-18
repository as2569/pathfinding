#include "pathfinding.h"
#include "tilemap.h"
#include "gf2d_vector.h"
#include "simple_logger.h"

int RowFromIndex(int index)
{
	int temp;
	temp = index / 32;
	return temp;
}

int ColumnFromIndex(int index)
{
	int temp;
	temp = index % 32;
	return temp;
}

int MatrixToIndex(int row, int column)
{
	int temp;
	temp = (row * 32) + column;
	return temp;
}

int TileAbove(int index)
{
	int row = RowFromIndex(index);
	int column = ColumnFromIndex(index);
	if (row - 1 >= 0)
	{
		int temp_index = MatrixToIndex(row - 1, column);
		//slog("Tile index %i", temp_index);
		return temp_index;
	}

}

int TileRight(int index)
{
	int row = RowFromIndex(index);
	int column = ColumnFromIndex(index);
	if (column + 1 <= 32)
	{
		int temp_index = MatrixToIndex(row,  column + 1);
		//slog("Tile index %i", temp_index);
		return temp_index;
	}
}

int TileDown(int index)
{
	int row = RowFromIndex(index);
	int column = ColumnFromIndex(index);
	if (row + 1 <= 20)
	{
		int temp_index = MatrixToIndex(row + 1, column);
		//slog("Tile index %i", temp_index);
		return temp_index;
	}
}

int TileLeft(int index)
{
	int row = RowFromIndex(index);
	int column = ColumnFromIndex(index);
	if (column - 1 >= 0)
	{
		int temp_index = MatrixToIndex(row, column - 1);
		//slog("Tile index %i", temp_index);
		return temp_index;
	}
}
