#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <functional>
#include <GL/glut.h>
#include "bmp.h"

class Graphics  {

	
public:

	static int winid;
	Graphics(int myargc, char** myargv, const char *app_name);
	~Graphics();

	static void Display(std::function<void()> fun);
	static void Reshape(int w, int h);
	
	static void Camera(float cx, float cy, float cz, float px, float py, float pz);
	static void Redispaly();

	static void EnableLight();
	static void DisableLight();
	static void EnableTexture();
	static GLuint LoadTexture(const char *TexName);

	static void Run();
	static void Clean();
	static void Exit();
	

};

#endif /* GRAPHICS_H_ */