// sfml
#include <SFML/Graphics.hpp>
// std
#include <cmath>
#include <vector>
#include <iostream>

class Unit
{
public:
    sf::CircleShape shape_;
    float max_speed_ = 0.1f;
    float unit_size = 20.f;
    bool is_selected = false;
    
    sf::Vector2f current_position_;
    sf::Vector2f target_position_;
    
public:
    explicit Unit(sf::Vector2f in_position)
    {
        current_position_ = in_position;
        target_position_ = in_position;
        
        shape_ = sf::CircleShape(unit_size);
        shape_.setFillColor(sf::Color::Blue);
        shape_.setOutlineThickness(2);
    }

    sf::Vector2f GetPosition() const { return current_position_; }
    bool IsSelected() const { return is_selected; }
    float GetSize() const { return unit_size; }
    void Select() { is_selected = true; }
    void Unselect() { is_selected = false; }
    void Move( sf::Vector2f delta) { current_position_+= delta; }
    
    ~Unit()
    {
        std::cout << "Unit is destroyed" << std::endl;
    }

    
    void set_target(const sf::Vector2f& in_target)
    {
        target_position_ = in_target;
    }
    sf::CircleShape& get_shape()
    {
        return shape_;
    }
    void update()
    {
        if (current_position_ != target_position_)
        {
            const sf::Vector2f distance_vector = target_position_ - current_position_;
            const auto vector_length = static_cast<float>(sqrt(pow(distance_vector.x, 2) +
                                                               pow(distance_vector.y, 2)));
            if (vector_length > unit_size / 2.f)
            {
                const sf::Vector2f delta_vector = (distance_vector / vector_length) * max_speed_;
                current_position_ += delta_vector;
            }
        }
        if (is_selected)
        {
            shape_.setOutlineColor(sf::Color::White);
        }
        else
        {
            shape_.setOutlineColor(sf::Color::Transparent);
        }
        shape_.setPosition(sf::Vector2f(current_position_.x - unit_size / 2, current_position_.y - unit_size / 2));
    }
    
};

sf::Vector2f GetDirectionVector(const sf::Vector2f& in_vector)
{
    const float scalar = sqrt(pow(in_vector.x, 2) + pow(in_vector.y, 2));
    return in_vector / scalar;
}

float GetVectorLength(const sf::Vector2f& in_Vector)
{
    return sqrt(pow(in_Vector.x, 2) +  pow(in_Vector.y, 2));
}


void ResolveCollisions(Unit& lhunit, Unit& rhunit)
{
    const sf::Vector2f current_vector_distance = lhunit.target_position_ - rhunit.target_position_;
    const float desired_scalar_distance = lhunit.GetSize() + rhunit.GetSize();
    const float current_scalar_distance = GetVectorLength(current_vector_distance);
    if (current_scalar_distance < desired_scalar_distance)
    {
        const float delta_distance = desired_scalar_distance - current_scalar_distance;
        
        sf::Vector2f direction_vector = sf::Vector2f(1, 0); 
        if (current_scalar_distance > 0.001f)
        {
            direction_vector = GetDirectionVector(current_vector_distance); 
        }
        else
        {
            direction_vector = GetDirectionVector(lhunit.GetPosition() - rhunit.GetPosition());
        }
        direction_vector *= delta_distance/2;
        
        lhunit.target_position_ += direction_vector;
        rhunit.target_position_ -= direction_vector;
    }
}

int main()
{
    int ScreenWidth = 800;
    int ScreenHeight = 600;

    
    sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "SFML works!");

    
    sf::RectangleShape HighlightBox(sf::Vector2f(10, 10));
    HighlightBox.setPosition(0, 0);
    HighlightBox.setFillColor(sf::Color::Transparent);
    HighlightBox.setOutlineThickness(1);
    HighlightBox.setOutlineColor(sf::Color::White);
    bool HighlightBoxActive = false;
    
    std::vector<Unit> UnitsList;
    UnitsList.push_back(Unit(sf::Vector2f(30, 30)));
    UnitsList.push_back(Unit(sf::Vector2f(50, 30)));
    UnitsList.push_back(Unit(sf::Vector2f(50, 30)));
    UnitsList.push_back(Unit(sf::Vector2f(50, 30)));
    UnitsList.push_back(Unit(sf::Vector2f(50, 30)));
    UnitsList.push_back(Unit(sf::Vector2f(50, 30)));
    UnitsList.push_back(Unit(sf::Vector2f(50, 30)));
    UnitsList.push_back(Unit(sf::Vector2f(50, 30)));
    UnitsList.push_back(Unit(sf::Vector2f(50, 30)));
    UnitsList.push_back(Unit(sf::Vector2f(50, 30)));

    while (window.isOpen())
    {
        auto event = sf::Event();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            {
                auto MousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
                for (Unit& unit : UnitsList)
                {
                    if (unit.IsSelected())
                    {
                        unit.set_target(MousePosition);
                    }
                }
            }
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                sf::Vector2i MousePosition = sf::Mouse::getPosition(window);
                if (!HighlightBoxActive)
                {
                    HighlightBox.setPosition(sf::Vector2f(MousePosition));
                    HighlightBoxActive = true;
                    for (Unit& unit : UnitsList)
                    {
                        unit.Unselect();
                    }
                }
                else
                {
                    HighlightBox.setSize(sf::Vector2f(MousePosition) - HighlightBox.getPosition());
                }
            }
            else
            {
                for (Unit& unit : UnitsList)
                {
                    const sf::Vector2f UnitPosition = unit.GetPosition();
                    if (HighlightBox.getSize().x > 0)
                    {
                        if (UnitPosition.x > HighlightBox.getPosition().x && UnitPosition.x < HighlightBox.getPosition().x + HighlightBox.getSize().x)
                        {
                            
                        }
                        else
                        {
                            continue;
                        }
                    }
                    else
                    {
                        if (UnitPosition.x > HighlightBox.getPosition().x + HighlightBox.getSize().x && UnitPosition.x < HighlightBox.getPosition().x)
                        {
                            
                        }
                        else
                        {
                            continue;
                        }
                        
                    }

                    if (HighlightBox.getSize().y > 0)
                    {
                        if (UnitPosition.y > HighlightBox.getPosition().y && UnitPosition.y < HighlightBox.getPosition().y + HighlightBox.getSize().y)
                        {
                            unit.Select();        
                        }
                    }
                    else
                    {
                        if (UnitPosition.y > HighlightBox.getPosition().y + HighlightBox.getSize().y && UnitPosition.y < HighlightBox.getPosition().y)
                        {
                            unit.Select();        
                        }
                    }
                }
                HighlightBox.setPosition(0, 0);
                HighlightBox.setSize(sf::Vector2f(0, 0));
                HighlightBoxActive = false;
            }
        }

        for (size_t i = 0; i < UnitsList.size(); i++)
        {
            for (size_t j = i + 1; j < UnitsList.size(); j++)
            {
                ResolveCollisions(UnitsList[i], UnitsList[j]);
            }
        }
        window.clear();
        window.draw(HighlightBox);
        
        for (Unit& unit : UnitsList)
        {
            unit.update();
            window.draw(unit.get_shape());
        }
        
        window.display();
    }

    return 0;
}
