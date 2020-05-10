#include "ResultEntity.h"

#include <gf/Text.h>
#include <gf/RenderTarget.h>
#include <gf/Coordinates.h>

#include "TimeAttackData.h"
#include "TimeAttackState.h"

namespace ta {

  ResultEntity::ResultEntity(gf::ResourceManager& resources, const TimeAttackData& data, const TimeAttackState& state)
  : m_font(resources.getFont("TovariSans.otf"))
  , m_data(data)
  , m_state(state)
  {
  }

  void ResultEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coords(target);

    auto position = coords.getRelativePoint({ 0.5f, 0.1f });
    auto characterSize = coords.getRelativeCharacterSize(0.1f);
    auto screenSize = coords.getRelativeSize({ 1.0f, 1.0f });

    gf::Text text;
    text.setCharacterSize(characterSize);
    text.setAlignment(gf::Alignment::Center);
    text.setParagraphWidth(screenSize.width);

    if (m_state.currentStage == m_data.races[m_state.currentRace].stages.size()) {
      // Win
      text.setString("Congratulations!\nYou won!");
    } else {
      // Fail
      text.setString("So close!\nTry again!");
    }

    text.setColor(gf::Color::Yellow);
    text.setOutlineColor(gf::Color::Black);
    text.setOutlineThickness(characterSize * 0.05f);
    text.setFont(m_font);
    text.setPosition(position);
    text.setAnchor(gf::Anchor::TopCenter);
    target.draw(text, states);
  }

}
