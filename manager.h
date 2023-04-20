#ifndef MANAGER_H
#define MANAGER_H
#include "config.h"
#include <gf/GameManager.h>
#include "scenes/rules.h"
#include "scenes/title.h"
#include "scenes/end.h"
#include "scenes/game.h"
#include "scenes/pause.h"
#include "scenes/mapViewer.h"
constexpr gf::Vector2i WINDOW_SIZE = {1422, 800};

class Manager : public gf::GameManager{
	public :
	Manager(std::string window_title);
	Title titleScene;
	Rules rulesScene;
	Game gameScene;
	Pause pauseScene;
	MapViewer mapScene;
	End endScene;
};





#endif
