#include "CarChoiceEntity.h"

#include <utility>

#include <gf/Coordinates.h>
#include <gf/RenderTarget.h>
#include <gf/Shapes.h>
#include <gf/Sprite.h>
#include <gf/Text.h>

#include <gf/Log.h>

#include "Settings.h"

namespace ta {

  namespace {

    constexpr int CarColorCount = 5;
    constexpr int CarTypeCount = 5;

    constexpr const char * CarNames[CarColorCount][CarTypeCount] = {
      { "car_black_1",  "car_black_2",  "car_black_3",  "car_black_4",  "car_black_5"   },
      { "car_blue_1",   "car_blue_2",   "car_blue_3",   "car_blue_4",   "car_blue_5"    },
      { "car_green_1",  "car_green_2",  "car_green_3",  "car_green_4",  "car_green_5"   },
      { "car_red_1",    "car_red_2",    "car_red_3",    "car_red_4",    "car_red_5"     },
      { "car_yellow_1", "car_yellow_2", "car_yellow_3", "car_yellow_4", "car_yellow_5"  }
    };

    constexpr int CarPadding = 10;

  }

  CarChoiceEntity::CarChoiceEntity(gf::ResourceManager& resources, const gf::TextureAtlas& atlas)
  : m_atlas(atlas)
  , m_font(resources.getFont("TovariSans.otf"))
  , m_cursor(0.0f, 0.0f)
  , m_selection(nullptr)
  , m_choice(nullptr)
  {
  }

  void CarChoiceEntity::pointTo(gf::Vector2f coords) {
    m_cursor = coords;
  }

  void CarChoiceEntity::triggerAction() {
    m_choice = m_selection;
  }

  const char *CarChoiceEntity::retriveChosenCar() {
    return std::exchange(m_choice, nullptr);
  }

  void CarChoiceEntity::update(gf::Time time) {
  }

  void CarChoiceEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coords(target);

    unsigned characterSize = coords.getRelativeCharacterSize(0.1f);
    auto position = coords.getRelativePoint({ 0.5f, 0.1f });

    gf::Text chooseText("Choose your car", m_font, characterSize);
    chooseText.setAnchor(gf::Anchor::Center);
    chooseText.setPosition(position);
    chooseText.setColor(gf::Color::White);
    chooseText.setOutlineColor(gf::Color::Black);
    chooseText.setOutlineThickness(characterSize * 0.05f);
    target.draw(chooseText, states);

    gf::Vector2f base = coords.getRelativePoint({ 0.5f, 0.25f });
    const float length = coords.getRelativeSize({ 0.0f, 0.12f }).height;
    const float spacing = length / 10;
    int maxTextureHeight = m_atlas.getSubTexture("car_black_1").getHeight() + CarPadding;
    float textureScale = length / maxTextureHeight;

    const char *selection = nullptr;

    for (int i = 0; i < CarColorCount; ++i) {
      for (int j = 0; j < CarTypeCount; ++j) {
        gf::Vector2f position = base + gf::vec((j - 2) * (length + spacing), i * (length + spacing));

        gf::Sprite sprite(m_atlas.getTexture(), m_atlas.getTextureRect(CarNames[i][j]));
        sprite.setScale(textureScale);
        sprite.setPosition(position);
        sprite.setAnchor(gf::Anchor::Center);
        target.draw(sprite, states);

        gf::RectF rect = gf::RectF::fromCenterSize(position, gf::vec(length, length));
        bool isCursorInside = rect.contains(m_cursor);

        gf::RectangleShape shape({ length, length });
        shape.setPosition(position);
        shape.setAnchor(gf::Anchor::Center);
        shape.setColor(gf::Color::Transparent);


        if (isCursorInside) {
          selection = CarNames[i][j];
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
