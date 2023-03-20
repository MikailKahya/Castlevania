#pragma once
#include <vector>
class Sprite;
class Texture;

class Room
{
public:
	enum class Type { stone, sandstone, clean };

	Room(const std::string& svgPath, Type tileType);
	Room(const std::string& svgPath, const Rectf& bounds, Type tileType);
	virtual ~Room();

	virtual void Draw() const;
	std::vector<std::vector<Point2f>> GetRoom();
	void SetBounds(const Rectf& bounds);

protected:
	void CreateStatics();

	static const std::vector<Texture*> BG_TEXTURES;
	static const std::vector<Texture*> TILES_TEXTURES;

	int m_Id;
	std::vector<Sprite*> m_pSpriteVec;
	std::vector<std::vector<Point2f>> m_SvgMap;
	Rectf m_Bounds;
	std::vector<Point2f> m_SpawnVec;
};

