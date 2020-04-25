#ifndef TA_PAUSE_ENTITY_H
#define TA_PAUSE_ENTITY_H

#include <gf/Entity.h>
#include <gf/Font.h>
#include <gf/ResourceManager.h>

namespace ta {

  class PauseEntity : public gf::Entity {
  public:
    PauseEntity(gf::ResourceManager& resources);

    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    gf::Font& m_font;
  };

}

#endif // TA_PAUSE_ENTITY_H
