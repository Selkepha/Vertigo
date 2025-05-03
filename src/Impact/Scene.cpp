#include "Scene.h"
#include "Manifold.h"

namespace Impact
{
	Scene::Scene(void)
	{
	}

	Scene::~Scene(void)
	{
	}

	/* ----- Public Static Wrappers ----- */
	void Scene::Step(float dt) { Get().hiddenStep(dt); };

	void Scene::DebugDraw(sf::RenderWindow* window) { Get().hiddenDebugDraw(window); };

	void Scene::SetGravity(Vec2 vector) { Get().hiddenSetGravity(vector); };

	void Scene::SetDrag(float coefficient) { Get().hiddenSetDrag(coefficient); };

	void Scene::SetIterations( int iterations) { Get().hiddenSetIterations(iterations); };


	/* ----- Hidden Methods ----- */

	void Scene::hiddenStep(float dt)
	{
		if(Rigidbody::allRigidbodies.size() == 0) { return; };

		//Step Velocities
		for(int i = 0; i < Rigidbody::allRigidbodies.size(); i++)
		{
			Rigidbody* b = Rigidbody::allRigidbodies[i];
			if(b->IsKinematic()) { continue; }; //Skip kinematic bodies!
			b->velocity += m_Gravity * dt; //gravity
			b->velocity *= 1 - (m_Drag * dt); //drag (air resistance)
			b->position += b->velocity * dt; //step position
		}

		BoxIn(Vec2(800, 600));

		//Manage collisions!
		for(int iterations = 0; iterations < m_Iterations; iterations++)
		{
			for(int i = 0; i < Rigidbody::allRigidbodies.size() - 1; i++)
			{
				for(int j = i + 1; j < Rigidbody::allRigidbodies.size(); j++)
				{
					Manifold m = Manifold(Rigidbody::allRigidbodies[i], Rigidbody::allRigidbodies[j]);
					m.Solve();
				}
			}
		}
	}

	void Scene::hiddenDebugDraw(sf::RenderWindow* window)
	{
		if(Rigidbody::allRigidbodies.size() == 0) { return; };

		sf::CircleShape circle(50.0f);
		// circle.setFillColor(sf::Color::Cyan);
		sf::ConvexShape poly;

		for(int i = 0; i < Rigidbody::allRigidbodies.size(); i++)
		{
			Impact::Rigidbody* b = Rigidbody::allRigidbodies[i];
			Impact::Shape* bodyShape = b->GetShape();

			//Circles
			int vertexCount = bodyShape->vertices.size();
			if(vertexCount == 0)
			{
				float radius = bodyShape->radius;
				circle.setRadius(radius);
				Impact::Vec2 pos = b->position;
				circle.setPosition({pos.x - radius, pos.y - radius}); //-pos.y ? because sfml y+ is down?
				window->draw(circle);
			}
			else 	//Polygons
			{
				poly.setPointCount(vertexCount);

				for(int i = 0; i < vertexCount; i++)
				{
					Impact::Vec2 vertex = bodyShape->vertices[i];
					vertex += b->position;
					poly.setPoint(i, sf::Vector2f(vertex.x, vertex.y));
				}
				window->draw(poly);
			}
		}
	}

	void Scene::hiddenSetGravity(Vec2 vector)
	{
		m_Gravity = vector;
	}

	void Scene::hiddenSetDrag(float coefficient)
	{
		m_Drag = coefficient;
	}

	void Scene::hiddenSetIterations( int iterations)
	{
		m_Iterations = iterations;
	}

	void Scene::BoxIn(Vec2 dimensions)
	{
		for(int i = 0; i < Rigidbody::allRigidbodies.size(); i++)
		{
			Impact::Rigidbody* b = Rigidbody::allRigidbodies[i];
			float x = b->position.x;
			float y = b->position.y;

			if(x > dimensions.x)
			{
				b->velocity.x = -abs(b->velocity.x);
				b->position.x = dimensions.x;
			} else if (x < 0)
			{
				b->velocity.x = abs(b->velocity.x);
				b->position.x = 0;
			}

			if(y > dimensions.y)
			{
				b->velocity.y = -abs(b->velocity.y);
				b->position.y = dimensions.y;
			} else if (y < 0)
			{
				b->velocity.y = abs(b->velocity.y);
				b->position.y = 0;
			}
		}
	}
}