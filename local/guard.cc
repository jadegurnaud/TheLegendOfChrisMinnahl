#include "guard.h"
#include "wall.h"
#include <iostream>
#include <cmath>
bool is_between(float number, float lower,float upper){
	return ((unsigned)(number-lower) <= (upper-lower));
}


RouteAction  newRoute(actionType type,float time,gf::Vector2i position){
	return RouteAction(type,time,0.0,position);
}

Guard::Guard(gf::Vector2i grid_pos):
	shape(GUARD_SIZE),
	detectorShape(DETECTOR_SIZE){
	
    speed = 200;
    position = grid_pos * WALL_SIZE;
    spawn_position = position;
    rect = gf::RectF().fromPositionSize(position,GUARD_SIZE);  
    color = gf::Color::Red;
   	shape.setColor(color);
    shape.setAnchor(gf::Anchor::TopLeft);
    shape.setPosition(position);
    detectorShape.setColor(gf::Color4f({0.7,0.7,0,0.5}));
    detectorShape.setAnchor(gf::Anchor::TopLeft);
   	detectorShape.setPosition(position);   
	dirGuard=3; 		

}

void Guard::reset(){
	position = spawn_position;

    rect = gf::RectF().fromPositionSize(position,GUARD_SIZE);  
    shape.setPosition(position);
    detectorShape.setColor(gf::Color4f({0.7,0.7,0,0.5}));
   	detectorShape.setPosition(position);
   	detectorRect = detectorRect.fromPositionSize(detectorShape.getPosition(),DETECTOR_SIZE);

	route_index = -1;
	nextAction();//initialize first action
}

void Guard::setRoute(std::vector<RouteAction> new_route){
	route = new_route;
	route_index = -1;
	
}

gf::RectF * Guard::getRect(){
	return &detectorRect;
}

gf::Vector2f Guard::getPosition()const{
    return position;
}

void Guard::nextAction(){
	if(route.size()==0){return;}
	route_index ++;
	
   	if(route_index >= (int)route.size()){
   		route_index = 0;
   	}


    RouteAction & currentAction = route[route_index];
   	currentAction.cumulated_time = 0;
//
    // std::cout << "Route index : "<< route_index <<"\n";
	// std::cout << "New action ! "<< (currentAction.type == actionType::GO ?  "GO" : "WAIT") <<"\n";
	// std::cout << "time : " << currentAction.time << "\n";
	// std::cout << "Cumul time : " << currentAction.cumulated_time << "\n";

	//
   	switch(currentAction.type){
   		case actionType::WAIT:
   			shape.setColor(gf::Color::Azure);
   			break;
   	   	case actionType::GO:
   	   	   	shape.setColor(gf::Color::Red);
   	   	   	last_position = position;

   			break;
   		default:
   			break;
   	}

}

int Guard::getdirectionGuard(){
	return dirGuard;
}

int Guard::getGridPosY(){
	float y_pos;
	y_pos = position.y + GUARD_SIZE.y - 0.1;
	return (int) y_pos / WALL_SIZE.y;
}

bool Guard::isPrint(){
	return print;
}

void Guard::setPrint(){
	print=true;
}

void Guard::update(gf::Time time){
	print=false;
	float dt = time.asSeconds();
	gf::Vector2f target;
	float time_proportion,deltaX,deltaY,upper,lower;
	;RouteAction & currentAction = route[route_index];

    switch(currentAction.type){
    	case actionType::WAIT:
    		break;
    	case actionType::GO:
    		time_proportion = currentAction.cumulated_time / currentAction.time;
    		deltaX = (currentAction.grid_position.x * WALL_SIZE.x) - last_position.x;
    		deltaY = (currentAction.grid_position.y * WALL_SIZE.y) - last_position.y;

			target = {
				(float)round(last_position.x + deltaX * time_proportion ),
				(float)round(last_position.y + deltaY * time_proportion),

			};
			//std::cout << "target : " << target[0] << ", " << target[1] << std::endl;
			lower = std::min(last_position.x,currentAction.grid_position.x * WALL_SIZE.x);	
			upper = std::max(last_position.x,currentAction.grid_position.x * WALL_SIZE.x);	

    		if ( is_between(target.x,lower,upper)){
    		 	position.x =target.x;
			}else{
    			position.x =  (currentAction.grid_position.x * WALL_SIZE.x);
    		}
    		
    		position.y = last_position.y + deltaY * time_proportion;

			lower = std::min(last_position.y,currentAction.grid_position.y * WALL_SIZE.y);	
			upper = std::max(last_position.y,currentAction.grid_position.y * WALL_SIZE.y);	

			//CLAMP VALUES
    		if ( is_between(target.y,lower,upper)){
    		 	position.y =target.y;
			}else{
    			position.y =  (currentAction.grid_position.y * WALL_SIZE.y);
    		}

    	   	rect = rect.fromPositionSize(position,GUARD_SIZE);
    		shape.setPosition(position);

			detectorShape.setPosition(rect.getTopLeft());

			deltaX = round(deltaX);
			deltaY = round(deltaY);
			if (abs(deltaX) > abs(deltaY)){
				if (deltaX > 0 ){
					//going right
					detectorShape.move({0,+(GUARD_SIZE.y * 0.5) - (DETECTOR_SIZE.y * 0.5)});
					dirGuard=1;
				}else if (deltaX <0){
					//going left
					detectorShape.move({-DETECTOR_SIZE.x +GUARD_SIZE.x,+(GUARD_SIZE.y * 0.5) - (DETECTOR_SIZE.y * 0.5)});
					dirGuard=2;
				}
			}else{
				if(deltaY > 0){
					//going down
					detectorShape.move({(GUARD_SIZE.x * 0.5) - (DETECTOR_SIZE.x * 0.5),0});
					dirGuard=3;
				}else if(deltaY <0){
					//going up
					detectorShape.move({(GUARD_SIZE.x * 0.5) - (DETECTOR_SIZE.x * 0.5),-DETECTOR_SIZE.y + GUARD_SIZE.y});
					dirGuard=4;
				}
			}		

    		detectorRect = detectorRect.fromPositionSize(detectorShape.getPosition(),DETECTOR_SIZE);


    		break;
    	default:
    		break;
    }



	currentAction.cumulated_time += dt;

	//unchanged

    
    if (currentAction.cumulated_time >= currentAction.time){
    	//std::cout << "dt : "<< dt << std::endl;
		nextAction();
    }
}

void Guard::render(gf::RenderTarget& target){
	//target.draw(detectorShape);
    //target.draw(detectorShape);

    //target.draw(shape);
};

