#ifndef TA_CAR_CHOICE_ENTITY_H
#define TA_CAR_CHOICE_ENTITY_H

#include <gf/Entity.h>
#include <gf/TextureAtlas.h>
#include <gf/Random.h>
#include <gf/ResourceManager.h>

namespace ta {

  class CarChoiceEntity : public gf::Entity {
  public:
    CarChoiceEntity(gf::ResourceManager& resources, const gf::TextureAtlas& atlas);

    void pointTo(gf::Vector2f coords);
    void triggerAction();
    const char *retrieveChosenCar();

    void update(gf::Time time) override;
    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    const gf::TextureAtlas& m_atlas;
    gf::Font& m_font;
    gf::Vector2f m_cursor;
    const char *m_selection;
    const char *m_choice;
  };


}


#endif // TA_CAR_CHOICE_ENTITY_H
