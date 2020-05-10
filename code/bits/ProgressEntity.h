#ifndef TA_PROGESS_ENTITY_H
#define TA_PROGESS_ENTITY_H

#include <gf/Entity.h>
#include <gf/Font.h>
#include <gf/ResourceManager.h>
#include <gf/TextureAtlas.h>

namespace ta {
  struct TimeAttackData;
  struct TimeAttackState;

  class ProgressEntity : public gf::Entity {
  public:
    ProgressEntity(gf::ResourceManager& resources, const gf::TextureAtlas& atlas, const TimeAttackData& data, const TimeAttackState& state);

    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    const gf::Texture& m_sandTexture;
    const gf::Texture& m_dirtTexture;
    const gf::Texture& m_asphaltTexture;
    const gf::TextureAtlas& m_atlas;
    gf::Font& m_font;
    const TimeAttackData& m_data;
    const TimeAttackState& m_state;
  };

}

#endif // TA_PROGESS_ENTITY_H
