#ifndef TA_CONTINUE_ENTITY_H
#define TA_CONTINUE_ENTITY_H

#include <gf/Entity.h>
#include <gf/Font.h>
#include <gf/ResourceManager.h>
#include <gf/WidgetContainer.h>
#include <gf/Widgets.h>

namespace ta {

  class ContinueEntity : public gf::Entity {
  public:
    ContinueEntity(gf::ResourceManager& resources);

    void pointTo(gf::Vector2f coords);
    void triggerAction();

    bool hasPressedContinue();

    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    gf::Font& m_font;
    gf::WidgetContainer m_container;
    gf::TextWidget m_continueWidget;
    bool m_pressed;
  };

}

#endif // TA_CONTINUE_ENTITY_H
