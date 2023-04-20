#ifndef LOCAL_MINIMAP_H
#define LOCAL_MINIMAP_H

#include "map.h"
#include "player.h"
#include "wall.h"
#include "level.h"
#include "../scenes/game.h"


class Minimap : public gf::Entity{
	private:
		Map& m_map; 
        Player& m_player;
        Level& m_level;
        std::vector<std::vector<Wall>> m_walls;
        std::vector<Wall> m_statues;
        std::vector<Wall> m_not_found_objects;
		Wall m_start, m_end;
        gf::Vector2f m_minimap_size;

        gf::ResourceManager & m_resources;
        gf::Texture & m_wall_texture;
		gf::Sprite m_wall_sprite;
		gf::Texture & m_object_not_found_texture;
		gf::Sprite m_object_not_found_sprite;
		//gf::Texture & m_object_found_texture;
		//gf::Sprite m_object_found_sprite;
		gf::Texture & m_floor_texture;
		gf::Sprite m_floor_sprite;
		gf::Texture & m_statue_texture;
		gf::Sprite m_statue_sprite;
		gf::Texture & m_start_texture;
		gf::Sprite m_start_sprite;
		gf::Texture & m_end_texture;
		gf::Sprite m_end_sprite;
		gf::Texture & m_showcase_texture;
		gf::Sprite m_showcase_sprite;
		
	public:
		Minimap(Game& game, gf::ResourceManager & resources) ;
        gf::Vector2f getSize();
        virtual void render(gf::RenderTarget & target, const gf::RenderStates & states);
        void update(gf::Time time);
		

};		
#endif
