#ifndef LOCAL_LEVEL_H
#define LOCAL_LEVEL_H
#include <gf/Entity.h>
#include <gf/Sprite.h>
#include <gf/Shapes.h>
#include <gf/RenderWindow.h>
#include <gf/ResourceManager.h>
#include <gf/Text.h>
#include <gf/Widgets.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include "wall.h"
#include "player.h"
#include "guard.h"
#include "map.h"


class Level : public gf::Entity{
	private:
		Map& map;
		Player& player;
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
		gf::Texture & m_guard_textureRight;
		gf::Texture & m_guard_textureLeft;
		gf::Texture & m_guard_textureDown;
		gf::Texture & m_guard_textureUp;
		gf::Sprite m_guard_sprite;
		gf::Texture & m_faisceau_textureRight;
		gf::Texture & m_faisceau_textureLeft;
		gf::Texture & m_faisceau_textureDown;
		gf::Texture & m_faisceau_textureUp;
		gf::Sprite m_faisceau_sprite;
		gf::Texture & m_showcase_texture;
		gf::Sprite m_showcase_sprite;
		bool isGameOver;
		bool isWin;
		std::vector<Wall> foundObjects;
		std::vector<Wall> notFoundObjects;
		std::vector<Guard> guards;
	public:
		Level(Player & player, Map & map, gf::ResourceManager & resources);
		void reset();
		virtual void render(gf::RenderTarget & target,
		const gf::RenderStates & states);	
		void addGuard(gf::Vector2i pos,std::vector<struct RouteAction > route);
		void update(gf::Time time);
		//find collider rect
		gf::RectF findCollider();
		//custom code to do once collided with a non empty wall
		void doWhenCollide(Wall & wall);
		bool checkGuards();
		bool checkGameOver();
		bool checkWin();
		std::vector<Wall> & getFoundObjects();
		std::vector<Wall> & getNotFoundObjects();

		gf::RectF testCollision(Wall & wall);
};		
#endif
