#include "TimerEntity.h"

#include <gf/Coordinates.h>
#include <gf/Curves.h>
#include <gf/RenderTarget.h>
#include <gf/Shapes.h>
#include <gf/StringUtils.h>
#include <gf/Text.h>

#include "TimerModel.h"

namespace ta {

  TimerEntity::TimerEntity(gf::ResourceManager& resources, TimerModel& model)
  : m_font(resources.getFont("CodeNewRomanBold.otf"))
  , m_model(model)
  {
  }

  void TimerEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coords(target);

    float seconds = m_model.getRemainingTime().asSeconds();

    std::string timerString = seconds <= 0.0f ? "0.00" : gf::niceNum(seconds, 0.01f);

    unsigned characterSize = coords.getRelativeCharacterSize(0.08f);

    auto position = coords.getRelativePoint({ 0.1f, 0.1f });
    gf::Text timer(timerString, m_font, characterSize);
    timer.setColor(gf::Color::Yellow);
    timer.setOutlineColor(gf::Color::Black);
    timer.setOutlineThickness(characterSize * 0.075f);
    timer.setPosition(position);
    timer.setAnchor(gf::Anchor::BottomCenter);
    target.draw(timer, states);

    position = coords.getRelativePoint({ 0.1f, 0.25f });
    auto radius = coords.getRelativeSize({ 0.0f, 0.1f }).height;

    gf::CircleShape clock(radius, 60);
    clock.setColor(gf::Color::Black * gf::Color::Opaque(0.5f));
    clock.setOutlineColor(gf::Color::Yellow);
    clock.setOutlineThickness(characterSize * 0.05f);
    clock.setPosition(position);
    clock.setAnchor(gf::Anchor::Center);
    target.draw(clock, states);

    float angle = - gf::Pi2 - seconds / 60.0f * 2.0f * gf::Pi;

    gf::Pie pie(radius, angle, - gf::Pi2);
    pie.setColor(gf::Color::Black);
    pie.setPosition(position);
    pie.setAnchor(gf::Anchor::Center);
    target.draw(pie, states);

    gf::Line handle(position, position + gf::unit(angle) * radius * 0.8f);
    handle.setWidth(characterSize * 0.05f);
    handle.setColor(gf::Color::Yellow);
    target.draw(handle, states);
  }

}

