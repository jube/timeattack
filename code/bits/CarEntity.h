#ifndef TA_CAR_ENTITY_H
#define TA_CAR_ENTITY_H

#include <gf/Entity.h>
#include <gf/TextureAtlas.h>

namespace ta {

  struct TimeAttackState;

  class CarEntity : public gf::Entity {
  public:
    CarEntity(const gf::TextureAtlas& atlas, TimeAttackState& state);

    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    const gf::TextureAtlas& m_atlas;
    TimeAttackState& m_state;
  };

}

#endif // TA_CAR_ENTITY_H
