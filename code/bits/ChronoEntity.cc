#include "ChronoEntity.h"

#include <gf/Coordinates.h>
#include <gf/RenderTarget.h>
#include <gf/StringUtils.h>
#include <gf/Text.h>
#include <gf/VectorOps.h>

#include "TimeAttackData.h"
#include "TimeAttackState.h"

namespace ta {

  ChronoEntity::ChronoEntity(gf::ResourceManager& resources, const TimeAttackData& data, const TimeAttackState& state)
  : m_font(resources.getFont("CodeNewRomanBold.otf"))
  , m_data(data)
  , m_state(state)
  {
  }

  void ChronoEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coords(target);

    auto characterSize = coords.getRelativeCharacterSize(0.05f);
    auto timeSize = coords.getRelativeSize({ 0.18f, 0.06f });

    std::size_t currentStage = m_state.currentStage;
    std::size_t stageCount = m_data.races[m_state.currentRace].stages.size();

    std::size_t cols = stageCount / 8;
    assert(cols == 0 || cols == 1);
    std::size_t lines = stageCount / (cols + 1);

    auto& times = m_state.chrono.getTimes();
    assert(!times.empty());

    auto displayTime = [&](gf::Vector2f position, gf::Color4f color, std::size_t index, gf::Time time) {
      gf::Text stageText(gf::formatString("%02zu", index + 1), m_font, characterSize);
      stageText.setColor(color);
      stageText.setOutlineColor(gf::Color::Black);
      stageText.setOutlineThickness(characterSize * 0.075f);
      stageText.setPosition(position);
      stageText.setAnchor(gf::Anchor::TopLeft);
      target.draw(stageText, states);

      gf::Text timeText(gf::formatString("%.02fs", time.asSeconds()), m_font, characterSize);
      timeText.setColor(color);
      timeText.setOutlineColor(gf::Color::Black);
      timeText.setOutlineThickness(characterSize * 0.075f);
      timeText.setPosition(position + gf::projx(timeSize));
      timeText.setAnchor(gf::Anchor::TopRight);
      target.draw(timeText, states);
    };

    auto displayNoTime = [&](gf::Vector2f position, std::size_t index) {
      gf::Text stageText(gf::formatString("%02zu", index + 1), m_font, characterSize);
      stageText.setColor(gf::Color::Gray());
      stageText.setOutlineColor(gf::Color::Black);
      stageText.setOutlineThickness(characterSize * 0.075f);
      stageText.setPosition(position);
      stageText.setAnchor(gf::Anchor::TopLeft);
      target.draw(stageText, states);

      gf::Text timeText("-", m_font, characterSize);
      timeText.setColor(gf::Color::Gray());
      timeText.setOutlineColor(gf::Color::Black);
      timeText.setOutlineThickness(characterSize * 0.075f);
      timeText.setPosition(position + gf::projx(timeSize));
      timeText.setAnchor(gf::Anchor::TopRight);
      target.draw(timeText, states);
    };

    gf::Vector2f base = coords.getRelativePoint({ 0.5f, 0.4f }) - gf::projx(timeSize) / 2 - cols * gf::projx(timeSize);

    std::size_t index = 0;

    for (; index < times.size() - 1; ++index) {
      auto position = base + (index % lines) * gf::projy(timeSize) + (index / lines) * 2 * gf::projx(timeSize);
      displayTime(position, gf::Color::Green, index, times[index]);
    }

    {
      auto position = base + (index % lines) * gf::projy(timeSize) + (index / lines) * 2 * gf::projx(timeSize);

      if (currentStage == stageCount) {
        displayTime(position, gf::Color::Green, index, times[index]);
      } else {
        displayTime(position, gf::Color::Red, index, times[index]);
      }

      ++index;
    }

    for (; index < stageCount; ++index) {
      auto position = base + (index % lines) * gf::projy(timeSize) + (index / lines) * 2 * gf::projx(timeSize);
      displayNoTime(position, index);
    }

  }

}
