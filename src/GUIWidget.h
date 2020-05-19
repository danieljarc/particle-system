#pragma once

#include <SFML/Graphics.hpp>

enum class GUIWidgetState
{
    None,
    Active,
    Inactive,
    Hover,
    Dragging
};

enum class GUIOrientation
{
    Vertical,
    Horizontal
};

enum class GUIVerticalAlignment
{
    Top,
    Center,
    Bottom
};

enum class GUIHorizontalAlignment
{
    Left,
    Center,
    Right
};

struct GUIPadding
{
    GUIPadding() : left(10.f), right(10.f), top(0.f), bottom(0.f) {}
    float left;
    float right;
    float top;
    float bottom;
};

struct GUISpacing
{
    GUISpacing() : vertical(10.f), horizontal(10.f) {}
    float vertical;
    float horizontal;
};

class GUIWidget : public sf::Drawable, public sf::Transformable
{
public:
    GUIWidget(GUIWidget* parent = nullptr);
    virtual ~GUIWidget();

    //Hierarchy
    void SetParent(GUIWidget* parent);
    GUIWidget* GetParent();

    //Size, position, bounds
    void SetSize(sf::Vector2f size);
    void SetSize(float width, float height);
    sf::Vector2f const GetSize();
    sf::Vector2f const GetWorldPosition();
    sf::FloatRect GetWorldBounds();

    //Alignment, orientation, padding, spacing
    void SetHorizontalAlignment(GUIHorizontalAlignment halign);
    void SetVerticalAlignment(GUIVerticalAlignment valign);
    void SetPadding(float l, float r, float t, float b);
    void SetSpacing(float v, float h);
    GUIHorizontalAlignment const GetHorizontalAlignment();
    GUIVerticalAlignment const GetGUIVerticalAlignment();
    GUIPadding const GetPadding();
    GUISpacing const GetSpacing();

    //GUIWidget specific
    virtual void Build() = 0;
    virtual bool ProcessEvent(const sf::Event& event) = 0;

protected:
    GUIWidget* m_parent;
    sf::Vector2f m_size;
    sf::FloatRect m_bounds;
    GUIHorizontalAlignment m_horizontalAlignment;
    GUIVerticalAlignment m_verticalAlignment;
    GUIPadding m_padding;
    GUISpacing m_spacing;
};