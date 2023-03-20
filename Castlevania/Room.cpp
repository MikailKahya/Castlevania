#include "pch.h"
#include "Room.h"
#include <SVGParser.h>
#include <Texture.h>
#include <Sprite.h>

const std::vector<Texture*> Room::BG_TEXTURES{};
const std::vector<Texture*> Room::TILES_TEXTURES{};

Room::Room(const std::string& svgPath, Type tileType)
    : Room(svgPath, Rectf{ 0.0f, 0.0f, 0.0f, 0.0f }, tileType)
{
}

Room::Room(const std::string& svgPath, const Rectf& bounds, Type tileType)
    : m_Id{ 1 }
    , m_pSpriteVec{}
    , m_SvgMap{}
    , m_Bounds{ bounds }
    , m_SpawnVec{}
{
    SVGParser::GetVerticesFromSvgFile(svgPath, m_SvgMap);
    CreateStatics();
}

Room::~Room()
{
    for (Sprite* pTexture : m_pSpriteVec)
    {
        delete pTexture;
    }
}

void Room::Draw() const
{
    for (Sprite* pSprite: m_pSpriteVec)
    {
        pSprite->Draw();
    }
}

std::vector<std::vector<Point2f>> Room::GetRoom()
{
    return m_SvgMap;
}

void Room::SetBounds(const Rectf& bounds)
{
    m_Bounds = bounds;
}

void Room::CreateStatics()
{
    if (BG_TEXTURES.empty())
    {
        const std::string pathString{ "Level/Bg/" };
        //BG_TEXTURES.push_back(new Texture{ pathString + "Stone.png" });
        //BG_TEXTURES.push_back(new Texture{ pathString + "Sandstone.png"})
    }
}
