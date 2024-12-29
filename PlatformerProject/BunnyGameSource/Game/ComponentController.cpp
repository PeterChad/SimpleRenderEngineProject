#include "ComponentController.h"

#include "glm/glm.hpp"
#include "SDL.h"

#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentPhysicsBody.h"
#include "Engine/Components/ComponentSoundSystem.h"
#include "ComponentPlatform.h"

#include "ComponentJetpack.h"
#include "ComponentSound.h"


void ComponentController::Init(rapidjson::Value& serializedData) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;

	_body = gameObject->FindComponent<ComponentPhysicsBody>();
}

void ComponentController::Update(float deltaTime) {
	auto body = _body.lock();
	if (!body)
		return;

	auto linearVelocity = body->getLinearVelocity();
	linearVelocity.x = _mov.x * _movSpeed;
	body->setLinearVelocity(linearVelocity);

	if (_jump) {
		body->addImpulse(glm::vec2(0, _jumpStrength));
		_jump = false;
	}

	if (_jetpack) {
		body->addImpulse(glm::vec2(0, _jetpackStrength));
		_jetpack = false;
	}

	//using hardcoded values, should probably fit to screen size given time.
	auto playerObject = body->GetGameObject().lock();
	glm::vec3 currentPos = playerObject->GetPosition();
	if (currentPos[0] < -235) {
		glm::vec3 newPos = glm::vec3(537, currentPos[1], currentPos[2]);
		playerObject->SetPosition(newPos);
		body->setPosition(newPos);
	}
	if (currentPos[0] > 540) {
		glm::vec3 newPos = glm::vec3(-232, currentPos[1], currentPos[2]);
		playerObject->SetPosition(newPos);
		body->setPosition(newPos);
	}
}

void ComponentController::KeyEvent(SDL_Event& event) {


	// movement
	switch (event.key.keysym.sym) {
		case SDLK_a: {
			if (event.type == SDL_KEYDOWN) {
				_mov.x = -1;
			}
			if (event.type == SDL_KEYUP && _mov.x < 0) { 
				_mov.x = 0;
			}
			break; 
			}
		case SDLK_d: {
			if (event.type == SDL_KEYDOWN) {
				_mov.x = 1;
			}
			if (event.type == SDL_KEYUP && _mov.x > 0) {
				_mov.x = 0;
			}
			break;
		}
	}

}

void ComponentController::OnCollisionStart(ComponentPhysicsBody* other, b2Manifold* manifold) {
	if (other == nullptr) {
		return;
	}
	//Get engine for handling platform destruction
	auto engine = MyEngine::Engine::GetInstance();

	//Get collision information
	auto collidedBody = other->GetGameObject().lock();
	auto collidedGameObject = collidedBody.get();
	auto soundCollision = collidedBody->FindComponent<ComponentSound>().lock();
	auto platformCollision = collidedBody->FindComponent<ComponentPlatform>().lock();
	auto jetpackCollision = collidedBody->FindComponent<ComponentJetpack>().lock();

	//Get player information and access to system components for playing SFX
	auto playerObject = GetGameObject().lock();
	if (soundCollision) {
		if (!collidedBody) {
			return;
		}
		auto soundSystem = playerObject->FindComponent<ComponentSoundSystem>().lock();
		soundSystem->PlaySFX(soundCollision->GetCollisionSoundFile(), soundCollision->GetCollisionSoundVolume());
	}

	//Handle jumping and schedule object destruction.
	if (platformCollision) {
		if (!collidedBody) {
			return;
		}
		_jump = true;
		if (platformCollision->_bouncy) {
			engine->RegisterForDestruction(collidedGameObject);
			return;
		}
	  }
	else if (jetpackCollision) {
		if (!collidedBody) {
			return;
		}
		engine->RegisterForDestruction(collidedGameObject);
		_jetpack = true;
	}
	
}

void ComponentController::OnCollisionEnd(ComponentPhysicsBody* other, b2Manifold* manifold) {
	if (other == nullptr || manifold == nullptr) {
		return;
	}
	if (manifold->localNormal.y > .99)
		_grounded = false;

	
}