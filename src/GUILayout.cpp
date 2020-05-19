#include "GUILayout.h"
#include "ResourceManager.h"

#include <iostream>

GUILayout::GUILayout(GUIOrientation orientation, GUIWidget* parent) :
    m_orientation(orientation),
    GUIWidget(parent)
{
    //Load main GUI font
    ResourceManager::GetInstance().LoadFont(FontID::Main, "assets/DOS_VGA_437.ttf");
}

GUILayout::~GUILayout()
{
    while (m_children.size() != 0)
    {
        m_children.pop_back();
    }
}

bool GUILayout::Add(std::shared_ptr<GUIWidget> widget)
{
    if (widget == nullptr)
    {
        return false;
    }
    else
    {
        widget->SetParent(this);
        m_children.push_back(widget);
        return true;
    }
}

bool GUILayout::Remove(std::shared_ptr<GUIWidget> widget)
{
    if (widget == nullptr)
    {
        return false;
    }
    else
    {
        bool result = false;

        std::vector<std::shared_ptr<GUIWidget>>::iterator it;

        for (it = m_children.begin(); it != m_children.end(); ++it)
        {
            if (*it == widget)
            {
                widget->SetParent(nullptr);
                m_children.erase(it);
                result = true;
            }
        }

        return result;
    }
}

bool GUILayout::ProcessEvent(const sf::Event& event)
{
    for (auto& widget : m_children)
    {
        if (widget->ProcessEvent(event))
        {
            return true;
        }
    }

    return false;
}

void GUILayout::Build()
{
    float yOffset = m_padding.top;
    float xOffset = m_padding.left;

    if (m_orientation == GUIOrientation::Vertical)
    {
        for (auto& widget : m_children)
        {
            widget->Build();
            sf::Vector2f widgetPos = sf::Vector2f(xOffset, yOffset);
            sf::Vector2f widgetSize = widget->GetSize();

            switch (m_horizontalAlignment)
            {
            case GUIHorizontalAlignment::Left:
                widgetPos.x = m_padding.left;
                break;
            case GUIHorizontalAlignment::Center:
                widgetPos.x = (m_size.x / 2.f) - (widgetSize.x / 2.f);
                break;
            case GUIHorizontalAlignment::Right:
                widgetPos.x = (m_size.x) - (widgetSize.x + m_padding.right);
                break;
            default:
                break;
            }

            if (widgetSize.x > m_size.x)
            {
                m_size.x = widgetSize.x;
            }

            yOffset += widgetSize.y + m_spacing.vertical;
            widget->setPosition(widgetPos);
        }

        m_size.x += (m_padding.left + m_padding.right);
        m_size.y = yOffset - m_spacing.vertical + m_padding.bottom;
    }
    else if (m_orientation == GUIOrientation::Horizontal)
    {
        for (auto& widget : m_children)
        {
            widget->Build();
            sf::Vector2f widgetPos = sf::Vector2f(xOffset, yOffset);
            sf::Vector2f widgetSize = widget->GetSize();

            switch (m_verticalAlignment)
            {
            case GUIVerticalAlignment::Top:
                widgetPos.y = m_padding.top;
                break;
            case GUIVerticalAlignment::Center:
                widgetPos.y = (m_size.y / 2.f) - (widgetSize.y / 2.f);
                break;
            case GUIVerticalAlignment::Bottom:
                widgetPos.y = (m_size.y) - (widgetSize.y + m_padding.bottom);
                break;
            default:
                break;
            }

            if (widgetSize.y > m_size.y)
            {
                m_size.y = widgetSize.y;
            }

            xOffset += widgetSize.x + m_spacing.horizontal;
            widget->setPosition(widgetPos);
        }

        m_size.y += (m_padding.top + m_padding.bottom);
        m_size.x = xOffset - m_spacing.horizontal + m_padding.right;
    }
}

void GUILayout::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for (auto& child : m_children)
    {
        target.draw(*child, states);
    }
}
