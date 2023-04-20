#include "level.h"
#include <iostream>
Level::Level(Player & playerLink,Map & mapLink, gf::ResourceManager & resources) 
: map(mapLink)
, player(playerLink)
, m_resources(resources)
, m_wall_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/wall.png")))
, m_object_not_found_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/object_not_found.png")))
//, m_object_found_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/object_found.png")))
, m_floor_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/floor.png")))
, m_statue_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/socle_statue.png")))
, m_start_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/start.png")))
, m_end_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/end.png")))
, m_guard_textureRight(m_resources.getTexture(m_resources.getAbsolutePath("sprites/guard/guard_right.png")))
, m_guard_textureLeft(m_resources.getTexture(m_resources.getAbsolutePath("sprites/guard/guard_left.png")))
, m_guard_textureDown(m_resources.getTexture(m_resources.getAbsolutePath("sprites/guard/guard_down.png")))
, m_guard_textureUp(m_resources.getTexture(m_resources.getAbsolutePath("sprites/guard/guard_up.png")))
, m_faisceau_textureRight(m_resources.getTexture(m_resources.getAbsolutePath("sprites/guard/lampe001.png")))
, m_faisceau_textureLeft(m_resources.getTexture(m_resources.getAbsolutePath("sprites/guard/lampe000.png")))
, m_faisceau_textureDown(m_resources.getTexture(m_resources.getAbsolutePath("sprites/guard/lampe003.png")))
, m_faisceau_textureUp(m_resources.getTexture(m_resources.getAbsolutePath("sprites/guard/lampe002.png")))
, m_showcase_texture(m_resources.getTexture(m_resources.getAbsolutePath("sprites/wall/vitrine.png")))
{

	reset();
}


void Level::reset(){
	std::cout << "reset guards" << std::endl;
	for (Guard & guard :map.getGuards()){
		guard.reset();
	}
	isGameOver = false;
	notFoundObjects = map.getObjects();	
	foundObjects = {}; 
	isWin = false;
	player.init();
	player.setPosition(map.getStart().getPosition());
	player.setVelocity({0,0});
	//only reset if level loaded at least once
}


void Level::addGuard(gf::Vector2i pos, std::vector<struct RouteAction > route){
	Guard newGuard = Guard(pos);
	newGuard.setRoute(route);
	guards.push_back(newGuard);
}

void Level::update(gf::Time time){
	for (Guard & guard :map.getGuards()){
		guard.update(time);
	}	

	//X MOTION
	player.applyXMotion(time);
	gf::RectF collider = findCollider();
	if(!collider.isEmpty()){
		if(player.getVelocity().x > 0){//RIGHT
			player.setPosition({collider.min.x-PLAYER_SIZE.x,player.getPosition().y });
		}else if(player.getVelocity().x < 0){
			player.setPosition({collider.max.x,player.getPosition().y});
		}
	}

	//Y MOTION
	player.applyYMotion(time);
	collider = findCollider();
	if(!collider.isEmpty()){
		if(player.getVelocity().y > 0){//DOWN
			player.setPosition({player.getPosition().x,collider.min.y- PLAYER_SIZE.y});
		}else if (player.getVelocity().y <0){
			player.setPosition({player.getPosition().x,collider.max.y });
		}
	}	
	player.setVelocity({0,0});
	if(!player.isAStatue() && checkGuards()){
		isGameOver = true;
	}
}

gf::RectF Level::findCollider(){
	int y = map.getHeight();
	int x = map.getWidth();

	//Level collision
	for(int row = 0 ; row < y; row++ ){
		for (int col = 0; col<x ; col++){
			gf::RectF tmp = testCollision(map.get(col,row));
			if(!tmp.isEmpty()){
				return tmp;
			}
		}
	}
	//Object collision
	std::vector<Wall> objList = notFoundObjects;
	for(Wall & obj:objList){
			gf::RectF tmp = testCollision(obj);
			if(!tmp.isEmpty()){
				return tmp;
			}	
	}
	//Statue collision
	std::vector<Wall> statueList = map.getStatues();
	for(Wall & statue:statueList){
			gf::RectF tmp = testCollision(statue);
			if(!tmp.isEmpty()){
				return tmp;
			}	
	}
	//showcase collision
	std::vector<Wall> showcasesList = map.getShowcases();
	for(Wall & showcase:showcasesList){
			gf::RectF tmp = testCollision(showcase);
			if(!tmp.isEmpty()){
				return tmp;
			}	
	}
	gf::RectF tmp = testCollision(map.getEnd());
	if(!tmp.isEmpty()){
		return tmp;
	}	
	tmp = testCollision(map.getStart());
	if(!tmp.isEmpty()){
		return tmp;
	}	
	return gf::RectF::empty();
}

gf::RectF Level::testCollision(Wall & wall){
	if(wall.getType() == WallType::EMPTY){return gf::RectF::empty();}
	gf::RectF wallRect = gf::RectF::fromPositionSize(wall.getPosition(),WALL_SIZE);
	gf::RectF playerRect = gf::RectF::fromPositionSize(player.getPosition(),PLAYER_SIZE);

	if(wallRect.intersects(playerRect)){
		//Custom collision code
		doWhenCollide(wall);
		if(wall.getType() == WallType::SOLID || wall.getType() == WallType::SHOWCASE){
			return wallRect;
		}
		return gf::RectF::empty();
	}
	
	return	gf::RectF::empty();	
}

void Level::doWhenCollide(Wall & wall){
	//get grid position of the collided wall
	// int x = (int) wall.getPosition().x / WALL_SIZE.x;
	// int y = (int) wall.getPosition().y / WALL_SIZE.y;
	switch(wall.getType()){
		case WallType::OBJECT:
			foundObjects.push_back(wall);
			notFoundObjects.erase(
				std::remove_if(notFoundObjects.begin(), notFoundObjects.end(), 
					[wall](const Wall & other) {return wall.equals(other);}),
				notFoundObjects.end());
			break;
		case WallType::STATUE:
			if(player.isWantToStatue()){
				player.setStatue(true);
				player.setPosition(wall.getPosition());
			}else{
				player.setStatue(false);
			}
			break;
		case WallType::SHOWCASE:
			break;
		case WallType::START:
			break;
		case WallType::END:
			if(notFoundObjects.size()==0){
				isWin = true;
			}
			break;
		default:
			break;	
	}
}
bool Level::checkGuards(){
	gf::RectF playerRect = gf::RectF::fromPositionSize(player.getPosition(),PLAYER_SIZE);
	for(Guard & guard : map.getGuards()){
		gf::RectF guardRect = *guard.getRect();
		if(guardRect.intersects(playerRect)){
			return true;
		}
	}
	return false;
}
void Level::render(gf::RenderTarget & target, const gf::RenderStates & states){

	int y = map.getHeight();
	int x = map.getWidth();
	for(int row = 0 ; row < y; row++ ){
		for (int col = 0; col<x ; col++){
			Wall wall = map.get(col,row);
			WallType type = wall.getType();
			gf::Vector2f sprite_position = {wall.getPosition().x, wall.getPosition().y+WALL_SIZE.y};

			//floor
			if(wall.getType()==WallType::EMPTY){
				m_floor_sprite.setAnchor(gf::Anchor::BottomLeft);
				m_floor_sprite.setPosition(sprite_position);
				m_floor_sprite.setTexture(m_floor_texture);
				target.draw(m_floor_sprite);
			}

			

			//start
			if(map.getStart().getPosition()==wall.getPosition()){
				m_start_sprite.setAnchor(gf::Anchor::BottomLeft);
				m_start_sprite.setPosition(sprite_position);
				m_start_sprite.setTexture(m_start_texture);
				m_start_sprite.setScale(1);
				target.draw(m_start_sprite);
			}				
			
			//end
			if(map.getEnd().getPosition()==wall.getPosition()){
				m_end_sprite.setAnchor(gf::Anchor::BottomLeft);
				m_end_sprite.setPosition(sprite_position);
				m_end_sprite.setTexture(m_end_texture);
				m_end_sprite.setScale(1);
				target.draw(m_end_sprite);
			}

			

			//statue
			std::vector<Wall> statuesList = map.getStatues();
			for(Wall & statue : statuesList){
				if(statue.getPosition()==wall.getPosition()){
					m_statue_sprite.setAnchor(gf::Anchor::BottomLeft);
					m_statue_sprite.setPosition(sprite_position);
					m_statue_sprite.setTexture(m_statue_texture);
					m_statue_sprite.setScale(1);
					target.draw(m_statue_sprite);
				}
			}
		}
	}

	
	for(int row = 0 ; row < y; row++ ){
		for (int col = 0; col<x ; col++){
			Wall wall = map.get(col,row);
			WallType type = wall.getType();
			gf::Vector2f sprite_position = {wall.getPosition().x, wall.getPosition().y+WALL_SIZE.y};

			//player
			if(row == player.getGridPosY()){
				player.render(target,states);
			}
		
			//render guard
			for(Guard & guard : map.getGuards()){
				if(row == guard.getGridPosY() && guard.isPrint()==false){
					guard.setPrint();
					guard.render(target);
					
					m_guard_sprite.setScale(0.8);
					m_faisceau_sprite.setAnchor(gf::Anchor::BottomLeft);
					m_faisceau_sprite.setScale(0.15);
					if(guard.getdirectionGuard()==1){
						const gf::Vector2f sprite_position = {guard.getPosition().x, guard.getPosition().y+(GUARD_SIZE.y*1.5)};
						m_guard_sprite.setAnchor(gf::Anchor::BottomLeft);
						m_guard_sprite.setPosition(sprite_position);
						const gf::Vector2f faisceau_position_right = {guard.getPosition().x+20, guard.getPosition().y+20};
						m_guard_sprite.setTexture(m_guard_textureRight);
						m_faisceau_sprite.setTexture(m_faisceau_textureRight);
						m_faisceau_sprite.setPosition(faisceau_position_right);
						target.draw(m_guard_sprite);
						//target.draw(m_faisceau_sprite);
					}else if(guard.getdirectionGuard()==2){
						const gf::Vector2f sprite_position = {guard.getPosition().x-(GUARD_SIZE.x*1.5), guard.getPosition().y+(GUARD_SIZE.y*1.5)};
						m_guard_sprite.setAnchor(gf::Anchor::BottomLeft);
						m_guard_sprite.setPosition(sprite_position);
						const gf::Vector2f faisceau_position_left = {guard.getPosition().x-55, guard.getPosition().y+55};
						m_guard_sprite.setTexture(m_guard_textureLeft);
						m_faisceau_sprite.setTexture(m_faisceau_textureLeft);
						m_faisceau_sprite.setPosition(faisceau_position_left);
						target.draw(m_guard_sprite);
						//target.draw(m_faisceau_sprite);
					}else if(guard.getdirectionGuard()==3){
						const gf::Vector2f sprite_position = {guard.getPosition().x-(GUARD_SIZE.x*0.8), guard.getPosition().y+(GUARD_SIZE.y*1.9)};
						m_guard_sprite.setAnchor(gf::Anchor::BottomLeft);
						m_guard_sprite.setPosition(sprite_position);
						const gf::Vector2f faisceau_position_down = {guard.getPosition().x, guard.getPosition().y+90};
						m_guard_sprite.setTexture(m_guard_textureDown);
						m_faisceau_sprite.setTexture(m_faisceau_textureDown);
						m_faisceau_sprite.setPosition(faisceau_position_down);
						target.draw(m_guard_sprite);
						//target.draw(m_faisceau_sprite);
					}else if(guard.getdirectionGuard()==4){
						const gf::Vector2f sprite_position = {guard.getPosition().x-(GUARD_SIZE.x*0.8), guard.getPosition().y+GUARD_SIZE.y};
						m_guard_sprite.setAnchor(gf::Anchor::BottomLeft);
						m_guard_sprite.setPosition(sprite_position);
						const gf::Vector2f faisceau_position_up = {guard.getPosition()};
						m_faisceau_sprite.setTexture(m_faisceau_textureUp);
						m_faisceau_sprite.setPosition(faisceau_position_up);
						//target.draw(m_faisceau_sprite);
						m_guard_sprite.setTexture(m_guard_textureUp);
						target.draw(m_guard_sprite);	
					}
				}
			}
			//object not found
			for(Wall & obj : notFoundObjects){
				if(obj.getPosition()==wall.getPosition()){
					
					m_object_not_found_sprite.setAnchor(gf::Anchor::BottomLeft);
					m_object_not_found_sprite.setPosition({wall.getPosition().x+(WALL_SIZE.x*0.17), wall.getPosition().y+WALL_SIZE.y});
					m_object_not_found_sprite.setTexture(m_object_not_found_texture);
					m_object_not_found_sprite.setScale(0.7);
					target.draw(m_object_not_found_sprite);
					
				}
			}
			//showcase
			if(wall.getType()==WallType::SHOWCASE){
				m_showcase_sprite.setAnchor(gf::Anchor::BottomLeft);
				m_showcase_sprite.setPosition({sprite_position.x-3,sprite_position.y});
				m_showcase_sprite.setTexture(m_showcase_texture);
				m_showcase_sprite.setScale({1.095});
				target.draw(m_showcase_sprite);
			}
			

			//render wall
			if(wall.getType()==WallType::SOLID){
				m_wall_sprite.setAnchor(gf::Anchor::BottomLeft);
				m_wall_sprite.setPosition(sprite_position);
				m_wall_sprite.setTexture(m_wall_texture);
				target.draw(m_wall_sprite);
			}
		}
	}
}



bool Level::checkGameOver(){
	return isGameOver;
}

bool Level::checkWin(){
	return isWin;
}

std::vector<Wall> & Level::getFoundObjects(){
	return foundObjects;
}
std::vector<Wall> & Level::getNotFoundObjects(){
	return notFoundObjects;
}

