#pragma once

#include <SFML/Graphics.hpp>

class ParticleSystem
{
public:
    ParticleSystem(sf::RenderWindow& window);
    ~ParticleSystem();

    void SetEmitterPosition(sf::Vector2f pos);
    void SetAttractorPosition(sf::Vector2f pos);
    void SetAttractorStrength(float strength);
    void SetGravityStrength(float strength);
    void SetSpeed(int speed);
    void SetSpread(int spread);
    void SetDirection(int direction);
    void SetCount(unsigned int count);
    void Initialize();
    void Shutdown();
    bool ProcessEvent(sf::Event& event);
    void Update(float dt);
    void Render();

private:
    sf::Vector2f Normalize(sf::Vector2f vector);
    void SetPosition(sf::Vector2f pos, std::size_t index);
    void SetColor(sf::Color col, std::size_t index);
    void ResetQuad(std::size_t index);

    //Particles
    unsigned int m_count;
    sf::VertexArray m_quads;
    std::vector<sf::Vector2f> m_positions;
    std::vector<sf::Vector2f> m_velocities;
    std::vector<sf::Time> m_lifetimes;
    sf::Vector2f m_quadSize;
    sf::Time m_minLifetime;
    sf::Time m_maxLifetime;
    int m_minSpeed;
    int m_maxSpeed;
    int m_spread;
    int m_direction;
    sf::Color m_color;
    
    //Timing
    sf::Clock m_clock;

    //Rendering
    sf::RenderWindow& m_window;
    sf::RenderTexture m_renderTexture;
    sf::Sprite m_sprite;
    sf::Shader m_vShader;
    sf::Shader m_fShader;

    //Emitter, attractor, forces
    sf::Vector2f m_emitterPosition;
    sf::CircleShape m_emitterShape;
    sf::Vector2f m_attractorPosition;
    sf::CircleShape m_attractorShape;
    sf::Vector2f m_attractorForce;
    float m_attractorStrength;
    sf::Vector2f m_gravityForce;
    float m_gravityStrength;
};