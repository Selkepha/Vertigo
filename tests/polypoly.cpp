
#include "Vertigo/Vertigo.h" //Include Vertigo game engine (includes SFML/Graphics.hpp)

class Game : public App
{
	//We need a window
	sf::RenderWindow* window;

	//Physics
	Impact::Shape polyShape;
	Impact::Material ideal;

	void OnStart()
	{
		window = new sf::RenderWindow(sf::VideoMode({800, 600}), "SFML works!");

		//Shapes
		std::vector<Impact::Vec2> vertices = {
			Impact::Vec2(45.0f, 40.0f),
			Impact::Vec2(60.0f, -40.0f),
			Impact::Vec2(-40.0f, -60.0f),
			Impact::Vec2(-55.0f, 50.0f)
		};
		polyShape = Impact::Shape(vertices);

		//Material
		ideal = Impact::Material(1.0f, 0.0f, 0.0f, 1.0f);

		//Rigidbodies
		Impact::Rigidbody* poly0 = new Impact::Rigidbody(&polyShape, &ideal);
		poly0->position = Impact::Vec2(100.0f, 500.0f);
		poly0->MakeKinematic();

		Impact::Rigidbody* poly1 = new Impact::Rigidbody(&polyShape, &ideal);
		poly1->position = Impact::Vec2(100.0f, 200.0f);

		//Change scene physics
		Impact::Scene::SetGravity(Impact::Vec2(0.0f, 98.81f));
	}

	void OnUpdate()
	{
		while(window->isOpen())
		{
			while (const std::optional event = window->pollEvent())
    		{
        		if (event->is<sf::Event::Closed>())
        		{
        		    window->close();
        		}
        		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        		{
        		    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
        		        window->close();
        		}
    		}
		}
	}

	void OnRender()
	{
		window->clear();
		Impact::Scene::DebugDraw(window);
        window->display();
	}

	void OnEnd()
	{
		window->close();
		delete window;
	}
};

App* GetApp(void)
{
	return new Game();
}