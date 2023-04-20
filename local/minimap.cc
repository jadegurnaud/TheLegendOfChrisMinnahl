#include "minimap.h"
#include <iostream>

Minimap::Minimap(Game& game, gf::ResourceManager & resources) 
: m_map(game.getMap())
, m_player(game.getPlayer())
, m_level(game.getLevel())
, m_statues(m_map.getStatues())
, m_not_found_objects(m_level.getNotFoundObjects())
, m_start(m_map.getStart())
, m_end(m_map.getEnd())
, m_resources(resources)
, m_wall_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/wall.png")))
, m_object_not_found_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/object_not_found.png")))
//, m_object_found_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/object_found.png")))
, m_floor_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/floor.png")))
, m_statue_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/socle_statue.png")))
, m_start_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/start.png")))
, m_end_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/end.png")))
, m_showcase_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/vitrine.png")))
{
	m_minimap_size={m_map.getWidth()*WALL_SIZE.x,m_map.getHeight()*WALL_SIZE.y};
}

gf::Vector2f Minimap::getSize(){
	return m_minimap_size;
}

void Minimap::update(gf::Time time){
	m_minimap_size={m_map.getWidth()*WALL_SIZE.x,m_map.getHeight()*WALL_SIZE.y};
    m_not_found_objects = m_level.getNotFoundObjects();
}

void Minimap::render(gf::RenderTarget & target, const gf::RenderStates & states){
    bool find = false;
	//render wall
	int y = m_map.getHeight();
	int x = m_map.getWidth();
	for(int row = 0 ; row < y; row++ ){
		for (int col = 0; col<x ; col++){
			find = false;
			Wall wall = m_map.get(col,row);
			WallType type = wall.getType();
			gf::Vector2f sprite_position = {wall.getPosition().x, wall.getPosition().y+WALL_SIZE.y};

			//ground
			if(wall.getType()==WallType::EMPTY){
				m_floor_sprite.setAnchor(gf::Anchor::BottomLeft);
				m_floor_sprite.setPosition(sprite_position);
				m_floor_sprite.setTexture(m_floor_texture);
				target.draw(m_floor_sprite);
			}
			//showcase
			if(wall.getType()==WallType::SHOWCASE){
				m_showcase_sprite.setAnchor(gf::Anchor::BottomLeft);
				m_showcase_sprite.setPosition({sprite_position.x-3,sprite_position.y});
				m_showcase_sprite.setTexture(m_showcase_texture);
				m_showcase_sprite.setScale({1.095});
				target.draw(m_showcase_sprite);
			}

			//object not found
			for(Wall & obj : m_not_found_objects){
				if(obj.getPosition()==wall.getPosition()){
					
					m_object_not_found_sprite.setAnchor(gf::Anchor::BottomLeft);
					m_object_not_found_sprite.setPosition({wall.getPosition().x+(WALL_SIZE.x*0.17), wall.getPosition().y+WALL_SIZE.y});
					m_object_not_found_sprite.setTexture(m_object_not_found_texture);
					m_object_not_found_sprite.setScale(0.7);
					target.draw(m_object_not_found_sprite);
					
				}
			}

			//statue
			if(find){continue;};
			std::vector<Wall> statuesList = m_map.getStatues();
			for(Wall & statue : statuesList){
				if(statue.getPosition()==wall.getPosition()){
					m_statue_sprite.setAnchor(gf::Anchor::BottomLeft);
					m_statue_sprite.setPosition(sprite_position);
					m_statue_sprite.setTexture(m_statue_texture);
					m_statue_sprite.setScale(1);
					target.draw(m_statue_sprite);
					find=true;
				}
			}


			//start
			if(find){continue;};
			if(m_map.getStart().getPosition()==wall.getPosition()){
				m_start_sprite.setAnchor(gf::Anchor::BottomLeft);
				m_start_sprite.setPosition(sprite_position);
				m_start_sprite.setTexture(m_start_texture);
				m_start_sprite.setScale(1);
				target.draw(m_start_sprite);
				find=true;
			}



			//end
			if(find){continue;};
			if(m_map.getEnd().getPosition()==wall.getPosition()){
				m_end_sprite.setAnchor(gf::Anchor::BottomLeft);
				m_end_sprite.setPosition(sprite_position);
				m_end_sprite.setTexture(m_end_texture);
				m_end_sprite.setScale(1);
				target.draw(m_end_sprite);
				find=true;
			}
		

			//wall
			if(find){continue;};
			if(wall.getType()==WallType::SOLID){
				m_wall_sprite.setAnchor(gf::Anchor::BottomLeft);
				m_wall_sprite.setPosition(sprite_position);
				m_wall_sprite.setTexture(m_wall_texture);
				target.draw(m_wall_sprite);
			}

			if(row == m_player.getGridPosY()){
				m_player.render(target,states);
			}
		}
	}

}






