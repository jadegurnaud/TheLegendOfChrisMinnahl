#ifndef RULES_H
#define RULES_H

#include <iostream>
#include <fstream>
#include <string>

#include <gf/Color.h>
#include <gf/Text.h>
#include <gf/Widgets.h>
#include <gf/Scene.h>
#include <gf/Math.h>
#include <gf/Time.h>
#include <gf/Action.h>
#include <gf/Font.h>
#include <gf/Coordinates.h>
#include <gf/WidgetContainer.h>
#include <gf/Sprite.h>


struct Manager;

class Rules : public gf::Scene {
	private:
		Manager& m_managerLink;
		gf::Font& m_font;
		gf::Text m_title; 
    	gf::Text m_rules1;
		gf::Text m_rules2;
		gf::Text m_rules3;
		gf::Text m_rules4;
		gf::Text m_rules5;
		gf::Texture & m_statue_texture;
		gf::Sprite m_statue_sprite;
		gf::Texture & m_arrows_texture;
		gf::Sprite m_arrows_sprite;
		gf::Texture & m_echap_texture;
		gf::Sprite m_echap_sprite;
		gf::Texture & m_object_texture;
		gf::Sprite m_object_sprite;
		gf::Texture & m_end_texture;
		gf::Sprite m_end_sprite;
		gf::TextButtonWidget m_returnButton;
		gf::WidgetContainer m_widgets;

	
	public:
		Rules(gf::Vector2i size,Manager& link);
		void renderTitle(gf::RenderTarget &target);
		void renderButton(gf::RenderTarget &target);
		void renderRules(gf::RenderTarget &target);
		void printRules();
		void doProcessEvent(gf::Event& event) override;
		void doRender (gf::RenderTarget &target, const gf::RenderStates &states) override;
	
};

#endif
