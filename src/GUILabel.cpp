#include "GUILabel.h"

GUILabel::GUILabel(const std::string& text, GUIStyle& style, GUIWidget* parent) :
    m_style(style),
    GUIWidget(parent)
{
    m_text.setString(text);
    m_text.setFont(ResourceManager::GetInstance().GetFont(m_style.fontID));
    m_text.setCharacterSize(m_style.fontSize);
    m_text.setFillColor(m_style.textColor);

    m_background.setFillColor(m_style.backgroundColor);
    m_background.setOutlineColor(m_style.backgroundOutlineColor);
    m_background.setOutlineThickness(m_style.backgroundOutlineThickness);

    m_size.x = m_text.getLocalBounds().width + m_padding.left + m_padding.right;
    m_size.y = m_text.getLocalBounds().height + m_padding.top + m_padding.bottom;

    m_background.setSize(m_size);
}

GUILabel::~GUILabel()
{
}

void GUILabel::SetText(const std::string& text)
{
    m_text.setString(text);
}

void GUILabel::SetTextColor(const sf::Color& color)
{
    m_text.setFillColor(color);
}

void GUILabel::SetBackgroundColor(const sf::Color& color)
{
    m_background.setFillColor(color);
}

void GUILabel::Build()
{
    sf::Vector2f textPos = sf::Vector2f(0.f, 0.f);

    switch (m_horizontalAlignment)
    {
    case GUIHorizontalAlignment::Left:
        textPos.x = m_padding.left;
        break;
    case GUIHorizontalAlignment::Center:
        textPos.x = (m_size.x / 2.f) - (m_text.getLocalBounds().width / 2.f);
        break;
    case GUIHorizontalAlignment::Right:
        textPos.x = (m_size.x) - (m_text.getLocalBounds().width + m_padding.right);
        break;
    default:
        break;
    }

    switch (m_verticalAlignment)
    {
    case GUIVerticalAlignment::Top:
        textPos.y = m_padding.top - m_text.getLocalBounds().top;
        break;
    case GUIVerticalAlignment::Center:
        textPos.y = (m_size.y / 2.f) - (m_text.getLocalBounds().height / 2.f) - m_text.getLocalBounds().top;
        break;
    case GUIVerticalAlignment::Bottom:
        textPos.y = (m_size.y) - (m_text.getLocalBounds().height + m_padding.bottom) - m_text.getLocalBounds().top;
        break;
    default:
        break;
    }

    m_text.setPosition(textPos);
    m_background.setSize(m_size);
}

bool GUILabel::ProcessEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonReleased)
    {
        sf::FloatRect labelArea = GetWorldBounds();
        sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

        if (labelArea.contains(mousePos))
        {
            return true;
        }
    }

    return false;
}

void GUILabel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_background, states);
    target.draw(m_text, states);
}
