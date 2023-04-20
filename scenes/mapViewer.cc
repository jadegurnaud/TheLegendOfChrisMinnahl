#include "mapViewer.h"
#include "../manager.h"

MapViewer::MapViewer(gf::Vector2i size,Manager& link)
: Scene(link.getRenderer().getSize())
, m_managerLink(link)
, m_font(m_managerLink.resources.getFont("font/arial.ttf"))
, m_miniMap(m_managerLink.gameScene, m_managerLink.resources)
, m_mAction("Close map")
, m_closeMap("Close map", m_font, 25)
, m_buttonGame("M", m_font, 25)
{
    
    setClearColor(gf::Color::Gray(0.2f));

    m_mAction.addKeycodeKeyControl(gf::Keycode::M);
    m_mAction.setInstantaneous();
	addAction(m_mAction);

	m_buttonGame.setDefaultTextColor(gf::Color::Black);
    m_buttonGame.setDefaultBackgroundColor(gf::Color::White);
    m_buttonGame.setSelectedTextColor(gf::Color::Black);
    m_buttonGame.setSelectedBackgroundColor(gf::Color::Gray(0.7f));
    m_buttonGame.setBackgroundOutlineThickness(2);
    m_buttonGame.setRadius(12.0);
    m_buttonGame.setAnchor(gf::Anchor::BottomLeft);
    m_buttonGame.setAlignment(gf::Alignment::Center);
    m_widgets.addWidget(m_buttonGame);

	m_closeMap.setDefaultTextColor(gf::Color::White);
    m_closeMap.setSelectedTextColor(gf::Color::White);
    m_closeMap.setAnchor(gf::Anchor::BottomLeft);
	m_widgets.addWidget(m_closeMap);

    addWorldEntity(m_miniMap);
    

}

void MapViewer::doHandleActions(gf::Window & window){
	if(m_mAction.isActive()){
        m_managerLink.replaceScene(m_managerLink.gameScene);
	}
}

void MapViewer::doRender (gf::RenderTarget &target, const gf::RenderStates &states){
    setWorldViewCenter(m_miniMap.getSize()/2);
    setWorldViewSize(m_miniMap.getSize());

    renderWorldEntities(target,states);
    renderHudEntities(target,states);

    //Fermer map
    gf::Coordinates coords(target);
	m_closeMap.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.02f, 0.02f)).x);
    m_closeMap.setPosition(coords.getRelativePoint({0.09f, 0.95f}));
	target.draw(m_closeMap);

	m_buttonGame.setCharacterSize(coords.getRelativeSize(gf::Vector2f(0.03f, 0.03f)).x);
	m_buttonGame.setParagraphWidth(coords.getRelativeSize(gf::Vector2f(0.1f, 0.1f) - 0.1f).x);
    m_buttonGame.setPadding(coords.getRelativeSize({0.01f, 0.01f}).x);
    m_buttonGame.setPosition(coords.getRelativePoint({0.05f, 0.95}));
	target.draw(m_buttonGame);
}
