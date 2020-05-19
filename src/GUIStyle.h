#pragma once

#include "ResourceManager.h"

#include <SFML/Graphics.hpp>

struct GUIStyle
{
    GUIStyle() :
        fontID(FontID::Main),
        fontSize(20),
        textColor(sf::Color(200, 200, 200, 220)),
        textHighlight(sf::Color(255, 255, 255, 220)),
        textOutlineColor(sf::Color::Magenta),
        textOutlineHighlight(sf::Color::Yellow),
        textOutlineThickness(0.f),
        backgroundColor(sf::Color(20, 20, 20, 220)),
        backgroundHighlight(sf::Color(60, 60, 60, 220)),
        backgroundOutlineColor(sf::Color::Magenta),
        backgroundOutlineHighlight(sf::Color::Yellow),
        backgroundOutlineThickness(0.f)
    {}

    //Font
    FontID fontID;
    unsigned int fontSize;

    //Text
    sf::Color textColor;
    sf::Color textHighlight;
    sf::Color textOutlineColor;
    sf::Color textOutlineHighlight;
    float textOutlineThickness;

    //Background
    sf::Color backgroundColor;
    sf::Color backgroundHighlight;
    sf::Color backgroundOutlineColor;
    sf::Color backgroundOutlineHighlight;
    float backgroundOutlineThickness;
};