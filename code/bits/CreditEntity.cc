#include "CreditEntity.h"

#include <gf/Color.h>
#include <gf/Coordinates.h>
#include <gf/RenderTarget.h>
#include <gf/Text.h>

namespace ta {

  namespace {

    constexpr auto CreditText =
      "Coded by Julien Bernard for his daughter Abbygaëlle during the 2020 lockdown for the 'Confinement' game jam.\n"
      "Graphics by Kenney (kenney.nl)\n"
    ;
  }

  CreditEntity::CreditEntity(gf::ResourceManager& resources)
  : m_font(resources.getFont("TovariSans.otf"))
  {
  }

  void CreditEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coords(target);

    unsigned characterSize = coords.getRelativeCharacterSize(0.07f);
    float paragraphWidth = coords.getRelativeSize({ 0.6f, 0.0f }).width;
    auto position = coords.getRelativePoint({ 0.5f, 0.4f });

    gf::Text credit(CreditText, m_font, characterSize);
    credit.setColor(gf::Color::Black);
    credit.setParagraphWidth(paragraphWidth);
    credit.setAlignment(gf::Alignment::Left);
    credit.setLineSpacing(1.2f);
    credit.setPosition(position);
    credit.setAnchor(gf::Anchor::Center);
    target.draw(credit, states);
  }


}
