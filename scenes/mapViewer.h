#ifndef MAP_VIEWER_H
#define MAP_VIEWER_H

#include <gf/Scene.h>
#include <gf/Action.h>
#include <gf/Coordinates.h>
#include <gf/Widgets.h>
#include <gf/WidgetContainer.h>
#include <gf/Font.h>

#include "../local/minimap.h"
#include "../local/player.h"
#include "../local/map.h"

struct Manager;

class MapViewer : public gf::Scene {
	private:
		Manager& m_managerLink;
		gf::Font& m_font;
		Minimap m_miniMap;
        gf::Action m_mAction;
		gf::TextWidget m_closeMap;
		gf::TextButtonWidget m_buttonGame;
		gf::WidgetContainer m_widgets;

	
	public:
		MapViewer(gf::Vector2i size,Manager& link);
        void doHandleActions(gf::Window & window) override;
		void doRender (gf::RenderTarget &target, const gf::RenderStates &states) override;
	
};

#endif
