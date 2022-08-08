// sfml
#include <SFML/Graphics.hpp>
// box 2d
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
// std
#include <vector>
#include <cstdlib>
#include <iostream>

#define PI 3.1415926535898

class Asteroid 
{
public:
    Asteroid(sf::Vector2f position, sf::Vector2f speed, b2World& physicWorld)
    {
        std::vector<sf::Vector2f> dots = GenerateShape(30, 60);
    	ShapeRepresentation = dots;
    	std::cout  << dots.size() << std::endl;
    	
        //graphics plate 
        VisibleShape = sf::ConvexShape(dots.size());

        b2Vec2* points = new b2Vec2[dots.size()];
        for (int i = 0; i < dots.size(); ++i)
        {
			VisibleShape.setPoint(i, dots[i]);
            points[i] = b2Vec2(dots[i].x, dots[i].y);
        }
		VisibleShape.setOutlineColor(sf::Color::Red);
        VisibleShape.setOutlineThickness(1);
        VisibleShape.setFillColor(sf::Color::Blue);
        VisibleShape.setPosition(position);

        // physics plate
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(position.x, position.y);
        bodyDef.linearVelocity.Set(speed.x, speed.y);
		b2Body* body = physicWorld.CreateBody(&bodyDef);
		b2PolygonShape dynamicBox;
		dynamicBox.Set(points, dots.size());

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.5f;
        fixtureDef.restitution = 0.9;
		body->CreateFixture(&fixtureDef);
        PhysicalShape = body;
    }
	
	std::vector<Asteroid> destroy()
    {
        /*
    	const int step = ShapeRepresentation.size() / 3 + 1;
    	if 

    	std::vector<Asteroid>
    	std::vector<sf::Vector2f> tmp;

    	for (int i = 0; i < ShapeRepresentation.size(); i++)
    	{
    		if 
    		ShapeRepresentation[i];
    	}
	    */
    }
	
    void update()
    {
        const b2Vec2 position = PhysicalShape->GetPosition();
        const float angle = PhysicalShape->GetAngle();
        const float angledeg = (angle / 3.14) * 180.f;
        VisibleShape.setPosition(sf::Vector2f(position.x, position.y));
        VisibleShape.setRotation(angledeg);
    }
    sf::ConvexShape getShape() {return VisibleShape;}

private:
    // shape
    sf::ConvexShape VisibleShape;
    b2Body* PhysicalShape;
    // worlds
    sf::RenderWindow* window;
    std::vector<sf::Vector2f> ShapeDots;
	std::vector<sf::Vector2f> ShapeRepresentation;

	int GetRandomDotsCount(float Radius)
    {
        const int Spred = 2;
        const int RValue = int(2 * Radius * PI / 40.f);
        const int MinDotsCount = RValue - Spred > 3 ? RValue - Spred : 3;
        const int MaxDotsCount = RValue + Spred;
		const int DotsCount = rand() % (MaxDotsCount - MinDotsCount) + MinDotsCount;
        return DotsCount;
	} 
    std::vector<sf::Vector2f> GetRandomDotsArr(float Radius, int DotsCount)
    {
		float RandomDotArea = Radius * sin(PI / float(DotsCount));
		float step = 360.f / float(DotsCount);
		sf::Vector2f tmp;
		std::vector<sf::Vector2f> DotsArr = std::vector<sf::Vector2f>(DotsCount);
		std::cout << "Generate New convex"  << std:: endl;
		for (float i=0; i < DotsCount; i++) {
			tmp.x = (float)Radius * sin(2*PI*i*step/360.f);
			tmp.y = (float)Radius * cos(2*PI*i*step/360.f);
			const sf::Vector2f tmp2 = GetRandomPositionInArea(RandomDotArea / 2);
			DotsArr[i] = tmp + tmp2;
			std::cout << i << " X:" << DotsArr[i].x << " Y:" << DotsArr[i].y << std::endl;
		}
        return DotsArr;
    }

    sf::Vector2f GetRandomPositionInArea(float Radius)
    {
        sf::Vector2f output = sf::Vector2f();

        const float XMax = Radius;
        const float XMin = -1.f * Radius;
        output.x = RandomValue(XMin, XMax);

        const float YMax = sqrt(Radius * Radius - output.x * output.x);
        const float YMin = -1.f * sqrt(Radius * Radius - output.x * output.x);
        output.y = RandomValue(YMin, YMax);

        return output;
    }
    float RandomValue(float From, float Till)
    {
        return From + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(Till-From)));
    }

    // Shape Generation
    std::vector<sf::Vector2f> GenerateShape(float MinRadius, float MaxRadius)
    {
        float Radius = RandomValue(MinRadius, MaxRadius);
        int DotsCount = GetRandomDotsCount(Radius);
        std::vector<sf::Vector2f> DotsArr = GetRandomDotsArr(Radius, DotsCount);
        return DotsArr;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    
    // create world
    b2Vec2 gravity(0.0f, 0.1f);
    b2World world(gravity);
    // create ground body
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(200.0f, 410.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(200.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);
    
    auto circle = Asteroid(sf::Vector2f(200, 200), sf::Vector2f(0, 1), world);
    auto circle2 = Asteroid(sf::Vector2f(200, 370), sf::Vector2f(0, -1), world);

    std::vector<Asteroid> Asteroids;

    Asteroids.push_back(circle);
    Asteroids.push_back(circle2);

	const float timeStep = 1.0f / 60.0f;
	const int32 velocityIterations = 100;
	const int32 positionIterations = 100;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonReleased)
            {
                const Asteroid tmp = Asteroid(sf::Vector2f(sf::Mouse::getPosition(window)), sf::Vector2f(0, 0), world);
                Asteroids.push_back(tmp);
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }


        world.Step(timeStep, velocityIterations, positionIterations);
        
        window.clear();

        for (auto ast : Asteroids)
        {
            ast.update();
            window.draw(ast.getShape());
        }
        window.display();
    }

    return 0;
}

