#include "TrafficEntity.h"

#include <gf/RenderTarget.h>
#include <gf/Sprite.h>

#include <gf/Log.h>

#include "Settings.h"

namespace ta {

  namespace {
    constexpr std::size_t VehicleCount = 10;
    constexpr gf::RectF ExtraView = IntroView.grow(500.0);

    constexpr auto Names = {
      "car_black_small_1",
      "car_black_small_2",
      "car_black_small_3",
      "car_black_small_4",
      "car_black_small_5",
      "car_blue_small_1",
      "car_blue_small_2",
      "car_blue_small_3",
      "car_blue_small_4",
      "car_blue_small_5",
      "car_green_small_1",
      "car_green_small_2",
      "car_green_small_3",
      "car_green_small_4",
      "car_green_small_5",
      "car_red_small_1",
      "car_red_small_2",
      "car_red_small_3",
      "car_red_small_4",
      "car_red_small_5",
      "car_yellow_small_1",
      "car_yellow_small_2",
      "car_yellow_small_3",
      "car_yellow_small_4",
      "car_yellow_small_5",
    };

  }

  TrafficEntity::TrafficEntity(const gf::TextureAtlas& atlas, gf::Random& random)
  : gf::Entity(-1)
  , m_atlas(atlas)
  , m_random(random)
  {
    for (std::size_t i = 0; i < VehicleCount; ++i) {
      m_vehicles.emplace_back(generateVehicle());
    }
  }

  void TrafficEntity::update(gf::Time time) {
    for (auto& vehicle : m_vehicles) {
      vehicle.warmup -= time;

      if (vehicle.warmup >= gf::Time::zero()) {
        continue;
      }

      auto direction = gf::unit(vehicle.angle);
      vehicle.position += vehicle.velocity * time.asSeconds() * direction;

      if (gf::dot(vehicle.position, direction) > 0 && !ExtraView.contains(vehicle.position)) {
        vehicle = generateVehicle();
      }
    }
  }

  void TrafficEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    for (auto& vehicle : m_vehicles) {
      gf::Sprite sprite(m_atlas.getTexture(), m_atlas.getTextureRect(vehicle.name));
      sprite.setPosition(vehicle.position);
      sprite.setRotation(vehicle.angle + gf::Pi2);
      sprite.setAnchor(gf::Anchor::Center);
      target.draw(sprite, states);

//       gf::Log::debug("%s @ %g,%g\n", vehicle.name, vehicle.position.x, vehicle.position.y);
    }
  }

  auto TrafficEntity::generateVehicle() -> Vehicle {
    Vehicle vehicle;
    vehicle.warmup = gf::seconds(0); // gf::seconds(m_random.computeUniformFloat(0.0f, 5.0f));
    vehicle.name = Names.begin()[m_random.computeUniformInteger(std::size_t{0}, Names.size() - 1)];
    vehicle.position = ExtraView.getSize().width * gf::unit(m_random.computeAngle());
    vehicle.angle = m_random.computeAngle();
    vehicle.velocity = m_random.computeUniformFloat(400.0f, 800.0f);
    return vehicle;
  }

}
