#ifndef TITLE_H
#define TITLE_H
#include <gf/Scene.h>
#include <gf/Math.h>
#include <gf/Time.h>
#include <gf/Action.h>
#include <gf/Views.h>
#include <gf/Color.h>
#include <string>
#include <gf/Widgets.h>
#include <gf/WidgetContainer.h>
#include <gf/Text.h>
#include <gf/Font.h>
#include <gf/Coordinates.h>

struct Manager;

class Title : public gf::Scene {
	private: 
	Manager& managerLink;
	gf::Font &m_font;
	gf::Text titleMenu;
	gf::WidgetContainer buttons;
	gf::TextButtonWidget buttonStart;
    gf::TextButtonWidget buttonRules; 
    gf::TextButtonWidget buttonQuit;
	void setButton(gf::TextButtonWidget &button);

	
	public:
		Title(gf::Vector2i size,Manager& link);
		void renderTitle(gf::RenderTarget &target);
		void renderButtons(gf::RenderTarget &target);
		void doProcessEvent(gf::Event& event) override;
		void doRender (gf::RenderTarget &target, const gf::RenderStates &states) override;
	
};

#endif
