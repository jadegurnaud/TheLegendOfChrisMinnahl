#ifndef LOCAL_GUARD_H
#define LOCAL_GUARD_H
#include <gf/Entity.h>
#include <gf/Sprite.h>
#include <gf/Shapes.h>
#include <gf/Event.h>
#include <gf/RenderWindow.h>

constexpr gf::Vector2i GUARD_SIZE = {32,32};
constexpr gf::Vector2i DETECTOR_SIZE = {80,80};


enum class actionType{GO,WAIT};


struct RouteAction {
  actionType type;
  float time;
  float cumulated_time;
  gf::Vector2i grid_position;
  RouteAction (actionType type,float time,float cumulated_time,gf::Vector2i grid_position):type(type),time(time),grid_position(grid_position) {}
};

//RouteAction dummy = RouteAction(actionType::WAIT,1,0,{0,0});

struct RouteAction newRoute(actionType type,float time,gf::Vector2i position);

class Guard : public gf::Entity{

    private:
    	std::vector<struct RouteAction> route;
    	int route_index;
    	
        gf::Vector2f position, last_position, spawn_position;
        double speed;
        gf::RectF rect;
        gf::RectangleShape shape;
        gf::Color4f color;
        gf::RectF detectorRect;
        gf::RectangleShape detectorShape;
        int dirGuard;
        bool print;
    public:
        Guard(gf::Vector2i grid_pos);
        bool isPrint();
        void setPrint();
        void reset();
		void nextAction();
        gf::Vector2f getPosition()const;
        int getdirectionGuard();
        int getGridPosY();
        void setRoute(std::vector<struct RouteAction > route);
        virtual void update(gf::Time time);
        virtual void render(gf::RenderTarget& target);
        gf::RectF * getRect();
};
#endif
