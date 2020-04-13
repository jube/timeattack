#include "RaceChoiceEntity.h"

#include <utility>

#include <gf/Coordinates.h>
#include <gf/RenderTarget.h>
#include <gf/Shapes.h>
#include <gf/Sprite.h>
#include <gf/Text.h>

#include <gf/Log.h>

#include "Settings.h"
#include "TimeAttackData.h"

namespace ta {

  namespace {
    constexpr std::size_t NoChoice = -1;
  }


  RaceChoiceEntity::RaceChoiceEntity(gf::ResourceManager& resources, TimeAttackData& data)
  : m_sandTexture(resources.getTexture("tileset_road_sand.png"))
  , m_dirtTexture(resources.getTexture("tileset_road_dirt.png"))
  , m_asphaltTexture(resources.getTexture("tileset_road_asphalt.png"))
  , m_font(resources.getFont("TovariSans.otf"))
  , m_cursor(0.0f, 0.0f)
  , m_data(data)
  , m_selection(NoChoice)
  , m_choice(NoChoice)
  {
  }

  void RaceChoiceEntity::pointTo(gf::Vector2f coords) {
    m_cursor = coords;
  }

  void RaceChoiceEntity::triggerAction() {
    m_choice = m_selection;
  }

  std::size_t RaceChoiceEntity::retrieveChosenRace() {
    auto choice = std::exchange(m_choice, NoChoice);

    if (choice != NoChoice) {
      m_cursor = gf::vec(0.0f, 0.0);
    }

    return choice;
  }

  void RaceChoiceEntity::update(gf::Time time) {
  }

  void RaceChoiceEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coords(target);

    unsigned characterSize = coords.getRelativeCharacterSize(0.1f);
    auto position = coords.getRelativePoint({ 0.5f, 0.1f });

    gf::Text chooseText("Choose your race", m_font, characterSize);
    chooseText.setAnchor(gf::Anchor::Center);
    chooseText.setPosition(position);
    chooseText.setColor(gf::Color::White);
    chooseText.setOutlineColor(gf::Color::Black);
    chooseText.setOutlineThickness(characterSize * 0.05f);
    target.draw(chooseText, states);

    gf::Vector2f base = coords.getRelativePoint({ 0.5f, 0.25f });
    const float length = coords.getRelativeSize({ 0.0f, 0.12f }).height;
    const float spacing = length / 2.5;

    float textureScale = length / TileExtent;

    static constexpr int GroundCount = 3;
    static constexpr RaceGround Grounds[GroundCount] = { RaceGround::Sand, RaceGround::Dirt, RaceGround::Asphalt };

    static constexpr int DifficultyCount = 4;
    static constexpr RaceDifficulty Difficulties[DifficultyCount] = { RaceDifficulty::Easy, RaceDifficulty::Medium, RaceDifficulty::Hard, RaceDifficulty::Challenging };

    std::size_t selection = NoChoice;

    for (int i = 0; i < GroundCount; ++i) {
      gf::Sprite sprite;
      sprite.setTextureRect(gf::RectF::fromPositionSize({ 0.0f, 0.0f }, 1.0f / TileCount));

      switch (Grounds[i]) {
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

      sprite.setScale(textureScale);
      sprite.setAnchor(gf::Anchor::Center);

      for (int j = 0; j < DifficultyCount; ++j) {
        std::size_t raceIndex = m_data.findRace(Difficulties[j], Grounds[i]);

        if (raceIndex == NoChoice) {
          continue;
        }

        gf::Vector2f position = base + gf::vec((i - 1) * (length + 3 * spacing),  j * (length + spacing));

        // race ground symbol

        sprite.setPosition(position);
        target.draw(sprite);

        // race difficulty symbol

        gf::StarShape star(length / 12, length / 6, 5);
        star.setOutlineColor(gf::Color::Gray(0.25f));
        star.setOutlineThickness(length / 40);

        switch (Difficulties[j]) {
          case RaceDifficulty::Easy:
            star.setColor(gf::Color::fromRgba32(0x0F, 0xDD, 0x9B));
            star.setPosition(position);
            star.setAnchor(gf::Anchor::Center);
            target.draw(star);
            break;
          case RaceDifficulty::Medium:
            star.setColor(gf::Color::fromRgba32(0xCB, 0xDD, 0x0F));

            for (int k = 0; k < 2; ++k) {
              star.setPosition(position + gf::unit(k * gf::Pi) * length / 4);
              star.setAnchor(gf::Anchor::Center);
              target.draw(star);
            }
            break;
          case RaceDifficulty::Hard:
            star.setColor(gf::Color::fromRgba32(0xDD, 0x85, 0x0F));

            for (int k = 0; k < 3; ++k) {
              star.setPosition(position + gf::unit(- gf::Pi2 + k * 2 * gf::Pi / 3) * length / 3.5);
              star.setAnchor(gf::Anchor::Center);
              target.draw(star);
            }
            break;
          case RaceDifficulty::Challenging:
            star.setColor(gf::Color::fromRgba32(0xDD, 0x0F, 0x0F));

            for (int k = 0; k < 4; ++k) {
              star.setPosition(position + gf::unit(gf::Pi4 + k * gf::Pi / 2) * length / 3);
              star.setAnchor(gf::Anchor::Center);
              target.draw(star);
            }
            break;
        }


        // outline

        gf::RectF rect = gf::RectF::fromCenterSize(position, gf::vec(length, length));
        bool isCursorInside = rect.contains(m_cursor);

        gf::RectangleShape shape({ length, length });
        shape.setPosition(position);
        shape.setAnchor(gf::Anchor::Center);
        shape.setColor(gf::Color::Transparent);

        if (isCursorInside) {
          selection = raceIndex;
          shape.setOutlineColor(gf::Color::Gray()); // gf::Color::darker(gf::Color::Green)
          shape.setOutlineThickness(characterSize * 0.05f);
        } else {
          shape.setOutlineColor(gf::Color::Gray(0.75f)); // gf::Color::darker(gf::Color::Green)
          shape.setOutlineThickness(characterSize * 0.01f);
        }

        target.draw(shape, states);

      }
    }

    m_selection = selection;
  }

}
