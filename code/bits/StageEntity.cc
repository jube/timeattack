#include "StageEntity.h"

#include <gf/RenderTarget.h>
#include <gf/Shapes.h>

#include "TimeAttackData.h"
#include "TimeAttackState.h"

#include "Settings.h"

namespace ta {

  StageEntity::StageEntity(TimeAttackData& data, const TimeAttackState& state, Which which)
  : m_data(data)
  , m_state(state)
  , m_which(which)
  {

  }

  void StageEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    assert(m_state.currentRace < m_data.races.size());
    auto& race = m_data.races[m_state.currentRace];

    auto currentStage = m_state.currentStage;

    if (m_which == Previous) {
      assert(currentStage > 0);
      --currentStage;
    }

    assert(currentStage < race.stages.size());
    auto& stage = race.stages[currentStage];

    auto terrain = m_data.findTerrain(race.ground);
    assert(terrain != nullptr);

    gf::Vector2f base = gf::vec(12, 12) * TileSize;
    terrain->tiles.setOrigin(base);
    target.draw(terrain->tiles, states);

    target.draw(stage.tiles, states);

#if 0
    gf::CircleShape shape(TargetDistance);
    shape.setColor(gf::Color::Transparent);
    shape.setOutlineColor(gf::Color::Red);
    shape.setOutlineThickness(2.0f);
    shape.setPosition(getTarget(stage.finish));
    shape.setAnchor(gf::Anchor::Center);
    target.draw(shape);
#endif
  }

}
