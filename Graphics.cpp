#include <iostream>

#include "Graphics.h"

int Graphics::winid = -1;

Graphics::Graphics(int myargc, char** myargv, const char *app_name)
{
	glutInit(&myargc, myargv);

	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(600, 800);
	glutInitWindowPosition(100, 50);
	Graphics::winid = glutCreateWindow(app_name);

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	//glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	//glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Graphics::Reshape(int w, int h)
{
	/*if (h == 0)
	h = 1;
	float ratio = w * 1.0 / h;


	glMatrixMode(GL_PROJECTION);
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(65.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	*/
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the correct perspective.
	gluPerspective(60.0, (double)w / (double)h, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void Graphics::Camera(float cx, float cy, float cz, float px, float py, float pz)
{

	/*std::cout << " Camera cx " << cx
	<< " cy " << cy
	<< " cz " << cz
	<< " px " << px
	<< " py " << py
	<< " pz " << pz << std::endl;
	*/
	// Set the camera position and lookat point
	gluLookAt(cx, cy, cz,   // Camera position
		px, py, pz,    // Look at point
		0.0, 1.0, 0.0);   // Up vector

}

void Graphics::Display(std::function<void()> dispaly)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	dispaly();

	// Update the displayed content.
	glFlush();
	glutSwapBuffers();
}

void Graphics::Redispaly()
{
	glutPostRedisplay();
}

void Graphics::EnableTexture()
{
	glEnable(GL_TEXTURE_2D);	// Enable Texture Mapping
}

void Graphics::EnableLight()
{
	//Color for ambient light
	GLfloat ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //white
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	//Color for positioned light
	GLfloat lightColor[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //white collor
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);

	GLfloat secular[] = { 1.0f, 0.0f, 0.0f, 1.0 }; //red
	glLightfv(GL_LIGHT0, GL_SPECULAR, secular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

}

void Graphics::DisableLight()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}

void Graphics::Run()
{
	glutMainLoop();
}

void Graphics::Exit()
{
	glutDestroyWindow(Graphics::winid);
}

Graphics::~Graphics()
{
	Exit();
}

GLuint Graphics::LoadTexture(const char *TexName)	// Load Bitmaps And Convert To Textures
{
	GLuint Texture;
	AUX_RGBImageRec *TextureImage[1];				// Create Storage Space For The Texture
	memset(TextureImage, 0, sizeof(void *) * 1);	// Set The Pointer To NULL

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (TextureImage[0] = LoadBMP(TexName)) // LoadBMP("grass.bmp"))
	{
		glGenTextures(1, &Texture);					// Create The Texture
		glBindTexture(GL_TEXTURE_2D, Texture);		// Typical Texture Generation Using Data From The Bitmap

		glTexImage2D(GL_TEXTURE_2D, 0, 3,
			TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0,
			GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		// Specify filtering and edge actions
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}
	else
	{
		return -1;
	}

	if (TextureImage[0])									// If Texture Exists
	{
		if (TextureImage[0]->data)							// If Texture Image Exists
		{
			free(TextureImage[0]->data);					// Free The Texture Image Memory
		}
		free(TextureImage[0]);								// Free The Image Structure
	}

	std::cout << " GLoader::LoadTexture " << std::endl;
	return Texture;											// Return The Status
}