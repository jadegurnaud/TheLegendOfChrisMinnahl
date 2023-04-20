#include "map.h"
using json = nlohmann::json;
Map::Map()
: start(Wall({0,0},WallType::START))
, end(Wall({1*WALL_SIZE.x,1*WALL_SIZE.y},WallType::END))
{

}

void Map::set(gf::Vector2i pos, WallType type){
	if(pos.y < 0 || pos.y >= (int)data.size()){return;}
	if(pos.y < 0 || pos.y >= (int)data.size()){return;}
	Wall newWall = Wall(pos * WALL_SIZE, type);
	switch(type){
		case WallType::OBJECT:
			objects.push_back(newWall);
			break;
		case WallType::STATUE:
			statues.push_back(newWall);
			break;
		/*case WallType::SHOWCASE:
			showcases.push_back(newWall);
			break;*/
		case WallType::START:
			start = newWall;
			break;
		
		case WallType::END:
			end = newWall;
			break;
		default:
			data[pos.y][pos.x] = newWall;
			break;
	}
}

Wall & Map::get(int x , int y){
	if(y < 0 || y >= (int)data.size() ||x < 0 || x >= (int)data[y].size() ){
		throw std::out_of_range("Invalid coordinates to getWall");
	}
	return data[y][x];
}
Wall & Map::getStart(){
	return start;
}
Wall & Map::getEnd(){
	return end;
}
std::vector<Wall> & Map::getObjects(){
	return objects;
}
std::vector<Wall> & Map::getStatues(){
	return statues;
}
std::vector<Guard> & Map::getGuards(){
	return guards;
}
std::vector<Wall> & Map::getShowcases(){
	return showcases;
}

int Map::getHeight(){return height;}
int Map::getWidth(){return width;}



//path 
void Map::load(gf::Path level_path){
	objects = {};
	statues = {};
	guards = {};
	
	start = Wall({0,0},WallType::START);
	end = Wall({1*WALL_SIZE.x,1*WALL_SIZE.y},WallType::END);

	data = {};
	FILE* f = fopen((level_path).c_str(),"r");
	if (f == nullptr){
		std::cout << "Couldn't open "<< (level_path).c_str() << std::endl;
		exit(1);
		return;
	}

	width = 0;
	height = 0;
	char line[128];
	while (fgets(line,128,f)){
		width = strlen(line)-1;
		height++;
	}
	rewind(f);

	//fill level with empty walls
    for(float i = 0; i<height;i++){
        data.push_back({});
        for(float j = 0; j<width;j++){
            gf::Vector2f pos = {j,i};
            pos = pos*WALL_SIZE;
            data[i].push_back(Wall(pos,WallType::EMPTY));
        }
    }
	char c;
	int row = 0;
	int col = 0;
	while(!feof(f)){
		c = getc(f);
		WallType tmp = WallType::EMPTY;
		switch(c){
			case '\0':
				break;
			case '\n':
				row++;
				col = -1;
				break;
			case 's':
				tmp = WallType::START;
				break;
			case 'e':
				tmp = WallType::END;
				break;
			case 'o':
				tmp = WallType::OBJECT;
				break;
			case 't':
				tmp = WallType::STATUE;
				break;
			case '#':
				tmp = WallType::SOLID;
				break;
			case 'v':
				tmp = WallType::SHOWCASE;
				break;
		}
		if(c=='\0'){break;}
		if(tmp != WallType::EMPTY){
			set({col,row},tmp);
		}

		col++;
	}
			
	fclose(f);


	//Load guards
	gf::Path guards_path = level_path.replace_extension(".json");

    std::ifstream jsonFile(guards_path);
    if(!jsonFile){
		std::cout << "Couldn't open "<<guards_path << std::endl;
    	return;
    }
	std::string jsonString((std::istreambuf_iterator<char>(jsonFile)),
                            std::istreambuf_iterator<char>());
	json jsonData = json::parse(jsonString);
	for(auto & guard : jsonData["list"]){
		Guard newGuard = Guard({guard["position"]["x"],guard["position"]["y"]});
		std::vector<struct RouteAction> routeList;
		for(auto & routeItem : guard["route"]){
			actionType tmp = (routeItem["type"] == "WAIT") ? actionType::WAIT : actionType::GO;  
			routeList.push_back(
				newRoute(
					tmp,
					routeItem["time"],
					{routeItem["position"]["x"],routeItem["position"]["y"]}
				)
			);
		}
		newGuard.setRoute(routeList);
		guards.push_back(newGuard);
	}
	
}
