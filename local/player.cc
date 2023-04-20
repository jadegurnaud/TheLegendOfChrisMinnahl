#include "player.h"
#include <iostream>
Player::Player(gf::ResourceManager& resources)
:resources(resources)
,textureRight(resources.getTexture(resources.getAbsolutePath("sprites/player/player_right.png")))
,textureLeft(resources.getTexture(resources.getAbsolutePath("sprites/player/player_left.png")))
,textureUp(resources.getTexture(resources.getAbsolutePath("sprites/player/player_up.png")))
,textureDown(resources.getTexture(resources.getAbsolutePath("sprites/player/player_down.png")))
,textureStatue(resources.getTexture(resources.getAbsolutePath("sprites/player/statue.png")))
{
	setPosition({0,0});

	
	isStatue=false;
	dirPlayer=3;
	statueSprite=false;
}
void Player::setPosition(gf::Vector2f pos){
	position = pos;
}
gf::Vector2f Player::getPosition(){
	return position;
}

void Player::init(){
	isStatue=false;
}

int Player::getGridPosY()const{
	float y_pos;
	y_pos = position.y + PLAYER_SIZE.y - 0.1;
	return (int) y_pos / WALL_SIZE.y;
}

void Player::setVelocity(gf::Vector2f vel){
	velocity = vel;
}
gf::Vector2f Player::getVelocity(){
	return velocity;
}
void Player::addVelocity(gf::Vector2f vel){
	velocity += vel;
}



void Player::setStatue(bool val){
	isStatue = val;
}
bool Player::isAStatue(){
	return isStatue;
}

void Player::setWantToStatue(bool val){
	wantToStatue=  val;
}

bool Player::isWantToStatue(){
	return wantToStatue;
}

void Player::setStatueSprite(bool var){
	statueSprite=  var;
}
void Player::applyXMotion(gf::Time time){
	float dt = time.asSeconds();
	position.x += velocity.x * speed * dt;

}
void Player::applyYMotion(gf::Time time){
	float dt = time.asSeconds();	
	position.y += velocity.y * speed * dt;
}
void Player::setdirectionPlayer(int var){
	dirPlayer=var;
}
void Player::render(gf::RenderTarget & target, const gf::RenderStates & states){
	gf::RectangleShape shape(PLAYER_SIZE);
	
	shape.setPosition(position);
	//target.draw(shape);
	sprite.setAnchor(gf::Anchor::BottomLeft);
	sprite.setPosition({getPosition().x, getPosition().y+PLAYER_SIZE.y});
	sprite.setScale(0.8);
	if(isAStatue()==true){
		sprite.setTexture(textureStatue);
		sprite.setScale(0.1);
	}else if(dirPlayer==1){
		sprite.setTexture(textureRight);
	}else if(dirPlayer==2){
		sprite.setTexture(textureLeft);
	}else if(dirPlayer==3){
		sprite.setTexture(textureUp);
	}else if(dirPlayer==4){
		sprite.setTexture(textureDown);
		
	}	
	target.draw(sprite);

}
