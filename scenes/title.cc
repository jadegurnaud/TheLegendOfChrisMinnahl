#include "title.h"
#include <iostream>
#include <gf/Log.h>

#include "../manager.h"

Title::Title(gf::Vector2i size,Manager& link) 
: Scene(link.getRenderer().getSize())
, managerLink(link)
, m_font(managerLink.resources.getFont("font/arial.ttf"))
, buttonStart("Start", m_font, 30.0)
, buttonRules("Rules", m_font, 30.0)
, buttonQuit("Quit", m_font, 30.0)
{
	setClearColor(gf::Color::Gray(0.1f));
	
	//Title
	this->titleMenu = gf::Text("The Legend Of Chris Minnahl", m_font); 
    this->titleMenu.setColor(gf::Color::White);

	
    //Button
	setButton(this->buttonStart);
    setButton(this->buttonRules);
    setButton(this->buttonQuit);
	
	
}

void Title::setButton(gf::TextButtonWidget &button){
    button.setDefaultTextColor(gf::Color::Black);
    button.setDefaultBackgroundColor(gf::Color::White);
    button.setSelectedTextColor(gf::Color::Black);
    button.setSelectedBackgroundColor(gf::Color::Gray(0.7f));
    button.setBackgroundOutlineThickness(2);
    button.setRadius(12.0);
    button.setAnchor(gf::Anchor::TopLeft);
    button.setAlignment(gf::Alignment::Center);
    this->buttons.addWidget(button);

}

void Title::renderTitle(gf::RenderTarget &target){
	gf::Coordinates coords(target);
	this->titleMenu.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.05f, 0.05f)).x);
	this->titleMenu.setPosition(coords.getRelativePoint({ 0.5f, 0.1f }));
	this->titleMenu.setAnchor(gf::Anchor::TopCenter);
	
	target.draw(this->titleMenu);

}

void Title::renderButtons(gf::RenderTarget &target){
    gf::Coordinates coords(target);

    constexpr float characterSize = 0.03f;
    constexpr float spaceBetweenButton = 0.14f;
    const float paddingSize = coords.getRelativeSize({0.02f, 0.f}).x;
    
	this->buttonStart.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    this->buttonStart.setPosition(coords.getRelativePoint({0.5f, 0.40f}));
    this->buttonStart.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.3f, 0.f) - 0.05f).x);
    this->buttonStart.setAnchor(gf::Anchor::Center);
    this->buttonStart.setPadding(paddingSize);

    this->buttonRules.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    this->buttonRules.setPosition(coords.getRelativePoint({0.5f, 0.40f + characterSize + spaceBetweenButton}));
    this->buttonRules.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.3f, 0.1f) - 0.05f).x);
    this->buttonRules.setAnchor(gf::Anchor::Center);
    this->buttonRules.setPadding(paddingSize);

   this->buttonQuit.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
   this->buttonQuit.setPosition(coords.getRelativePoint({0.5f, 0.40f + (characterSize + spaceBetweenButton) * 2}));
   this->buttonQuit.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.3f, 0.1f) - 0.05f).x);
   this->buttonQuit.setAnchor(gf::Anchor::Center);
   this->buttonQuit.setPadding(paddingSize);

	target.draw(this->buttonStart);
    target.draw(this->buttonRules);
    target.draw(this->buttonQuit);
}

void Title::doProcessEvent(gf::Event& event) {
    gf::MouseButtonEvent &mouseEvent = event.mouseButton;
    switch (event.type) {
        case gf::EventType::MouseButtonPressed:
            if(this->buttonStart.contains(mouseEvent.coords)){
                this->buttonStart.setSelected();
            }else if(this->buttonRules.contains(mouseEvent.coords)){
                this->buttonRules.setSelected();
            }else if(this->buttonQuit.contains(mouseEvent.coords)){
                this->buttonQuit.setSelected();
            }
            break;
        case gf::EventType::MouseButtonReleased:
            this->buttonStart.setState(gf::WidgetState::Default );
            this->buttonRules.setState(gf::WidgetState::Default );
            this->buttonQuit.setState(gf::WidgetState::Default );

            if(this->buttonStart.contains(mouseEvent.coords)){
                managerLink.gameScene.init();
                managerLink.replaceScene(managerLink.gameScene);
            }else if(this->buttonRules.contains(mouseEvent.coords)){
                managerLink.pauseScene.setPause(false);
                managerLink.replaceScene(managerLink.rulesScene);
            }else if(this->buttonQuit.contains(mouseEvent.coords)){
                managerLink.getWindow().close();
            }
            break;
        default:
            break;
    }
}

void Title::doRender (gf::RenderTarget &target, const gf::RenderStates &states){
    target.setView(getHudView());
    renderTitle(target);
    renderButtons(target);
}