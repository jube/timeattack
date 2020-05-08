#ifndef TA_CREDIT_ENTITY_H
#define TA_CREDIT_ENTITY_H

#include <gf/Entity.h>
#include <gf/Font.h>
#include <gf/ResourceManager.h>

namespace ta {

  class CreditEntity : public gf::Entity {
  public:
    CreditEntity(gf::ResourceManager& resources);

    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    gf::Font& m_font;
  };

}

#endif // TA_CREDIT_ENTITY_H
