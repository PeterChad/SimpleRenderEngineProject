#pragma once

#include "Engine/Component.h"
#include "Engine/MyEngine.h"

class ComponentController : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event&) override;
	void OnCollisionStart(ComponentPhysicsBody* other, b2Manifold* manifold) override;
	void OnCollisionEnd(ComponentPhysicsBody* other, b2Manifold* manifold) override;
	void ScreenEdgePan(std::shared_ptr<ComponentPhysicsBody> body);
	void HandleJump(std::shared_ptr<ComponentPhysicsBody> body);

private:
	std::weak_ptr<ComponentPhysicsBody> _body;
	glm::vec3 _mov;
	bool _jump;
	bool _jetpack;

	float _movSpeed = 3;
	float _jumpStrength = 5;
	float _jetpackStrength = 7;
};