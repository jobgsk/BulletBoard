#ifndef RENDER_H_
#define RENDER_H_

#include <iostream>
#include <sstream>
#include <string>

#include <assert.h>
#include "Vector3.h"
#include "Graphics.h"

class Render{
public:
	float m_r, m_g, m_b;
	
	Render(float r, float g, float b) :
		m_r(r), m_g(g), m_b(b)
	{
	
	};

	//virtual void render(btRigidBody* body) = 0;
	virtual void render(float mat[]) = 0;
	

};

class СhipRender : public Render{
public:
	Vector3<float> m_extent;
	GLUquadricObj* m_quad;
	
	СhipRender(float r, float g, float b, Vector3<float> extent) :
		Render(r, g, b), m_extent(extent)
	{
		m_quad = gluNewQuadric();
	};

	virtual ~СhipRender()
	{
		gluDeleteQuadric(m_quad);
	};

	virtual void render(float mat[])
	{
		glColor3f(m_r, m_g, m_b);

		glPushMatrix();
		glMultMatrixf(mat);     //translation,rotation

		glTranslatef(0, m_extent.y*2, 0);
		glRotatef(90, 1, 0, 0);

		gluCylinder(m_quad, 
			m_extent.x, m_extent.x*0.85f, 
			m_extent.y*2.0, 
			1.f, 
			36.f);

		//glColor3f(0.8, 0.8, 0.8);
		glTranslatef(0.0f, 0.0f, 1.0f);
		gluDisk(m_quad, 0.0f, m_extent.x, 36, 1);

		glPopMatrix();
	};

};


class BoardRender : public Render{
public:
	Vector3<float> m_extent;
	GLuint texture;

	BoardRender(const char * texpath, float r, float g, float b, Vector3<float> extent) :
		Render(r, g, b), m_extent(extent)
	{
		texture = Graphics::LoadTexture(texpath);
		if (texture == -1) {
			std::cout << "texture does not load " << texpath << std::endl;
			assert(false);
		}
	};

	virtual void render(float mat[])
	{
		glColor3f(m_r, m_g, m_b);

		glPushMatrix();
		glMultMatrixf(mat);     //translation,rotation

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBegin(GL_QUADS);
			glVertex3f(-m_extent.x, m_extent.y, -m_extent.z);
			glVertex3f(-m_extent.x, -m_extent.y, -m_extent.z);
			glVertex3f(-m_extent.x, -m_extent.y, m_extent.z);
			glVertex3f(-m_extent.x, m_extent.y, m_extent.z);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(m_extent.x, m_extent.y, -m_extent.z);
			glVertex3f(m_extent.x, -m_extent.y, -m_extent.z);
			glVertex3f(m_extent.x, -m_extent.y, m_extent.z);
			glVertex3f(m_extent.x, m_extent.y, m_extent.z);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-m_extent.x, m_extent.y, m_extent.z);
			glVertex3f(-m_extent.x, -m_extent.y, m_extent.z);
			glVertex3f(m_extent.x, -m_extent.y, m_extent.z);
			glVertex3f(m_extent.x, m_extent.y, m_extent.z);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-m_extent.x, m_extent.y, -m_extent.z);
			glVertex3f(-m_extent.x, -m_extent.y, -m_extent.z);
			glVertex3f(m_extent.x, -m_extent.y, -m_extent.z);
			glVertex3f(m_extent.x, m_extent.y, -m_extent.z);
		glEnd();
		glBegin(GL_QUADS);
			glTexCoord2f(0, 1);
			glVertex3f(-m_extent.x, m_extent.y, -m_extent.z);
			
			glTexCoord2f(0, 0);
			glVertex3f(-m_extent.x, m_extent.y, m_extent.z);

			
			glTexCoord2f(1, 0);
			glVertex3f(m_extent.x, m_extent.y, m_extent.z);
			
			glTexCoord2f(1, 1);
			glVertex3f(m_extent.x, m_extent.y, -m_extent.z);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-m_extent.x, -m_extent.y, -m_extent.z);
			glVertex3f(-m_extent.x, -m_extent.y, m_extent.z);
			glVertex3f(m_extent.x, -m_extent.y, m_extent.z);
			glVertex3f(m_extent.x, -m_extent.y, -m_extent.z);
		glEnd();

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	};
};

class SphereRender : public Render{
public:
	float m_radius;
	GLUquadricObj* m_quad;
	
	SphereRender(float r, float g, float b, float radius) :
		Render(r, g, b), m_radius(radius)
	{
		m_quad = gluNewQuadric();
	};

	virtual ~SphereRender()
	{
		gluDeleteQuadric(m_quad);
	};

	virtual void render(float mat[])
	{
		glColor3f(m_r, m_g, m_b);

		glPushMatrix();
		glMultMatrixf(mat);     //translation,rotation
		gluSphere(m_quad, m_radius, 20, 20);
		glPopMatrix();
	};

};

class CylinderRender : public Render {
public:
	Vector3<float> m_extent;
	GLUquadricObj* m_quad;

	CylinderRender(float r, float g, float b, Vector3<float> extent) :
		Render(r, g, b), m_extent(extent)
	{
		m_quad = gluNewQuadric();
	};

	virtual ~CylinderRender()
	{
		gluDeleteQuadric(m_quad);
	};

	virtual void render(float mat[])
	{
		glColor3f(m_r, m_g, m_b);

		glPushMatrix();
		glMultMatrixf(mat);     //translation,rotation

		glTranslatef(0, m_extent.y, 0);
		glRotatef(90, 1, 0, 0);
		gluCylinder(m_quad, m_extent.x, m_extent.x, m_extent.y*2.0, 20, 20);
		
		glPopMatrix();
	};

};

class BoxRender : public Render{
public:
	Vector3<float> m_extent;

	BoxRender(float r, float g, float b, Vector3<float> extent) :
		Render(r, g, b), m_extent(extent)
	{
		
	};

	virtual void render(float mat[])
	{
		glColor3f(m_r, m_g, m_b);

		glPushMatrix();
		glMultMatrixf(mat);     //translation,rotation
		glBegin(GL_QUADS);
			glVertex3f(-m_extent.x, m_extent.y, -m_extent.z);
			glVertex3f(-m_extent.x, -m_extent.y, -m_extent.z);
			glVertex3f(-m_extent.x, -m_extent.y, m_extent.z);
			glVertex3f(-m_extent.x, m_extent.y, m_extent.z);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(m_extent.x, m_extent.y, -m_extent.z);
			glVertex3f(m_extent.x, -m_extent.y, -m_extent.z);
			glVertex3f(m_extent.x, -m_extent.y, m_extent.z);
			glVertex3f(m_extent.x, m_extent.y, m_extent.z);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-m_extent.x, m_extent.y, m_extent.z);
			glVertex3f(-m_extent.x, -m_extent.y, m_extent.z);
			glVertex3f(m_extent.x, -m_extent.y, m_extent.z);
			glVertex3f(m_extent.x, m_extent.y, m_extent.z);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-m_extent.x, m_extent.y, -m_extent.z);
			glVertex3f(-m_extent.x, -m_extent.y, -m_extent.z);
			glVertex3f(m_extent.x, -m_extent.y, -m_extent.z);
			glVertex3f(m_extent.x, m_extent.y, -m_extent.z);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-m_extent.x, m_extent.y, -m_extent.z);
			glVertex3f(-m_extent.x, m_extent.y, m_extent.z);
			glVertex3f(m_extent.x, m_extent.y, m_extent.z);
			glVertex3f(m_extent.x, m_extent.y, -m_extent.z);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-m_extent.x, -m_extent.y, -m_extent.z);
			glVertex3f(-m_extent.x, -m_extent.y, m_extent.z);
			glVertex3f(m_extent.x, -m_extent.y, m_extent.z);
			glVertex3f(m_extent.x, -m_extent.y, -m_extent.z);
		glEnd();
		glPopMatrix();
	};
};

class PlaineRender : public Render{
public:
	GLuint texture;
	Vector3<float> m_extent;

	PlaineRender(const char * texpath, float r, float g, float b, Vector3<float> extent) :
		Render(r, g, b), m_extent(extent)
	{
		texture = Graphics::LoadTexture(texpath);
		if (texture == -1) {
			std::cout << "texture does not load " << texpath << std::endl;
			assert(false);
		}
	};

	PlaineRender(float r, float g, float b, Vector3<float> extent) :
		Render(r, g, b), m_extent(extent)
	{
		texture = -1;
	};

	virtual void render(float mat[])
	{
		glColor3f(m_r, m_g, m_b);
		
		glPushMatrix();
		glMultMatrixf(mat);     //translation,rotation

		if (texture != -1)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture);
		}

		glBegin(GL_QUADS);
			
			if (texture != -1)
				glTexCoord2f(0, 1);
			glVertex3f(-m_extent.x, 0, m_extent.z);

			if (texture != -1)
				glTexCoord2f(0, 0);
			glVertex3f(-m_extent.x, 0, -m_extent.z);

			if (texture != -1)
				glTexCoord2f(1, 0);
			glVertex3f(m_extent.x, 0, -m_extent.z);

			if (texture != -1)
				glTexCoord2f(1, 1);
			glVertex3f(m_extent.x, 0, m_extent.z);

		glEnd();
		if (texture != -1)
		{
			glDisable(GL_TEXTURE_2D);
		}
		glPopMatrix();
	};

};

class ArrowRender : public Render{
public:
	GLuint texture;
	Vector3<float> m_extent;
	float m_force;

	ArrowRender(float r, float g, float b, Vector3<float> extent) :
		Render(r, g, b), m_extent(extent)
	{
		texture = -1;
		m_force = 0;
	};

	void set_force(float force)
	{
		m_force = force;
	};

	virtual void render(float mat[])
	{
		glColor3f(m_r, m_g, m_b);

		glPushMatrix();
		glMultMatrixf(mat);     //translation,rotation

		glBegin(GL_QUADS);

		glVertex3f(0, 0, 0.5);
		glVertex3f(-m_force, 0, 0);
		glVertex3f(-m_force, 0, 0);
		glVertex3f(0, 0, -0.5);

		glEnd();
		glPopMatrix();
	};

};

class TextRender : public Render{
public:

	std::string m_init_text;
	std::string m_render_text;
	int m_x, m_y;


	TextRender(std::string text, int x, int y) : Render(1.0, 1.0, 1.0),
		m_init_text(text), m_render_text(text), m_x(x), m_y(y)
	{

	};

	void concatenate(int value)
	{
		std::stringstream sstm;
		sstm << m_init_text << value;
		m_render_text = sstm.str();
	}

	virtual void render(float mat[])
	{

	}

	virtual void render()
	{
		const char * text = m_render_text.data();
		int length = m_render_text.size();

		// change the current matrix to PROJECTION
		glMatrixMode(GL_PROJECTION);
		// 16 doubles in stack memory
		double matrix[16];
		// get the values from PROJECTION matrix to local variable
		glGetDoublev(GL_PROJECTION_MATRIX, matrix);
		// reset PROJECTION matrix to identity matrix
		glLoadIdentity();
		// orthographic perspective
		glOrtho(0, 800, 0, 600, -5, 5);
		// change current matrix to MODELVIEW matrix again
		glMatrixMode(GL_MODELVIEW);
		// reset it to identity matrix
		glLoadIdentity();
		// push current state of MODELVIEW matrix to stack
		glPushMatrix();
		// reset it again. (may not be required, but it my convention)
		glLoadIdentity();
		// raster position in 2D
		glRasterPos2i(m_x, m_y);
		for (int i = 0; i<length; i++){
			// generation of characters in our text with 9 by 15 GLU font
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
		}
		// get MODELVIEW matrix value from stack
		glPopMatrix();
		// change current matrix mode to PROJECTION
		glMatrixMode(GL_PROJECTION);
		// reset
		glLoadMatrixd(matrix);
		// change current matrix mode to MODELVIEW
		glMatrixMode(GL_MODELVIEW);
	};

};

#endif /* RENDER_H_ */