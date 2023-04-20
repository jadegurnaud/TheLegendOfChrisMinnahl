#ifndef LOCAL_WALL_H
#define LOCAL_WALL_H
#include <gf/Entity.h>
#include <gf/Sprite.h>
#include <gf/Shapes.h>
#include <gf/Sprite.h>
#include <gf/RenderWindow.h>
#include <iostream>
constexpr gf::Vector2f WALL_SIZE = {32.0,32.0};

/** 
 * @brief Abstract class for all types of walls
*/
enum class WallType {SOLID,EMPTY,START,END,OBJECT,STATUE,SHOWCASE};

class Wall{
    protected:
        gf::Vector2f m_position;
        gf::RectF rect;
        gf::RectangleShape shape;
        gf::Color4f color;
        bool solid;
        WallType type;


    public:
        /**
         * @brief Default constructor
         * @param position world coordinates of the wall (topleft)
        */
        Wall(gf::Vector2f position,WallType type);

        gf::RectF getRect();

        gf::Vector2f getPosition()const;
        
		WallType getType()const;

        void render(gf::RenderTarget& target);

        bool equals(const Wall & other)const;

        /** 
         * @brief checks if the wall has collisions
        * @return true if the wall has collision, false otherwise
        */
        bool isSolid();

        bool setType(WallType type);
};

#endif
