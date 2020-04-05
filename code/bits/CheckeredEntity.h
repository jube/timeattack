#ifndef TA_CHECKERED_ENTITY_H
#define TA_CHECKERED_ENTITY_H

#include <gf/Entity.h>
#include <gf/ResourceManager.h>

namespace ta {

  class CheckeredEntity : public gf::Entity {
  public:
    CheckeredEntity(gf::ResourceManager& resources);
    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    gf::Texture& m_checkered;
  };

}

#endif // TA_CHECKERED_ENTITY_H
