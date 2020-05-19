#pragma once

#include "GUIWidget.h"
#include "GUIStyle.h"

#include <functional>

class GUISlider : public GUIWidget
{
public:
    GUISlider(GUIStyle& style, GUIWidget* parent = nullptr);
    ~GUISlider();

    void SetValue(float value);
    const float GetValue();
    std::function<void(float)> OnMove;
    virtual void Build() override;
    virtual bool ProcessEvent(const sf::Event& event) override;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    GUIStyle& m_style;
    GUIWidgetState m_state;
    sf::RectangleShape m_control;
    sf::RectangleShape m_fill;
    sf::RectangleShape m_bar;
    sf::RectangleShape m_background;
    float m_value;
};