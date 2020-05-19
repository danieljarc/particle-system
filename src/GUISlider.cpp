#include "GUISlider.h"
#include <iostream>

GUISlider::GUISlider(GUIStyle& style, GUIWidget* parent) :
    m_style(style),
    m_state(GUIWidgetState::None),
    GUIWidget(parent),
    m_value(0.0f)
{
    //Set background style
    m_background.setFillColor(m_style.backgroundColor);
    m_background.setOutlineColor(m_style.backgroundOutlineColor);
    m_background.setOutlineThickness(m_style.backgroundOutlineThickness);

    //Set empty bar style
    m_bar.setFillColor(sf::Color::Black);
    m_bar.setSize(sf::Vector2f(0.f, 2.f));

    //Set bar fill style
    m_fill.setFillColor(sf::Color(100,255,255,255));

    //Set Control style
    m_control.setFillColor(sf::Color(200,200,200,255));
    m_control.setSize(sf::Vector2f(20.f, 24.f));
    m_control.setOrigin(m_control.getLocalBounds().width / 2.f, m_control.getLocalBounds().height / 2.f);
}

GUISlider::~GUISlider()
{
}

void GUISlider::SetValue(float value)
{
    m_value = value;
}

const float GUISlider::GetValue()
{
    return m_value;
}

void GUISlider::Build()
{
    sf::Vector2f barSize;
    sf::Vector2f barPos;
    sf::Vector2f fillSize;
    sf::Vector2f fillPos; 
    sf::Vector2f controlSize;
    sf::Vector2f controlPos;

    barSize.x = m_size.x - (m_padding.left + m_padding.right);
    barSize.y = m_bar.getLocalBounds().height;
    barPos.x = m_padding.left;
    barPos.y = (m_size.y / 2.f) - (barSize.y / 2.f);

    fillSize.x = m_value * barSize.x;
    fillSize.y = barSize.y;
    fillPos.x = barPos.x;
    fillPos.y = barPos.y;

    controlSize.x = m_control.getLocalBounds().width;
    controlSize.y = m_control.getLocalBounds().height;
    controlPos.x = fillSize.x + (controlSize.x / 2.f);
    controlPos.y = fillPos.y + (fillSize.y / 2.f);

    m_bar.setSize(barSize);
    m_bar.setPosition(barPos);

    m_fill.setSize(fillSize);
    m_fill.setPosition(fillPos);

    m_control.setSize(controlSize);
    m_control.setPosition(controlPos);

    m_background.setSize(m_size);
}

bool GUISlider::ProcessEvent(const sf::Event& event)
{
    bool result = false;

    sf::FloatRect sliderArea = GetWorldBounds();

    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

        if (sliderArea.contains(mousePos))
        {
            m_state = GUIWidgetState::Dragging;
            result = true;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (m_state == GUIWidgetState::Dragging)
        {
            m_state = GUIWidgetState::None;
            OnMove(m_value);
            result = true;
        }
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        sf::Vector2f mousePos(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));

        if (m_state == GUIWidgetState::Dragging && sliderArea.contains(mousePos))
        {
            float newXPos = mousePos.x - sliderArea.left + m_padding.left;
            float minXPos = m_bar.getGlobalBounds().left;
            float maxXPos = m_bar.getGlobalBounds().left + m_bar.getGlobalBounds().width;

            if (newXPos < minXPos)
            {
                newXPos = minXPos;
            }

            if (newXPos > maxXPos)
            {
                newXPos = maxXPos;
            }

            m_value = (newXPos - minXPos) / (maxXPos - minXPos);
            m_control.setPosition(newXPos, m_control.getPosition().y);
            m_fill.setSize(sf::Vector2f(newXPos - m_control.getLocalBounds().width / 2.f, m_fill.getLocalBounds().height));
            result = true;
        }
    }

    return result;
}

void GUISlider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_background, states);
    target.draw(m_bar, states);
    target.draw(m_fill, states);
    target.draw(m_control, states);
}