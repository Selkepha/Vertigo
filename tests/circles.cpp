
#include "Vertigo/Vertigo.h" //Include Vertigo game engine (includes SFML/Graphics.hpp)

class Game : public App
{
	//We need a window
	sf::RenderWindow* window;

	//Physics
	Impact::Shape smallCircle;
	Impact::Shape mediumCircle;
	Impact::Shape bigCircle;
	Impact::Material idealish;

	void OnStart()
	{
		window = new sf::RenderWindow(sf::VideoMode({800, 600}), "SFML works!");

		smallCircle = Impact::Shape(10.0f);
		mediumCircle = Impact::Shape(15.0f);
		bigCircle = Impact::Shape(20.0f);
		idealish = Impact::Material(0.9f, 0.0f, 0.0f, 1.0f);

		//Change scene physics
		Impact::Scene::SetGravity(Impact::Vec2(0.0f, 0.0f)); //98.81f));
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
        		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) // Keyboard inputs
        		{
        		    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
        		        window->close();
				}

				if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
				{
					if (mouseButtonPressed->button == sf::Mouse::Button::Left)
					{
						static unsigned int count = 0;
						Impact::Rigidbody* newBody;
						if(count % 3 == 0)
						{
							newBody = new Impact::Rigidbody(&bigCircle, &idealish);
						}
						else if (count % 3 == 1)
						{
							newBody = new Impact::Rigidbody(&mediumCircle, &idealish);
						}
						else
						{
							newBody = new Impact::Rigidbody(&smallCircle, &idealish);
						}
						newBody->position = Impact::Vec2(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
						count++;
					}
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