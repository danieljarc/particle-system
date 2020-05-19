#include "ParticleSystem.h"

#include <cmath>

ParticleSystem::ParticleSystem(sf::RenderWindow& window) :
    m_window(window),
    m_count(10000),
    m_minLifetime(sf::seconds(3.f)),
    m_maxLifetime(sf::seconds(10.f)),
    m_minSpeed(10),
    m_maxSpeed(60),
    m_spread(360),
    m_direction(360),
    m_gravityForce(0.f, 1.f),
    m_gravityStrength(0.f),
    m_attractorForce(0.f, 0.f),
    m_attractorStrength(0.f),
    m_quadSize(2.f, 2.f)
{
    //Load shaders
    m_vShader.loadFromFile("assets/vertex_shader.vert", sf::Shader::Vertex);
    m_vShader.setUniform("storm_total_radius", 200.f);
    m_vShader.setUniform("storm_inner_radius", 12.f);

    m_fShader.loadFromFile("assets/fragment_shader.frag", sf::Shader::Fragment);
    m_fShader.setUniform("texture", sf::Shader::CurrentTexture);
    m_fShader.setUniform("blur_radius", 0.001f);
}

ParticleSystem::~ParticleSystem()
{
    Shutdown();
}

void ParticleSystem::SetEmitterPosition(sf::Vector2f pos)
{
    m_emitterPosition = pos;
    m_emitterShape.setPosition(pos);
}

void ParticleSystem::SetAttractorPosition(sf::Vector2f pos)
{
    m_attractorPosition = pos;
    m_attractorShape.setPosition(pos);
}

void ParticleSystem::SetAttractorStrength(float strength)
{
    m_attractorStrength = strength;
}

void ParticleSystem::SetGravityStrength(float strength)
{
    m_gravityStrength = strength;
}

void ParticleSystem::SetSpeed(int speed)
{
    m_minSpeed = std::max(1, speed - 30);
    m_maxSpeed = std::min(500, speed + 30);
}

void ParticleSystem::SetSpread(int spread)
{
    m_spread = std::max(spread, 1);
}

void ParticleSystem::SetDirection(int direction)
{
    m_direction = direction % 360;
}

void ParticleSystem::SetCount(unsigned int count)
{
    m_count = count;

    m_quads.resize(m_count * 4);
    m_positions.resize(m_count);
    m_velocities.resize(m_count);
    m_lifetimes.resize(m_count);

    for (std::size_t i = 0; i < m_count; ++i)
    {
        ResetQuad(i);
    }
}

void ParticleSystem::Initialize()
{
    //Setup emitter/attractor
    m_attractorPosition.x = m_window.getSize().x / 2.f + 100.f;
    m_attractorPosition.y = m_window.getSize().y / 2.f;
    m_attractorShape.setOutlineColor(sf::Color::Red);
    m_attractorShape.setFillColor(sf::Color::Transparent);
    m_attractorShape.setRadius(10.f);
    m_attractorShape.setOutlineThickness(-4.f);
    m_attractorShape.setOrigin(m_attractorShape.getGlobalBounds().width / 2, m_attractorShape.getGlobalBounds().height / 2);
    m_attractorShape.setPosition(m_attractorPosition);

    m_emitterPosition.x = m_window.getSize().x / 2.f - 100.f;
    m_emitterPosition.y = m_window.getSize().y / 2.f;
    m_emitterShape.setOutlineColor(sf::Color::Green);
    m_emitterShape.setFillColor(sf::Color::Transparent);
    m_emitterShape.setRadius(10.f);
    m_emitterShape.setOutlineThickness(-4.f);
    m_emitterShape.setOrigin(m_emitterShape.getGlobalBounds().width / 2, m_emitterShape.getGlobalBounds().height / 2);
    m_emitterShape.setPosition(m_emitterPosition);

    //Create render texture
    m_renderTexture.create(m_window.getSize().x, m_window.getSize().y);

    //Create data arrays
    m_positions.resize(m_count);
    m_velocities.resize(m_count);
    m_lifetimes.resize(m_count);
    m_quads.setPrimitiveType(sf::Quads);
    m_quads.resize(m_count * 4);

    //Initialize particles
    for (std::size_t i = 0; i < m_count; ++i)
    {
        ResetQuad(i);
    }
}

void ParticleSystem::Shutdown()
{
    m_quads.clear();
    m_positions.clear();
    m_velocities.clear();
    m_lifetimes.clear();
}

bool ParticleSystem::ProcessEvent(sf::Event& event)
{
    bool result = false;

    sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        SetEmitterPosition(mousePos);
        result = true;
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
    {
        SetAttractorPosition(mousePos);
        result = true;
    }

    return result;
}

void ParticleSystem::Update(float dt)
{
    m_vShader.setUniform("storm_position", m_attractorPosition);

    for (std::size_t i = 0; i < m_count; ++i)
    {
        m_lifetimes[i] -= sf::seconds(dt);

        if (m_lifetimes[i] <= sf::Time::Zero)
        {
            SetColor(sf::Color::Transparent, i);
            ResetQuad(i);
        }

        m_color.r = static_cast<sf::Uint8>((1 + sin(m_clock.getElapsedTime().asSeconds() * 0.1)) * 128.f);
        m_color.g = static_cast<sf::Uint8>((1 + sin(m_clock.getElapsedTime().asSeconds() * 0.5)) * 128.f);
        m_color.b = static_cast<sf::Uint8>((1 + sin(m_clock.getElapsedTime().asSeconds() * 0.8)) * 128.f);
        m_color.a = static_cast<sf::Uint8>((m_lifetimes[i].asSeconds() / m_maxLifetime.asSeconds()) * 255);

        m_attractorForce = Normalize(m_attractorPosition - m_positions[i]);

        m_velocities[i] += m_gravityForce * m_gravityStrength;
        m_velocities[i] += m_attractorForce * m_attractorStrength;

        m_positions[i] += m_velocities[i] * dt;

        SetColor(m_color, i);
        SetPosition(m_positions[i], i);
    }
}

void ParticleSystem::Render()
{
    m_renderTexture.clear();
    m_renderTexture.draw(m_quads, &m_vShader);
    m_renderTexture.display();
    m_sprite.setTexture(m_renderTexture.getTexture());

    m_window.draw(m_sprite, &m_fShader);
    m_window.draw(m_emitterShape);
    m_window.draw(m_attractorShape);
}

sf::Vector2f ParticleSystem::Normalize(sf::Vector2f vector)
{
    float magnitude = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));

    if (magnitude != 0)
    {
        return sf::Vector2f(vector.x / magnitude, vector.y / magnitude);
    }
    else
    {
        return vector;
    }
}

void ParticleSystem::SetPosition(sf::Vector2f pos, std::size_t i)
{
    m_quads[(i * 4) + 0].position = sf::Vector2f(pos.x, pos.y);
    m_quads[(i * 4) + 1].position = sf::Vector2f(pos.x + m_quadSize.x, pos.y);
    m_quads[(i * 4) + 2].position = sf::Vector2f(pos.x + m_quadSize.x, pos.y + m_quadSize.y);
    m_quads[(i * 4) + 3].position = sf::Vector2f(pos.x, pos.y + m_quadSize.y);
}

void ParticleSystem::SetColor(sf::Color col, std::size_t i)
{
    m_quads[i * 4 + 0].color = col;
    m_quads[i * 4 + 1].color = col;
    m_quads[i * 4 + 2].color = col;
    m_quads[i * 4 + 3].color = col;
}

void ParticleSystem::ResetQuad(std::size_t i)
{
    int deg = ((std::rand() % m_spread) - (m_spread / 2)) + m_direction;
    float rad = (deg - 90 % 360) * 3.14f / 180.f; //-90 to sets 360 up on screen
    float speed = static_cast<float>((std::rand() % m_maxSpeed - m_minSpeed) + m_minSpeed);

    m_positions[i] = m_emitterPosition;
    m_velocities[i] = sf::Vector2f(std::cos(rad) * speed, std::sin(rad) * speed);
    m_lifetimes[i] = sf::milliseconds((std::rand() % m_maxLifetime.asMilliseconds()) + m_minLifetime.asMilliseconds());

    SetPosition(m_positions[i], i);
    SetColor(sf::Color::White, i);
}