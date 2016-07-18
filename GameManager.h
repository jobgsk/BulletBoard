#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "Vector3.h"
#include <vector>
#include "GameObject.h"
#include "Camera.h"
#include "PhysicsWorld.h"
#include "Graphics.h"
#include "converter.h"
#include "Player.h"



class GameManager  {

	std::vector<GameObject*> game_objects;
	Camera* camera;
	PhysicsWorld* physics_world;

	Player * player1;
	Player * player2;
	Player * player;

	TextRender * info1;
	TextRender * info2;
	TextRender * info3;

	int step = 0;
	bool gameover = false;
	
	float base_time;
public:

	GameObject * chip1_obj;
	GameObject * chip2_obj;
	GameObject * chip3_obj;

	GameObject * chip4_obj;
	GameObject * chip5_obj;
	GameObject * chip6_obj;

	GameObject * plaine_obj;
	GameObject * box_obj;

	GameManager()
	{
	
	};

	float grad_to_rad(float grad)
	{
		return (grad * 3.14) / 180;
	}

	void init()
	{
		physics_world = new PhysicsWorld();
		
		PlainePhysicsBody * plaine_body = new PlainePhysicsBody(0.0, 0.0, 0.0, 0.0);
		BoxPhysicsBody * box_body = new BoxPhysicsBody(15, 0.5, 6, 0, 0, 0, 100.0);
		//box_body->rotate(grad_to_rad(45), 0, 0);
		//box_body->rotate(grad_to_rad(0.1), 0, 0);

		//SpherePhysicsBody * sphere_body = new SpherePhysicsBody(1.0, 0, 15, 0, 1.0);

		CylinderPhysicsBody * chip1_body = new CylinderPhysicsBody(1, 1, 3, 0.5, 5, 2.0);
		CylinderPhysicsBody * chip2_body = new CylinderPhysicsBody(1, 1, 4, 0.5, 5, 1.0);
		CylinderPhysicsBody * chip3_body = new CylinderPhysicsBody(1, 1, 5, 0.5, 5, 0.5);

		CylinderPhysicsBody * chip4_body = new CylinderPhysicsBody(1.5, 1, 3, 0.5, -5, 2.0);
		CylinderPhysicsBody * chip5_body = new CylinderPhysicsBody(1.5, 1, 4, 0.5, -5, 1.0);
		CylinderPhysicsBody * chip6_body = new CylinderPhysicsBody(1.5, 1, 5, 0.5, -5, 0.5);

		СhipRender * chip1_render = new СhipRender(1.0, 0.0, 0.0, tanks::bullet_to_tanks(chip1_body->get_extent()));
		СhipRender * chip2_render = new СhipRender(0.0, 1.0, 0.0, tanks::bullet_to_tanks(chip2_body->get_extent()));
		СhipRender * chip3_render = new СhipRender(1.0, 1.0, 0.0, tanks::bullet_to_tanks(chip3_body->get_extent()));

		СhipRender * chip4_render = new СhipRender(1.0, 0.0, 0.0, tanks::bullet_to_tanks(chip4_body->get_extent()));
		СhipRender * chip5_render = new СhipRender(0.0, 1.0, 0.0, tanks::bullet_to_tanks(chip5_body->get_extent()));
		СhipRender * chip6_render = new СhipRender(1.0, 1.0, 0.0, tanks::bullet_to_tanks(chip6_body->get_extent()));

		PlaineRender * plaine_render = new PlaineRender(
			"Media/floor.bmp", 0.8, 0.8, 0.8, Vector3<float>(10, 0, 10));
		BoardRender * box_render = new BoardRender(
			"Media/board.bmp", 1.0, 0.0, 0.0, tanks::bullet_to_tanks(box_body->get_extent()));
		
		//GameObject * sphere_obj = new GameObject(sphere_body, sphere_render, 1);
		chip1_obj = new GameObject(chip1_body, chip1_render, 1);
		chip2_obj = new GameObject(chip2_body, chip2_render, 2);
		chip3_obj = new GameObject(chip3_body, chip3_render, 3);
		chip4_obj = new GameObject(chip4_body, chip4_render, 4);
		chip5_obj = new GameObject(chip5_body, chip5_render, 5);
		chip6_obj = new GameObject(chip6_body, chip6_render, 6);

		plaine_obj = new GameObject(plaine_body, plaine_render, 0);
		box_obj = new GameObject(box_body, box_render, 10);

		physics_world->add_body(plaine_obj);
		physics_world->add_body(box_obj);

		//physics_world->add_body(sphere_obj);
		physics_world->add_body(chip1_obj);
		physics_world->add_body(chip2_obj);
		physics_world->add_body(chip3_obj);
		physics_world->add_body(chip4_obj);
		physics_world->add_body(chip5_obj);
		physics_world->add_body(chip6_obj);

		game_objects.push_back(plaine_obj);
		game_objects.push_back(box_obj);

		//game_objects.push_back(sphere_obj);
		game_objects.push_back(chip1_obj);
		game_objects.push_back(chip2_obj);
		game_objects.push_back(chip3_obj);
		game_objects.push_back(chip4_obj);
		game_objects.push_back(chip5_obj);
		game_objects.push_back(chip6_obj);

		camera = new Camera(box_obj, 15.0);

		ArrowRender * player1_render = new ArrowRender(1.0, 0.0, 0.0, Vector3<float>(2, 0, 0.2));
		ArrowRender * player2_render = new ArrowRender(1.0, 0.0, 0.0, Vector3<float>(2, 0, 0.2));

		player1 = new Player(player1_render, chip1_obj);
		player2 = new Player(player2_render, chip4_obj);
		player = player1;

		info1 = new TextRender("Player 1: ", 50, 570);
		info2 = new TextRender("Player 2: ", 550, 570);
		info3 = new TextRender("Game over: ", 250, 250);
	}

	/*
		Run Game loop
	*/
	void run()
	{
		base_time = glutGet(GLUT_ELAPSED_TIME);
		Graphics::Run();
	}

	void display()
	{
		Vector3<float> c_position = camera->m_position;
		Vector3<float> c_direction = camera->m_orientation;
		Graphics::Camera(
			c_position.x, c_position.y, c_position.z,
			c_direction.x, c_direction.y, c_direction.z);

		for (int i = 0; i < game_objects.size(); i++)
		{
			game_objects[i]->render();
		}

		player->render();
		
		info1->concatenate(player1->score);
		info2->concatenate(player2->score);

		info1->render();
		info2->render();

		if (gameover)
		{
			if (player1->score > player2->score)
				info3->m_render_text = info3->m_init_text + " Player 1 win";
			else if (player1->score < player2->score)
				info3->m_render_text = info3->m_init_text + " Player 2 win";
			else
				info3->m_render_text = info3->m_init_text + " Dead heat";

			info3->render();
		}

	};

	/*
	update positions of all objects in the scene
	*/
	void update()
	{
		if (gameover)
			return;

		float time = glutGet(GLUT_ELAPSED_TIME);
		float delta = (time - base_time);

		if (1000.0 / 60 > delta)
			return;

		for (int i = 0; i<game_objects.size(); i++)
			game_objects[i]->m_hit = false;

		physics_world->run();
		bool done = player->update();
		if (done && step >= 6)
			gameover = true;
		Graphics::Redispaly();

		base_time = time;
	};

	/*
	handle keys events or pass them to the current scene
	*/
	void keyboard(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case 'q':
			chip1_obj->m_body->set_position(Vector3<float>(6, 1, 0));
			player1->set_chip(chip1_obj);
			player1->setup(0, 0);
			player = player1;
			step++;
			break;
		case 'w':
			chip2_obj->m_body->set_position(Vector3<float>(6, 1, 0));
			player1->set_chip(chip2_obj);
			player1->setup(0, 0);
			player = player1;
			step++;
			break;
		case 'e':
			chip3_obj->m_body->set_position(Vector3<float>(6, 1, 0));
			player1->set_chip(chip3_obj);
			player1->setup(0, 0);
			player = player1;
			step++;
			break;

		case 'a':
			chip4_obj->m_body->set_position(Vector3<float>(6, 1, 0));
			player2->set_chip(chip4_obj);
			player2->setup(0, 0);
			player = player2;
			step++;
			break;
		case 's':
			chip5_obj->m_body->set_position(Vector3<float>(6, 1, 0));
			player2->set_chip(chip5_obj);
			player2->setup(0, 0);
			player = player2;
			step++;
			break;
		case 'd':
			chip6_obj->m_body->set_position(Vector3<float>(6, 1, 0));
			player2->set_chip(chip6_obj);
			player2->setup(0, 0);
			player = player2;
			step++;
			break;
		};
	};

	void mouse_press(int button, int state, int x, int y)
	{
		player->setup(x, y);
	};

	void mouse_release(int button, int state, int x, int y)
	{
		std::cout << "shoot" << std::endl;
		player->shoot();
		player->setup(0, 0);
	};

	void mouse_move(int x, int y)
	{
		player->aim(x, y);
	};

	void quit()
	{
		for (int i = 0; i < game_objects.size(); i++)
		{
			physics_world->delete_body(game_objects[i]);
			delete game_objects[i];
		}

		delete physics_world;
		
		Graphics::Exit();
		exit(0);
	}

};

#endif /* GAME_MANAGER_H_ */

