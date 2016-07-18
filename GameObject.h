#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "PhysicsBoby.h"
#include "Render.h"

class GameObject{
public:
	int m_id;
	bool m_hit;

	PhysicsBody* m_body;
	Render* m_render;
	float m_trans_mat[16];

	Vector3<float> prev_pos;
	
	GameObject(PhysicsBody* b, Render* r, int i) :
		m_body(b), m_render(r), m_id(i), m_hit(false) 
	{
		prev_pos = Vector3<float>();
	};

	void render()
	{
		m_body->get_mat(m_trans_mat);
		
		/*std::cout << " mat ";
		for (int i = 0; i < 16; i++)
		{
			std::cout << i << "  " << m_trans_mat[i];
		}
		std::cout << std::endl;
		*/

		//if (m_hit)
		//	m_render->m_g = 1;

		m_render->render(m_trans_mat);
	}


};

#endif /* GAME_OBJECT_H_ */


