#ifndef GAME_H
#define GAME_H
#include <gf/Scene.h>
#include <gf/Math.h>
#include <gf/Time.h>
#include <gf/Action.h>
#include <gf/Views.h>
#include <gf/Widgets.h>
#include <gf/Font.h>
#include <gf/WidgetContainer.h>
#include <gf/Coordinates.h>
#include <gf/Vector.h>
#include <gf/Color.h>
#include "../local/player.h"
#include "../local/level.h"
#include "../local/map.h"
struct Manager;

constexpr gf::Vector2f GAME_SIZE = {500.0, 500.0};

class Game : public gf::Scene {
	private:
		gf::Action echapAction,spaceAction, mAction,rightAction,
		leftAction,upAction,downAction; 
		Manager& managerLink;
		gf::Font& m_font;
		Map map;
		Player player;
		std::vector<std::string> level_list;
		Level level;
		gf::TextWidget m_score;
		gf::TextWidget m_openMap;
		gf::TextButtonWidget m_buttonMap;
		gf::WidgetContainer m_widgets;
		int compteur_niveau;
		int nb_total_levels;
		


	public:
		Game(gf::Vector2i size, Manager& managerLink);
		Level& getLevel();
		Map& getMap();
		Player& getPlayer();
		int counterLevel();
		void setCounterLevel(int var);
		int getNumCurrentLevel();
		int getNumTotalLevels();
		void desactivateActions();
		void doHandleActions(gf::Window & window);
		void doUpdate(gf::Time time);
		void doRender (gf::RenderTarget &target, const gf::RenderStates &states) override;
		void init();
		void changeLevel();
		void reset();
};

#endif
