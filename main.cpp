
#include <functional>
#include <exception>
#include <iostream>
#include "GameManager.h"


GameManager *app;

bool callbackFunc(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
{
	GameObject* go = static_cast<GameObject*>(colObj0Wrap->getCollisionObject()->getUserPointer());
	if (go)
	{
		go->m_hit = true;
	}
	

	return false;
}


void __keyboard(unsigned char key, int x, int y)
{
	app->keyboard(key, x, y);
}

bool pressed = false;
void __mouse_button(int button, int state, int x, int y) 
{
	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			pressed = false;
			app->mouse_release(button, state, x, y);
		}
		else  {// state = GLUT_DOWN
			pressed = true;
			app->mouse_press(button, state, x, y);
		}
	}
}

void __mouse_move(int x, int y) {

	app->mouse_move(x, y);
}

void __update()
{
	app->update();
}


void __display()
{
	auto fp = std::bind(&GameManager::display, app);
	Graphics::Display(fp);
}

void __reshape(int w, int h)
{
	Graphics::Reshape(w, h);
};





void __callbacks()
{
	gContactAddedCallback=callbackFunc;

	glutKeyboardFunc(__keyboard);
	glutDisplayFunc(__display);
	glutReshapeFunc(__reshape);
	glutIdleFunc(__update);

	// here are the two new functions
	glutMouseFunc(__mouse_button);
	glutMotionFunc(__mouse_move);

}

int main(int argc, char** argv)
{
	try
	{
		Graphics *gl = new Graphics(argc, argv, "Test");
		app = new GameManager();
		Graphics::EnableTexture();
		Graphics::EnableLight();
		app->init();
		__callbacks();
		app->run();

	}
	catch (std::exception& e)
	{
		std::cout << " error " << &e << std::endl;
		std::cin.ignore();
	}

	return EXIT_SUCCESS;
}
