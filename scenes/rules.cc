#include "rules.h"
#include "pause.h"
#include "../manager.h"



Rules::Rules(gf::Vector2i size,Manager& link) 
: Scene(link.getRenderer().getSize())
, m_managerLink(link)
, m_font(m_managerLink.resources.getFont("font/arial.ttf"))
, m_returnButton("Return", m_font, 20.0)
, m_statue_texture(m_managerLink.resources.getTexture(m_managerLink.resources.getAbsolutePath("sprites/wall/socle_statue.png")))
, m_arrows_texture(m_managerLink.resources.getTexture(m_managerLink.resources.getAbsolutePath("sprites/rules/fleches.png")))
, m_echap_texture(m_managerLink.resources.getTexture(m_managerLink.resources.getAbsolutePath("sprites/rules/echap.png")))
, m_object_texture(m_managerLink.resources.getTexture(m_managerLink.resources.getAbsolutePath("sprites/wall/object_not_found.png")))
, m_end_texture(m_managerLink.resources.getTexture(m_managerLink.resources.getAbsolutePath("sprites/wall/end.png")))
{
	setClearColor(gf::Color::Gray(0.1f));


    //Title
	this->m_title = gf::Text("Rules", m_font); 
    this->m_title.setColor(gf::Color::White);


    //Button
    this->m_returnButton.setDefaultTextColor(gf::Color::Black);
    this->m_returnButton.setDefaultBackgroundColor(gf::Color::White);
    this->m_returnButton.setSelectedTextColor(gf::Color::Black);
    this->m_returnButton.setSelectedBackgroundColor(gf::Color::Gray(0.7f));
    this->m_returnButton.setBackgroundOutlineThickness(2);
    this->m_returnButton.setRadius(12.0);
    this->m_returnButton.setAnchor(gf::Anchor::TopLeft);
    this->m_returnButton.setAlignment(gf::Alignment::Center);
    m_widgets.addWidget(this->m_returnButton);

    //Rules
    /*std::ifstream rulesFile (m_managerLink.resources.getAbsolutePath("game_rules.txt"));
    std::string rules;

    if (rulesFile.is_open()) {
        while (rulesFile) {
        std::string line;
            std::getline (rulesFile, line);
            rules+=line+"\n";
        }
    }else {
        std::cout << "Couldn't open file\n";
    }
    */
    
    this->m_rules1 = gf::Text("to move", m_font); 
    this->m_rules1.setColor(gf::Color::White);
    this->m_rules2 = gf::Text("press space to hide", m_font); 
    this->m_rules2.setColor(gf::Color::White);
    this->m_rules3 = gf::Text("steal it", m_font); 
    this->m_rules3.setColor(gf::Color::White);
    this->m_rules4 = gf::Text("pause menu", m_font); 
    this->m_rules4.setColor(gf::Color::White);
    this->m_rules5 = gf::Text("escape", m_font); 
    this->m_rules5.setColor(gf::Color::White);
}

void Rules::renderTitle(gf::RenderTarget &target){
    gf::Coordinates coords(target);
    this->m_title.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.07f, 0.07f)).x);
    this->m_title.setPosition(coords.getRelativePoint({ 0.5f, 0.1f }));
    this->m_title.setAnchor(gf::Anchor::TopCenter);

    target.draw(this->m_title);
}

void Rules::renderButton(gf::RenderTarget &target){
    gf::Coordinates coords(target);
    this->m_returnButton.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    this->m_returnButton.setPosition(coords.getRelativePoint({0.8f, 0.05f}));
    this->m_returnButton.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.2f, 0.1f) - 0.05f).x);
    this->m_returnButton.setPadding(coords.getRelativeSize({0.01f, 0.f}).x);

    target.draw(this->m_returnButton);
}

void Rules::renderRules(gf::RenderTarget &target){
    gf::Coordinates coords(target);
    constexpr float characterSize = 0.03f;
    constexpr float spaceBetweenRules = 0.11f;

    m_arrows_sprite.setAnchor(gf::Anchor::Center);
    m_arrows_sprite.setPosition(coords.getRelativePoint({ 0.4f, 0.35f}));
    m_arrows_sprite.setTexture(m_arrows_texture);
    m_arrows_sprite.setScale(0.5);
    target.draw(m_arrows_sprite);
    this->m_rules1.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    this->m_rules1.setPosition(coords.getRelativePoint({ 0.52f, 0.35f }));
    this->m_rules1.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.9f, 0.9f) - 0.05f).x);
    this->m_rules1.setAnchor(gf::Anchor::Center);
    target.draw(this->m_rules1);

    m_echap_sprite.setAnchor(gf::Anchor::Center);
    m_echap_sprite.setPosition(coords.getRelativePoint({ 0.4f, 0.35f + characterSize + spaceBetweenRules}));
    m_echap_sprite.setTexture(m_echap_texture);
    m_echap_sprite.setScale(0.2);
    target.draw(m_echap_sprite);
    this->m_rules4.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    this->m_rules4.setPosition(coords.getRelativePoint({ 0.55f, 0.35f + characterSize + spaceBetweenRules}));
    this->m_rules4.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.9f, 0.9f) - 0.05f).x);
    this->m_rules4.setAnchor(gf::Anchor::Center);

    target.draw(this->m_rules4);

    m_statue_sprite.setAnchor(gf::Anchor::Center);
    m_statue_sprite.setPosition(coords.getRelativePoint({ 0.4f, 0.35f + (characterSize + spaceBetweenRules)* 2}));
    m_statue_sprite.setTexture(m_statue_texture);
    m_statue_sprite.setScale(1);
    target.draw(m_statue_sprite);
    this->m_rules2.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    this->m_rules2.setPosition(coords.getRelativePoint({ 0.6f, 0.35f + (characterSize + spaceBetweenRules)* 2}));
    this->m_rules2.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.9f, 0.9f) - 0.05f).x);
    this->m_rules2.setAnchor(gf::Anchor::Center);
    target.draw(this->m_rules2);

    m_object_sprite.setAnchor(gf::Anchor::Center);
    m_object_sprite.setPosition(coords.getRelativePoint({ 0.4f, 0.35f + (characterSize + spaceBetweenRules)* 3}));
    m_object_sprite.setTexture(m_object_texture);
    m_object_sprite.setScale(1);
    target.draw(m_object_sprite);
    this->m_rules3.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    this->m_rules3.setPosition(coords.getRelativePoint({ 0.515f, 0.35f + (characterSize + spaceBetweenRules)* 3}));
    this->m_rules3.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.9f, 0.9f) - 0.05f).x);
    this->m_rules3.setAnchor(gf::Anchor::Center);
    target.draw(this->m_rules3);

    m_end_sprite.setAnchor(gf::Anchor::Center);
    m_end_sprite.setPosition(coords.getRelativePoint({ 0.4f, 0.35f + (characterSize + spaceBetweenRules)* 4}));
    m_end_sprite.setTexture(m_end_texture);
    m_end_sprite.setScale(1);
    target.draw(m_end_sprite);
    this->m_rules5.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
    this->m_rules5.setPosition(coords.getRelativePoint({ 0.515f, 0.35f + (characterSize + spaceBetweenRules)* 4}));
    this->m_rules5.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.9f, 0.9f) - 0.05f).x);
    this->m_rules5.setAnchor(gf::Anchor::Center);
    target.draw(this->m_rules5);


}


void Rules::doProcessEvent(gf::Event& event) {
    gf::MouseButtonEvent &mouseEvent = event.mouseButton;
    switch (event.type) {
        case gf::EventType::MouseButtonPressed:
            if(this->m_returnButton.contains(mouseEvent.coords)){
                    this->m_returnButton.setSelected();
            }
            break;
        case gf::EventType::MouseButtonReleased:
            this->m_returnButton.setState(gf::WidgetState::Default );

            if(this->m_returnButton.contains(mouseEvent.coords)){
                if(m_managerLink.pauseScene.isPause()==true){
                    m_managerLink.popScene();
                    m_managerLink.pushScene(m_managerLink.gameScene);
                    m_managerLink.pushScene(m_managerLink.pauseScene);
                }else{
                    m_managerLink.replaceScene(m_managerLink.titleScene);
                }
            }
            break;
        default:
            break;
    }
}

void Rules::doRender (gf::RenderTarget &target, const gf::RenderStates &states){
    target.setView(getHudView());
    renderTitle(target);
    renderButton(target);
    renderRules(target);
}
