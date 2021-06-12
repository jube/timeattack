#include "ProgressEntity.h"

#include <gf/Coordinates.h>
#include <gf/RenderTarget.h>
#include <gf/Shapes.h>
#include <gf/Sprite.h>
#include <gf/StringUtils.h>
#include <gf/Text.h>

#include "Settings.h"
#include "TimeAttackData.h"
#include "TimeAttackState.h"

namespace ta {


  ProgressEntity::ProgressEntity(gf::ResourceManager& resources, const gf::TextureAtlas& atlas, const TimeAttackData& data, const TimeAttackState& state)
  : m_sandTexture(resources.getTexture("tileset_road_sand.png"))
  , m_dirtTexture(resources.getTexture("tileset_road_dirt.png"))
  , m_asphaltTexture(resources.getTexture("tileset_road_asphalt.png"))
  , m_atlas(atlas)
  , m_font(resources.getFont("CodeNewRomanBold.otf"))
  , m_data(data)
  , m_state(state)
  {
  }

  void ProgressEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coords(target);

    std::size_t currentStage = m_state.currentStage;
    std::size_t stageCount = m_data.races[m_state.currentRace].stages.size();

    std::string progressString = gf::formatString("%02zu/%02zu", currentStage + 1, stageCount);
    unsigned characterSize = coords.getRelativeCharacterSize(0.08f);

    auto progressPosition = coords.getRelativePoint({ 0.9f, 0.1f });
    gf::Text progress(progressString, m_font, characterSize);
    progress.setColor(gf::Color::Yellow);
    progress.setOutlineColor(gf::Color::Black);
    progress.setOutlineThickness(characterSize * 0.075f);
    progress.setPosition(progressPosition);
    progress.setAnchor(gf::Anchor::BottomCenter);
    target.draw(progress, states);

    auto roadPosition = coords.getRelativePoint({ 0.9f, 0.15f });

    const float length = coords.getRelativeSize({ 0.0f, 0.05f }).height;
    const float spacing = length / 10;
    const float padding = length / 5;

    float textureScale = length / TileExtent;

    gf::RectF back = gf::RectF::fromPositionSize(roadPosition - length / 2 - padding, gf::vec(length + 2 * padding, stageCount * length + (stageCount - 1) * spacing + 2 * padding));

    gf::RoundedRectangleShape shape(back);
    shape.setColor(gf::Color::Gray() * gf::Color::Opaque(0.7f));
    shape.setRadius(padding);
    target.draw(shape, states);

    for (std::size_t i = 0; i < stageCount; ++i) {
      gf::Sprite sprite;

      switch (m_data.races[m_state.currentRace].ground) {
        case RaceGround::Sand:
          sprite.setTexture(m_sandTexture);
          break;
        case RaceGround::Dirt:
          sprite.setTexture(m_dirtTexture);
          break;
        case RaceGround::Asphalt:
          sprite.setTexture(m_asphaltTexture);
          break;
      }

      sprite.setTextureRect(gf::RectF::fromPositionSize({ 0.0f, 0.0f }, 1.0f / TileCount));

      if (stageCount - i - 1 > currentStage) {
        sprite.setColor(gf::Color::Opaque(0.5f));
      }

      gf::Vector2f position = roadPosition + gf::diry(i * (length + spacing));

      sprite.setScale(textureScale);
      sprite.setAnchor(gf::Anchor::Center);
      sprite.setPosition(position);
      target.draw(sprite, states);
    }

    gf::Vector2f miniCarPosition = roadPosition + gf::diry((stageCount - currentStage - 1) * (length + spacing));

    gf::Sprite sprite(m_atlas.getTexture(), m_atlas.getTextureRect(m_state.car.texture));
    sprite.setScale(textureScale / 2);
    sprite.setAnchor(gf::Anchor::Center);
    sprite.setPosition(miniCarPosition);
    target.draw(sprite, states);


  }

}


