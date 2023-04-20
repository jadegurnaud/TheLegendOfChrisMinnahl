#include "manager.h"
#include <gf/Text.h>



Manager::Manager(std::string window_title) 
: GameManager(window_title,{MANAGER_DATA_DIR})
, gameScene(WINDOW_SIZE,*this)
, titleScene(WINDOW_SIZE,*this)
, rulesScene(WINDOW_SIZE,*this)
, pauseScene(WINDOW_SIZE,*this)
, mapScene(WINDOW_SIZE,*this)
, endScene(WINDOW_SIZE,*this){

	getWindow().setSize(WINDOW_SIZE);
	pushScene(titleScene);
	resources.addSearchDir(MANAGER_DATA_DIR);

}

