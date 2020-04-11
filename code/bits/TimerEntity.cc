#include "TimerEntity.h"

#include <gf/Coordinates.h>
#include <gf/RenderTarget.h>
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

    std::string timerString = gf::niceNum(m_model.getRemainingTime().asSeconds(), 0.01f);

    unsigned characterSize = coords.getRelativeCharacterSize(0.08f);

    auto position = coords.getRelativePoint({ 0.05f, 0.15f });
    gf::Text timer(timerString, m_font, characterSize);
    timer.setColor(gf::Color::Yellow);
    timer.setOutlineColor(gf::Color::Black);
    timer.setOutlineThickness(characterSize * 0.075f);
    timer.setPosition(position);
    timer.setAnchor(gf::Anchor::BottomLeft);
    target.draw(timer, states);
  }

}

