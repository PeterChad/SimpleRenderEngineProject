#pragma once

#include "Engine/Component.h"
#include "Engine/MyEngine.h"

class ComponentController : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event&) override;
	void OnCollisionStart(ComponentPhysicsBody* other, b2Manifold* manifold) override;
	void OnCollisionEnd(ComponentPhysicsBody* other, b2Manifold* manifold) override;

private:
	std::weak_ptr<ComponentPhysicsBody> _body;
	glm::vec3 _mov;
	bool _jump;
	bool _grounded;
	bool _jetpack;

	float _movSpeed = 2;
	float _jumpStrength = 1;
	float _jetpackStrength = 3;
	

	//MyEngine::Engine* engine;
};