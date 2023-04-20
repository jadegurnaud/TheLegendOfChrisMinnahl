#include "wall.h"
  
Wall::Wall(gf::Vector2f position,WallType type){
    this->m_position = position;
    //Set up the collider rect
    this->rect = gf::RectF().fromPositionSize(this->m_position,WALL_SIZE);

	//Set up the shape (visual representation of the player)
    this->shape.setAnchor(gf::Anchor::TopLeft);
    this->shape.setPosition(this->m_position);
    this->shape.setSize(WALL_SIZE);

	//Sets the type of wall, (solid ?, color?)
    this->setType(type);
}
WallType Wall::getType()const{
	return this->type;
}

bool Wall::equals(const Wall & other)const{
	return (other.getType() == getType()) && (other.getPosition() == getPosition());
}

bool Wall::setType(WallType type){
    switch(type){
        case WallType::EMPTY:
            this->solid = false;
            this->color = gf::Color::Gray(0.2f);
            break;
        case WallType::SOLID:
            this->solid = true;
            this->color = gf::Color::Green;
            break;
        case WallType::START:
        	this->solid = false;
        	this->color = gf::Color::Yellow;
        	break;
        case WallType::END:
        	this->solid = false;
        	this->color = gf::Color::Magenta;
        	break;
        case WallType::OBJECT:
        	this->solid = false;
        	this->color = gf::Color::Orange;
        	break;
        case WallType::STATUE:
        	this->solid = false;
        	this->color = gf::Color::Blue;
        	break;
        case WallType::SHOWCASE:
        	this->solid = true;
        	this->color = gf::Color::Orange;
        	break;
        default:
            return false;
    }
    this->shape.setColor(this->color);

    this->type = type;
    return true;
}

gf::RectF Wall::getRect(){
    return this->rect;
}

gf::Vector2f Wall::getPosition()const{
    return this->m_position;
}

bool Wall::isSolid(){
    return this->solid;
}

void Wall::render(gf::RenderTarget& target){
    target.draw(this->shape);
}
