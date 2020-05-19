#pragma once

#include "GUIWidget.h"

class GUILayout : public GUIWidget
{
public:
    GUILayout(GUIOrientation orientation = GUIOrientation::Vertical, GUIWidget* parent = nullptr);
    ~GUILayout();

    bool Add(std::shared_ptr<GUIWidget> widget);
    bool Remove(std::shared_ptr<GUIWidget> widget);
    virtual bool ProcessEvent(const sf::Event& event) override;
    virtual void Build() override;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    GUIOrientation m_orientation;
    std::vector<std::shared_ptr<GUIWidget>> m_children;
};