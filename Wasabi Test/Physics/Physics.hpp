#pragma once

#include "../TestSuite.hpp"
#include <Renderers/WForwardRenderer.h>

class PhysicsDemo : public WTestState {
	WObject* m_ground;
	WRigidBody* m_groundRB;
	WObject* m_ball;
	WRigidBody* m_ballRB;

public:
	PhysicsDemo(Wasabi* const app);

	virtual void Load();
	virtual void Update(float fDeltaTime);
	virtual void Cleanup();

	virtual WRenderer* CreateRenderer() { return new WForwardRenderer(m_app); }
	virtual WPhysicsComponent* CreatePhysicsComponent() {
		WBulletPhysics* physics = new WBulletPhysics(m_app);
		WError werr = physics->Initialize(true);
		if (!werr)
			W_SAFE_DELETE(physics);
		return physics;
	}
};