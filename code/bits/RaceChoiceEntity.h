#ifndef TA_RACE_CHOICE_ENTITY_H
#define TA_RACE_CHOICE_ENTITY_H

#include <gf/Entity.h>
#include <gf/TextureAtlas.h>
#include <gf/Random.h>
#include <gf/ResourceManager.h>

#include "RaceTypes.h"

namespace ta {
  struct TimeAttackData;

  class RaceChoiceEntity : public gf::Entity {
  public:
    RaceChoiceEntity(gf::ResourceManager& resources, TimeAttackData& data);

    void pointTo(gf::Vector2f coords);
    void triggerAction();
    std::size_t retrieveChosenRace();

    void update(gf::Time time) override;
    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    const gf::Texture& m_sandTexture;
    const gf::Texture& m_dirtTexture;
    const gf::Texture& m_asphaltTexture;
    gf::Font& m_font;
    gf::Vector2f m_cursor;

    TimeAttackData& m_data;
    std::size_t m_selection;
    std::size_t m_choice;
  };

}

#endif // TA_RACE_CHOICE_ENTITY_H
