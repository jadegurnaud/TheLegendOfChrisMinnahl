#include "end.h"
#include "../manager.h"



End::End(gf::Vector2i size,Manager& link)
: Scene(link.getRenderer().getSize())
, m_managerLink(link)
, m_font(m_managerLink.resources.getFont("font/arial.ttf"))
, m_menuButton("Menu", m_font, 20.0)
, m_restartButton("Restart", m_font, 20.0)
, m_nextButton("Next", m_font, 20.0)
, m_level(m_managerLink.gameScene.getLevel())
{
    setClearColor(gf::Color::Gray(0.3f));

    m_won = false;

    //Initialization texts
    this->m_text_win = gf::Text("You won !!", m_font); 
    this->m_text_win.setColor(gf::Color::White);

    this->m_text_lose = gf::Text("Game over", m_font); 
    this->m_text_lose.setColor(gf::Color::White);


    //Initialization buttons
    setButton(this->m_menuButton);
    setButton(this->m_restartButton);
    setButton(this->m_nextButton);

    

}

void End::setButton(gf::TextButtonWidget &button){
    button.setDefaultTextColor(gf::Color::Black);
    button.setDefaultBackgroundColor(gf::Color::White);
    button.setSelectedTextColor(gf::Color::Black);
    button.setSelectedBackgroundColor(gf::Color::Gray(0.7f));
    button.setBackgroundOutlineThickness(2);
    button.setRadius(12.0);
    button.setAnchor(gf::Anchor::TopLeft);
    button.setAlignment(gf::Alignment::Center);
   

}



void End::doProcessEvent(gf::Event& event) {
    gf::MouseButtonEvent &mouseEvent = event.mouseButton;
    switch (event.type) {
        case gf::EventType::MouseButtonPressed:
            if(this->m_menuButton.contains(mouseEvent.coords)){
                    this->m_menuButton.setSelected();
            }else if(this->m_restartButton.contains(mouseEvent.coords)){
                    this->m_restartButton.setSelected();
            }else if(this->m_nextButton.contains(mouseEvent.coords)){
                    this->m_nextButton.setSelected();
            }
            break;
        case gf::EventType::MouseButtonReleased:
            this->m_menuButton.setState(gf::WidgetState::Default);
            this->m_restartButton.setState(gf::WidgetState::Default);
            this->m_nextButton.setState(gf::WidgetState::Default);

            if(this->m_menuButton.contains(mouseEvent.coords)){
                m_managerLink.gameScene.reset();
                m_managerLink.replaceScene(m_managerLink.titleScene);
            }else if(this->m_restartButton.contains(mouseEvent.coords)){
                m_managerLink.gameScene.reset();
                m_managerLink.replaceScene(m_managerLink.gameScene);
            }else if(this->m_nextButton.contains(mouseEvent.coords)){
                m_managerLink.gameScene.reset();
                m_managerLink.gameScene.changeLevel();
                m_managerLink.replaceScene(m_managerLink.gameScene);
            }
            break;
        default:
            break;
    }
}

void End::setLose(){
    m_won=false;
}

void End::setWin(){
    m_won=true;
}

void End::doRender (gf::RenderTarget &target, const gf::RenderStates &states){
    gf::Coordinates coords(target);
    target.setView(getHudView());

    const float characterSize = coords.getRelativeSize(gf::Vector2f(0.05f, 0.05f)).x;
    const float paddingSize = coords.getRelativeSize({0.01f, 0.f}).x;
    const float paragraphWidth = coords.getRelativeSize(gf::Vector2f(0.3f, 0.2f) - 0.05f).x;

    //Render text
    m_widgets.clear();
    if(m_won){
        this->m_text_win.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.1f, 0.1f)).x);
        this->m_text_win.setPosition(coords.getRelativePoint({ 0.5f, 0.3f }));
        this->m_text_win.setAnchor(gf::Anchor::TopCenter);
        target.draw(this->m_text_win);
        if(m_managerLink.gameScene.counterLevel()<=m_managerLink.gameScene.getNumTotalLevels()){
            m_nextButton.setCharacterSize(characterSize);
            m_nextButton.setAnchor(gf::Anchor::TopRight);
            m_nextButton.setPosition(coords.getRelativePoint({0.8f, 0.6f}));
            m_nextButton.setParagraphWidth(paragraphWidth);
            m_nextButton.setPadding(paddingSize);
            this->m_widgets.addWidget(m_nextButton);
        }
    }else{
        this->m_text_lose.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.1f, 0.1f)).x);
        this->m_text_lose.setPosition(coords.getRelativePoint({ 0.5f, 0.3f }));
        this->m_text_lose.setAnchor(gf::Anchor::TopCenter);
        target.draw(this->m_text_lose);
    }


    //Render buttons

    m_restartButton.setCharacterSize(characterSize);
    m_restartButton.setAnchor(gf::Anchor::TopLeft);
    m_restartButton.setPosition(coords.getRelativePoint({0.2f, 0.6f}));
    m_restartButton.setParagraphWidth(paragraphWidth);
    m_restartButton.setPadding(paddingSize);

    m_menuButton.setCharacterSize(characterSize);
    if(m_managerLink.gameScene.counterLevel()<=m_managerLink.gameScene.getNumTotalLevels() && m_won){
        m_menuButton.setAnchor(gf::Anchor::Center);
        m_menuButton.setPosition(coords.getRelativePoint({0.5f, 0.75f}));
    }else{
        m_menuButton.setAnchor(gf::Anchor::TopRight);
        m_menuButton.setPosition(coords.getRelativePoint({0.8f, 0.6f}));
    }
    m_menuButton.setParagraphWidth(paragraphWidth);
    m_menuButton.setPadding(paddingSize);
    
    this->m_widgets.addWidget(m_restartButton);
    this->m_widgets.addWidget(m_menuButton);
    m_widgets.render(target);
} 