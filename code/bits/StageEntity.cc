#include "StageEntity.h"

#include <gf/Curves.h>
#include <gf/RenderTarget.h>
#include <gf/Shapes.h>

#include "TimeAttackData.h"
#include "TimeAttackState.h"

#include "Settings.h"

namespace ta {

  namespace {

    gf::Vector2f getStageOffset(StageLimit limit) {
      switch (limit) {
        case StageLimit::LeftTop:
        case StageLimit::LeftCenter:
        case StageLimit::LeftBottom:
          return -1.0f * gf::dirx(TileExtent * GroundExtent);
        case StageLimit::TopLeft:
        case StageLimit::TopCenter:
        case StageLimit::TopRight:
          return -1.0f * gf::diry(TileExtent * GroundExtent);
        case StageLimit::RightTop:
        case StageLimit::RightCenter:
        case StageLimit::RightBottom:
          return 1.0f * gf::dirx(TileExtent * GroundExtent);
        case StageLimit::BottomLeft:
        case StageLimit::BottomCenter:
        case StageLimit::BottomRight:
          return 1.0f * gf::diry(TileExtent * GroundExtent);
      }

      assert(false);
      return gf::vec(0.0f, 0.0f);
    }

  }

  StageEntity::StageEntity(TimeAttackData& data, const TimeAttackState& state, Which which)
  : gf::Entity(-5)
  , m_data(data)
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

    gf::Vector2f base = gf::vec(12, 12) * TileSize;

    // terrain

    auto terrain = m_data.findTerrain(race.ground);
    assert(terrain != nullptr);

    terrain->tiles.setOrigin(base);
    target.draw(terrain->tiles, states);

    // extensions

    {
      std::size_t i = currentStage;
      gf::Vector2f offset = gf::vec(0.0f, 0.0f);

      while (i > 0) {
        offset += getStageOffset(race.stages[i].start);
        --i;
        race.stages[i].tiles.setPosition(offset);
        target.draw(race.stages[i].tiles, states);
      }

      assert(i == 0);
      auto extension = m_data.findExtension(race.ground, race.stages[0].start);

      if (extension) {
        extension->tiles.setPosition(offset);
        extension->tiles.setOrigin(base);
        target.draw(extension->tiles, states);
      }
    }

    {
      std::size_t i = currentStage;
      std::size_t max = race.stages.size() - 1;
      gf::Vector2f offset = gf::vec(0.0f, 0.0f);

      while (i < max) {
        offset += getStageOffset(race.stages[i].finish);
        ++i;
        race.stages[i].tiles.setPosition(offset);
        target.draw(race.stages[i].tiles, states);
      }

      assert(i == max);
      auto extension = m_data.findExtension(race.ground, race.stages[max].finish);

      if (extension) {
        extension->tiles.setPosition(offset);
        extension->tiles.setOrigin(base);
        target.draw(extension->tiles, states);
      }
    }


    // road

    stage.tiles.setPosition(gf::vec(0.0f, 0.0f));
    target.draw(stage.tiles, states);

#if 0
    gf::CompoundCurve curve(stage.line.getPoint(0));

    for (std::size_t i = 1; i < stage.line.getPointCount(); ++i) {
      curve.lineTo(stage.line.getPoint(i));
    }

    curve.close();
    curve.setColor(gf::Color::Red);
    curve.setWidth(5.0f);
    target.draw(curve, states);
#endif

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
