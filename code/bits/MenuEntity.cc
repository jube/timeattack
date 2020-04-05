#include "MenuEntity.h"

#include <gf/Coordinates.h>
#include <gf/RenderTarget.h>
#include <gf/Text.h>

namespace ta {

  MenuEntity::MenuEntity(gf::ResourceManager& resources, MenuChoice& choice)
  : m_font(resources.getFont("TovariSans.otf"))
  , m_startWidget("Start", m_font)
  , m_helpWidget("Help", m_font)
  , m_creditsWidget("Credits", m_font)
  , m_quitWidget("Quit", m_font)
  {
    m_startWidget.setCallback([&choice]() { choice = MenuChoice::Start; });
    m_container.addWidget(m_startWidget);

    m_helpWidget.setCallback([&choice]() { choice = MenuChoice::Help; });
    m_container.addWidget(m_helpWidget);

    m_creditsWidget.setCallback([&choice]() { choice = MenuChoice::Credits; });
    m_container.addWidget(m_creditsWidget);

    m_quitWidget.setCallback([&choice]() { choice = MenuChoice::Quit; });
    m_container.addWidget(m_quitWidget);

  }

  void MenuEntity::pointTo(gf::Vector2f coords) {
    m_container.pointTo(coords);
  }

  void MenuEntity::triggerAction() {
    m_container.triggerAction();
  }

  void MenuEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coords(target);

    unsigned logoCharacterSize = coords.getRelativeCharacterSize(0.15f);

    auto logoPosition = coords.getRelativePoint({ 0.5f, 0.2f });
    gf::Text logo("Time Attack!", m_font, logoCharacterSize);
    logo.setColor(gf::Color::Yellow); // gf::Color::fromRgba32(0x31, 0x8C, 0xE7)
    logo.setOutlineColor(gf::Color::Black);
    logo.setOutlineThickness(logoCharacterSize * 0.05f);
    logo.setPosition(logoPosition);
    logo.setAnchor(gf::Anchor::Center);
    target.draw(logo, states);

    unsigned characterSize = coords.getRelativeCharacterSize(0.1f);
    auto selectedColor = gf::Color::darker(gf::Color::Green, 0.3f);

    auto startPosition = coords.getRelativePoint({ 0.5f, 0.4f });
    m_startWidget.setCharacterSize(characterSize);
    m_startWidget.setAnchor(gf::Anchor::Center);
    m_startWidget.setPosition(startPosition);
    m_startWidget.setDefaultTextColor(gf::Color::White);
    m_startWidget.setDefaultTextOutlineColor(gf::Color::Black);
    m_startWidget.setSelectedTextColor(selectedColor);
    m_startWidget.setSelectedTextOutlineColor(gf::Color::Black);
    m_startWidget.setTextOutlineThickness(characterSize * 0.05f);
    target.draw(m_startWidget, states);

    auto helpPosition = coords.getRelativePoint({ 0.5f, 0.5f });
    m_helpWidget.setCharacterSize(characterSize);
    m_helpWidget.setAnchor(gf::Anchor::Center);
    m_helpWidget.setPosition(helpPosition);
    m_helpWidget.setDefaultTextColor(gf::Color::White);
    m_helpWidget.setDefaultTextOutlineColor(gf::Color::Black);
//     m_helpWidget.setSelectedTextColor(selectedColor);
    m_helpWidget.setSelectedTextOutlineColor(gf::Color::Black);
    m_helpWidget.setTextOutlineThickness(characterSize * 0.05f);
    target.draw(m_helpWidget, states);

    auto creditsPosition = coords.getRelativePoint({ 0.5f, 0.6f });
    m_creditsWidget.setCharacterSize(characterSize);
    m_creditsWidget.setAnchor(gf::Anchor::Center);
    m_creditsWidget.setPosition(creditsPosition);
    m_creditsWidget.setDefaultTextColor(gf::Color::White);
    m_creditsWidget.setDefaultTextOutlineColor(gf::Color::Black);
//     m_creditsWidget.setSelectedTextColor(selectedColor);
    m_creditsWidget.setSelectedTextOutlineColor(gf::Color::Black);
    m_creditsWidget.setTextOutlineThickness(characterSize * 0.05f);
    target.draw(m_creditsWidget, states);

    auto quitPosition = coords.getRelativePoint({ 0.5f, 0.7f });
    m_quitWidget.setCharacterSize(characterSize);
    m_quitWidget.setAnchor(gf::Anchor::Center);
    m_quitWidget.setPosition(quitPosition);
    m_quitWidget.setDefaultTextColor(gf::Color::White);
    m_quitWidget.setDefaultTextOutlineColor(gf::Color::Black);
    m_quitWidget.setSelectedTextColor(gf::Color::Red);
    m_quitWidget.setSelectedTextOutlineColor(gf::Color::Black);
    m_quitWidget.setTextOutlineThickness(characterSize * 0.05f);
    target.draw(m_quitWidget, states);
  }


}


