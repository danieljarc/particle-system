#include "Application.h"
#include "GUISlider.h"
#include "ResourceManager.h"

#include <iostream>
#include <iomanip>

Application::Application() :
    m_fpsLabel("FPS: 0.0", m_style),
    m_fps(0.f),
    m_frameCount(0),
    m_particleSystem(m_window)
{
    //Seed random
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //Get resolution
    sf::Vector2i resolution = sf::Vector2i(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

    //Create window
    m_window.create(sf::VideoMode(resolution.x - 400, resolution.y - 400), "Particle System Demo", sf::Style::Close);
    m_window.setPosition(sf::Vector2i(resolution.x / 2 - m_window.getSize().x / 2, resolution.y / 2 - m_window.getSize().y / 2));

    //Create control panel
    m_controls.SetPadding(0.f, 0.f, 0.f, 0.f);
    m_controls.SetSpacing(0.f, 0.f);
    m_controls.move(10.f, 10.f);

    m_fpsLabel.SetTextColor(sf::Color::White);
    m_fpsLabel.SetBackgroundColor(sf::Color::Transparent);
    m_fpsLabel.setPosition(m_window.getSize().x - 120.f, 20.f);

    //Direction Slider
    auto slider1Label = std::make_shared<GUILabel>("Direction:", m_style);
    slider1Label->SetSize(140.f, 40.f);

    auto slider1Value = std::make_shared<GUILabel>("360", m_style);
    slider1Value->SetSize(80.f, 40.f);

    auto slider1 = std::make_shared<GUISlider>(m_style);
    slider1->SetSize(200.f, 40.f);
    slider1->SetValue(1.f);
    slider1->OnMove = [this, slider1Value](float value)
    {
        unsigned int direction = static_cast<unsigned int>(value * 360);
        std::stringstream text;
        text << direction;
        slider1Value->SetText(text.str());
        m_particleSystem.SetDirection(direction);
    };

    auto slider1Container = std::make_shared<GUILayout>(GUIOrientation::Horizontal);
    slider1Container->SetPadding(0.f, 0.f, 0.f, 0.f);
    slider1Container->SetSpacing(0.f, 0.f);

    slider1Container->Add(slider1Label);
    slider1Container->Add(slider1);
    slider1Container->Add(slider1Value);
    slider1Container->Build();

    //Spread Slider
    auto slider2Label = std::make_shared<GUILabel>("Spread:", m_style);
    slider2Label->SetSize(140.f, 40.f);

    auto slider2Value = std::make_shared<GUILabel>("360", m_style);
    slider2Value->SetSize(80.f, 40.f);

    auto slider2 = std::make_shared<GUISlider>(m_style);
    slider2->SetSize(200.f, 40.f);
    slider2->SetValue(1.f);
    slider2->OnMove = [this, slider2Value](float value)
    {
        unsigned int spread = static_cast<unsigned int>(value * 360);
        std::stringstream text;
        text << spread;
        slider2Value->SetText(text.str());
        m_particleSystem.SetSpread(spread);
    };

    auto slider2Container = std::make_shared<GUILayout>(GUIOrientation::Horizontal);
    slider2Container->SetPadding(0.f, 0.f, 0.f, 0.f);
    slider2Container->SetSpacing(0.f, 0.f);

    slider2Container->Add(slider2Label);
    slider2Container->Add(slider2);
    slider2Container->Add(slider2Value);
    slider2Container->Build();

    //Speed Slider
    auto slider3Label = std::make_shared<GUILabel>("Speed:", m_style);
    slider3Label->SetSize(140.f, 40.f);

    auto slider3Value = std::make_shared<GUILabel>("250", m_style);
    slider3Value->SetSize(80.f, 40.f);

    auto slider3 = std::make_shared<GUISlider>(m_style);
    slider3->SetSize(200.f, 40.f);
    slider3->SetValue(0.5f);
    slider3->OnMove = [this, slider3Value](float value)
    {
        unsigned int speed = static_cast<unsigned int>(value * 500); //500 = max limit
        std::stringstream text;
        text << speed;
        slider3Value->SetText(text.str());
        m_particleSystem.SetSpeed(speed);
    };

    auto slider3Container = std::make_shared<GUILayout>(GUIOrientation::Horizontal);
    slider3Container->SetPadding(0.f, 0.f, 0.f, 0.f);
    slider3Container->SetSpacing(0.f, 0.f);

    slider3Container->Add(slider3Label);
    slider3Container->Add(slider3);
    slider3Container->Add(slider3Value);
    slider3Container->Build();

    //Gravity Slider
    auto slider4Label = std::make_shared<GUILabel>("Gravity:", m_style);
    slider4Label->SetSize(140.f, 40.f);

    auto slider4Value = std::make_shared<GUILabel>("0.0", m_style);
    slider4Value->SetSize(80.f, 40.f);

    auto slider4 = std::make_shared<GUISlider>(m_style);
    slider4->SetSize(200.f, 40.f);
    slider4->SetValue(0.f);
    slider4->OnMove = [this, slider4Value](float value)
    {
        float strength = value * 5.f;
        std::stringstream text;
        text << std::fixed << std::setprecision(1) << strength;
        slider4Value->SetText(text.str());
        m_particleSystem.SetGravityStrength(strength);
    };

    auto slider4Container = std::make_shared<GUILayout>(GUIOrientation::Horizontal);
    slider4Container->SetPadding(0.f, 0.f, 0.f, 0.f);
    slider4Container->SetSpacing(0.f, 0.f);

    slider4Container->Add(slider4Label);
    slider4Container->Add(slider4);
    slider4Container->Add(slider4Value);
    slider4Container->Build();

    //Attractor Slider
    auto slider5Label = std::make_shared<GUILabel>("Attractor:", m_style);
    slider5Label->SetSize(140.f, 40.f);

    auto slider5Value = std::make_shared<GUILabel>("0.0", m_style);
    slider5Value->SetSize(80.f, 40.f);

    auto slider5 = std::make_shared<GUISlider>(m_style);
    slider5->SetSize(200.f, 40.f);
    slider5->SetValue(0.f);
    slider5->OnMove = [this, slider5Value](float value)
    {
        float strength = value * 10.f;
        std::stringstream text;
        text << std::fixed << std::setprecision(1) << strength;
        slider5Value->SetText(text.str());
        m_particleSystem.SetAttractorStrength(strength);
    };

    auto slider5Container = std::make_shared<GUILayout>(GUIOrientation::Horizontal);
    slider5Container->SetPadding(0.f, 0.f, 0.f, 0.f);
    slider5Container->SetSpacing(0.f, 0.f);

    slider5Container->Add(slider5Label);
    slider5Container->Add(slider5);
    slider5Container->Add(slider5Value);
    slider5Container->Build();

    //Count Slider
    auto slider6Label = std::make_shared<GUILabel>("Count:", m_style);
    slider6Label->SetSize(140.f, 40.f);

    auto slider6Value = std::make_shared<GUILabel>("10000", m_style);
    slider6Value->SetSize(80.f, 40.f);

    auto slider6 = std::make_shared<GUISlider>(m_style);
    slider6->SetSize(200.f, 40.f);
    slider6->SetValue(0.5f);
    slider6->OnMove = [this, slider6Value](float value)
    {
        unsigned int count = static_cast<unsigned int>(value * 20000.f); //20000 = max limit
        std::stringstream text;
        text << count;
        slider6Value->SetText(text.str());
        m_particleSystem.SetCount(count);
    };

    auto slider6Container = std::make_shared<GUILayout>(GUIOrientation::Horizontal);
    slider6Container->SetPadding(0.f, 0.f, 0.f, 0.f);
    slider6Container->SetSpacing(0.f, 0.f);

    slider6Container->Add(slider6Label);
    slider6Container->Add(slider6);
    slider6Container->Add(slider6Value);
    slider6Container->Build();

    //Build Panel
    m_controls.Add(slider2Container);
    m_controls.Add(slider1Container);
    m_controls.Add(slider3Container);
    m_controls.Add(slider4Container);
    m_controls.Add(slider5Container);
    m_controls.Add(slider6Container);
    m_controls.Build();

    m_particleSystem.Initialize();
}

Application::~Application()
{
}

void Application::Run()
{
    sf::Clock clock;
    sf::Time dt; 
    sf::Event event;

    while (m_window.isOpen())
    {
        dt = clock.restart();

        while (m_window.pollEvent(event))
        {
            ProcessEvent(event);
        }

        Update(dt.asSeconds());
        Render();
    }
}

void Application::ProcessEvent(sf::Event& event)
{
    if (event.type == sf::Event::Closed)
    {
        m_window.close();
    }
    else
    {
        if (!m_controls.ProcessEvent(event))
        {
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left)
            {
                sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                m_particleSystem.SetEmitterPosition(mousePos);
            }
            
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Right)
            {
                sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                m_particleSystem.SetAttractorPosition(mousePos);
            }
        }
    }
}

void Application::Update(float dt)
{
    m_frameCount++;
    m_fpsTimer += sf::seconds(dt);

    if (m_fpsTimer.asSeconds() >= 1.f)
    {
        m_stream.str("");
        m_stream.clear();
        m_stream << "FPS: " << m_frameCount;
        m_fpsLabel.SetText(m_stream.str());
        m_frameCount = 0;
        m_fpsTimer = sf::Time::Zero;
    }

    m_particleSystem.Update(dt);
}

void Application::Render()
{
    m_window.clear();
    m_particleSystem.Render();
    m_window.draw(m_controls);
    m_window.draw(m_fpsLabel);
    m_window.display();
}
