#pragma once

#include "GUIStyle.h"
#include "GUILayout.h"
#include "GUILabel.h"
#include "ParticleSystem.h"

#include <SFML/Graphics.hpp>
#include <sstream>

class Application
{
public:
    Application();
    ~Application();

    void Run();

private:
    void ProcessEvent(sf::Event& event);
    void Update(float dt);
    void Render();

    sf::RenderWindow m_window;
    ParticleSystem m_particleSystem;
    GUIStyle m_style;
    GUILayout m_controls;
    GUILabel m_fpsLabel;
    sf::Time m_fpsTimer;
    float m_fps;
    unsigned int m_frameCount;
    std::stringstream m_stream;
};