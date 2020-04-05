#ifndef TA_TRAFFIC_ENTITY_H
#define TA_TRAFFIC_ENTITY_H

#include <gf/Entity.h>
#include <gf/TextureAtlas.h>
#include <gf/Random.h>
#include <gf/ResourceManager.h>

namespace ta {

  class TrafficEntity : public gf::Entity {
  public:
    TrafficEntity(const gf::TextureAtlas& atlas, gf::Random& random);

    void update(gf::Time time) override;
    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    struct Vehicle {
      gf::Time warmup;
      const char *name;
      gf::Vector2f position;
      float angle;
      float velocity;
    };

    Vehicle generateVehicle();

  private:
    const gf::TextureAtlas& m_atlas;
    gf::Random& m_random;
    std::vector<Vehicle> m_vehicles;
  };


}


#endif // TA_TRAFFIC_ENTITY_H
