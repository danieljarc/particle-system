#pragma once

#include "GUIWidget.h"
#include "GUIStyle.h"

class GUILabel : public GUIWidget
{
public:
    GUILabel(const std::string& text, GUIStyle& style, GUIWidget* parent = nullptr);
    ~GUILabel();

    void SetText(const std::string& text);
    void SetTextColor(const sf::Color& color);
    void SetBackgroundColor(const sf::Color& color);
    virtual void Build() override;
    virtual bool ProcessEvent(const sf::Event& event);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    GUIStyle& m_style;
    sf::Text m_text;
    sf::RectangleShape m_background;
};