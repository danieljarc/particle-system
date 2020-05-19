#include "GUIWidget.h"

GUIWidget::GUIWidget(GUIWidget* parent) :
    m_parent(parent),
    m_size(sf::Vector2f(0.f, 0.f)),
    m_bounds(sf::FloatRect(0.f, 0.f, 0.f, 0.f)),
    m_horizontalAlignment(GUIHorizontalAlignment::Left),
    m_verticalAlignment(GUIVerticalAlignment::Center),
    m_padding(),
    m_spacing()
{
}

GUIWidget::~GUIWidget()
{
}

void GUIWidget::SetParent(GUIWidget* parent)
{
    m_parent = parent;
}

GUIWidget* GUIWidget::GetParent()
{
    return m_parent;
}

void GUIWidget::SetSize(sf::Vector2f size)
{
    m_size = size;
}

void GUIWidget::SetSize(float width, float height)
{
    m_size.x = width;
    m_size.y = height;
}

sf::Vector2f const GUIWidget::GetSize()
{
    return m_size;
}

sf::Vector2f const GUIWidget::GetWorldPosition()
{
    GUIWidget* parent = m_parent;
    sf::Transform transform = getTransform();

    while (parent != nullptr)
    {
        transform *= parent->getTransform();
        parent = parent->m_parent;
    }

    return transform * sf::Vector2f();
}

sf::FloatRect GUIWidget::GetWorldBounds()
{
    sf::FloatRect bounds;
    bounds.left = GetWorldPosition().x;
    bounds.top = GetWorldPosition().y;
    bounds.width = m_size.x;
    bounds.height = m_size.y;
    return bounds;
}

void GUIWidget::SetHorizontalAlignment(GUIHorizontalAlignment halign)
{
    m_horizontalAlignment = halign;
}

void GUIWidget::SetVerticalAlignment(GUIVerticalAlignment valign)
{
    m_verticalAlignment = valign;
}

GUIHorizontalAlignment const GUIWidget::GetHorizontalAlignment()
{
    return m_horizontalAlignment;
}

GUIVerticalAlignment const GUIWidget::GetGUIVerticalAlignment()
{
    return m_verticalAlignment;
}

void GUIWidget::SetPadding(float l, float r, float t, float b)
{
    m_padding.left = l;
    m_padding.right = r;
    m_padding.top = t;
    m_padding.bottom = b;
}

GUIPadding const GUIWidget::GetPadding()
{
    return m_padding;
}

void GUIWidget::SetSpacing(float h, float v)
{
    m_spacing.horizontal = h;
    m_spacing.vertical = v;
}

GUISpacing const GUIWidget::GetSpacing()
{
    return m_spacing;
}
