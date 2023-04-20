#ifndef PAUSE_H
#define PAUSE_H
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

class Pause : public gf::Scene {
	private: 
	Manager& managerLink;
	gf::Font& m_font;
	gf::Text titleMenu;
	gf::WidgetContainer buttons;
	gf::TextButtonWidget buttonRestart;
    gf::TextButtonWidget buttonResume; 
	gf::TextButtonWidget buttonRules;
    gf::TextButtonWidget buttonMenu;
	bool pause;
	void setButton(gf::TextButtonWidget &button);

	
	public:
		Pause(gf::Vector2i size,Manager& link);
		bool isPause();
		void setPause(bool var);
		void renderTitle(gf::RenderTarget &target);
		void renderButtons(gf::RenderTarget &target);
		void doProcessEvent(gf::Event& event) override;
		void doRender (gf::RenderTarget &target, const gf::RenderStates &states) override;
	
};

#endif
