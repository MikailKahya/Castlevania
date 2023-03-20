#include "pch.h"
#include "Corridor.h"

Corridor::Corridor(const std::string& svgPath, Type tileType)
	: Room(svgPath, tileType)
{
}

Corridor::Corridor(const std::string& svgPath, const Rectf& bounds, Type tileType)
	: Room(svgPath, bounds, tileType)
{
}
