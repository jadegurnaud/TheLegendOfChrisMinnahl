#include "pause.h"
#include <iostream>

#include "../manager.h"

Pause::Pause(gf::Vector2i size,Manager& link) 
: Scene(link.getRenderer().getSize())
, managerLink(link)
, m_font(managerLink.resources.getFont("font/arial.ttf"))
, buttonRestart("Restart", m_font)
, buttonResume("Resume", m_font)
, buttonRules("Rules", m_font)
, buttonMenu("Menu", m_font){
	setClearColor(gf::Color::Black);

    this->pause=false;

	//Title
	this->titleMenu = gf::Text("Pause", m_font); 
    this->titleMenu.setColor(gf::Color::White);

	
    //Button
	setButton(this->buttonRestart);
    setButton(this->buttonResume);
    setButton(this->buttonRules);
    setButton(this->buttonMenu);
	
	
}

void Pause::setButton(gf::TextButtonWidget &button){
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

bool Pause::isPause(){
	return pause;
}

void Pause::setPause(bool var){
    pause = var;
}

void Pause::renderTitle(gf::RenderTarget &target){
	gf::Coordinates coords(target);
	this->titleMenu.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.07f, 0.07f)).x);
	this->titleMenu.setPosition(coords.getRelativePoint({ 0.5f, 0.23f }));
	this->titleMenu.setAnchor(gf::Anchor::TopCenter);
	
	target.draw(this->titleMenu);

}

void Pause::renderButtons(gf::RenderTarget &target){
    gf::Coordinates coords(target);

    constexpr float characterSize = 0.02f;
    constexpr float spaceBetweenButton = 0.07f;
    const float paddingSize = coords.getRelativeSize({0.01f, 0.f}).x;
    
	this->buttonRestart.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.02f, 0.02f)).x);
    this->buttonRestart.setPosition(coords.getRelativePoint({0.5f, 0.42f + characterSize + spaceBetweenButton}));
    this->buttonRestart.setAnchor(gf::Anchor::TopCenter);
    this->buttonRestart.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.17f, 0.1f) - 0.05f).x);
    this->buttonRestart.setPadding(paddingSize);

    this->buttonResume.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.02f, 0.02f)).x);
    this->buttonResume.setPosition(coords.getRelativePoint({0.5f, 0.42f}));
    this->buttonResume.setAnchor(gf::Anchor::TopCenter);
    this->buttonResume.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.17f, 0.1f) - 0.05f).x);
    this->buttonResume.setPadding(paddingSize);

    this->buttonRules.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.02f, 0.02f)).x);
    this->buttonRules.setPosition(coords.getRelativePoint({0.5f, 0.42f + (characterSize + spaceBetweenButton) * 2}));
    this->buttonRules.setAnchor(gf::Anchor::TopCenter);
    this->buttonRules.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.17f, 0.1f) - 0.05f).x);
    this->buttonRules.setPadding(paddingSize);

    this->buttonMenu.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.02f, 0.02f)).x);
    this->buttonMenu.setPosition(coords.getRelativePoint({0.5f, 0.42f + (characterSize + spaceBetweenButton) * 3}));
    this->buttonMenu.setAnchor(gf::Anchor::TopCenter);
    this->buttonMenu.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.17f, 0.1f) - 0.05f).x);
    this->buttonMenu.setPadding(paddingSize);

	target.draw(this->buttonRestart);
    target.draw(this->buttonResume);
    target.draw(this->buttonRules);
    target.draw(this->buttonMenu);
}

void Pause::doProcessEvent(gf::Event& event) {
    gf::MouseButtonEvent &mouseEvent = event.mouseButton;
    switch (event.type) {
        case gf::EventType::MouseButtonPressed:
            if(this->buttonRestart.contains(mouseEvent.coords)){
                this->buttonRestart.setSelected();
            }else if(this->buttonResume.contains(mouseEvent.coords)){
                this->buttonResume.setSelected();
            }else if(this->buttonRules.contains(mouseEvent.coords)){
                this->buttonRules.setSelected();
            }else if(this->buttonMenu.contains(mouseEvent.coords)){
                this->buttonMenu.setSelected();
            }
            break;
        case gf::EventType::MouseButtonReleased:
            this->buttonRestart.setState(gf::WidgetState::Default );
            this->buttonResume.setState(gf::WidgetState::Default );
            this->buttonRules.setState(gf::WidgetState::Default );
            this->buttonMenu.setState(gf::WidgetState::Default );


            if(this->buttonRestart.contains(mouseEvent.coords)){
                managerLink.gameScene.reset();
                managerLink.replaceAllScenes(managerLink.gameScene);
            }else if(this->buttonResume.contains(mouseEvent.coords)){
                managerLink.popScene();
                managerLink.gameScene.resume();
            }else if(this->buttonRules.contains(mouseEvent.coords)){
                setPause(true);
                managerLink.replaceAllScenes(managerLink.rulesScene);
            }else if(this->buttonMenu.contains(mouseEvent.coords)){
              
                managerLink.gameScene.reset();
                managerLink.replaceAllScenes(managerLink.titleScene);
            }
            break;
        default:
            break;
    }
}

void Pause::doRender (gf::RenderTarget &target, const gf::RenderStates &states){
    target.setView(getHudView());
    gf::Coordinates coords(target);
    gf::RoundedRectangleShape shape(coords.getRelativeSize(gf::Vector2f(0.5f, 0.6f)));
    shape.setColor(gf::Color4f({0.1,0.1,0.1,0.5}));
    shape.setAnchor(gf::Anchor::Center);
    shape.setOutlineColor(gf::Color::Black);
    shape.setOutlineThickness(5);
    shape.setRadius(10);
    shape.setPosition(coords.getRelativePoint({0.5f, 0.5f}));
	target.draw(shape);
    renderTitle(target);
    renderButtons(target);
}