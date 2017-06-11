#pragma once

#include "cocos2d.h"
#include "fudancraft.h"

class GridSize;

struct GridPoint
{
	GridPoint(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	int x, y;		//The integer coordinate of grid point


	bool operator==(const GridPoint& gp2) const;
	friend GridPoint operator+(const GridPoint& gp1, const GridPoint& gp2);
	friend GridPoint operator-(const GridPoint& gp1, const GridPoint& gp2);
	friend GridPoint operator-(const GridPoint& gp, const GridSize& gz);
	GridPoint getDirectionVector();
};

typedef GridPoint GridVec;

typedef std::vector<GridPoint>  GridPath;

struct GridSize
{
	int width;
	int height;

	GridSize(int _width = 0, int _height = 0) : width(_width), height(_height) {}
	friend GridSize operator/(const GridSize& gz, int s);
};

struct GridRect
{
	GridPoint gp;		//The left-down endpoint of the grid rectangle
	GridSize size;		//The integer size of the grid rectangle

	GridRect(GridPoint _gp = GridPoint(), GridSize _size = GridSize()) : gp(_gp), size(_size) {}
};

class GridMap : public cocos2d::Ref
{
public:
	static GridMap* create(const cocos2d::TMXTiledMap * tiled_map);
	GridPoint findFreePositionNear( const GridPoint& gp);
	cocos2d::Point getPoint(const GridPoint& gp);
	GridPoint getGridPoint(const cocos2d::Point& p);
	cocos2d::Point getGridRectCenter(const GridRect& grec);
	cocos2d::Point getPointWithOffset(const GridPoint& gp);
	GridPoint getGridPointWithOffset(const cocos2d::Point& p);
	bool checkPosition(const GridRect& grec);
	bool checkPosition(const GridPoint& gp);
	bool occupyPosition(int id, const GridPoint& pos, bool occupy_grid = true);
	bool occupyPosition(int id, const cocos2d::Point& pos, bool occupy_grid = true);
	bool occupyPosition(int id, const GridRect& grec, bool occupy_grid = true);
	bool checkPointInMap(const GridPoint& gp) const;
	bool checkPointInMap(int x, int y) const;
	void leavePosition(const GridPoint& pos, bool occupy_grid = true);
	void leavePosition(const GridRect& grec, bool occupy_grid = true);
	std::vector<std::vector<int>>& getLogicalGridMap();
	std::vector<int> getUnitIDAt(const GridRect& range) const;
	int getUnitIDAt(const GridPoint& gp) const;

	bool hasApproached(const cocos2d::Point& cur_fp, const GridPoint& dest_gp);
private:
	bool initWithTiledMap(const cocos2d::TMXTiledMap* tiled_map);
	std::vector<std::vector<int>> gmap;		//Grid layer, records whether grids are occupied
	std::vector<std::vector<int>> umap;		//Unit ID layer, records the IDs of units occupy the grids
	int map_width, map_height;				//The width and height of the map (number of grids)
	int grid_width, grid_height;			//The width and height of the grids (number of pixels)
	cocos2d::Vec2 offset_vec;				//The offset vector caused by grid
};