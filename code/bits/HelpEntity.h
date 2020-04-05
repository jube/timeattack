#ifndef TA_HELP_ENTITY_H
#define TA_HELP_ENTITY_H

#include <gf/Entity.h>
#include <gf/Font.h>
#include <gf/ResourceManager.h>

namespace ta {

  class HelpEntity : public gf::Entity {
  public:
    HelpEntity(gf::ResourceManager& resources);

    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    gf::Font& m_font;
  };

}

#endif // TA_HELP_ENTITY_H
