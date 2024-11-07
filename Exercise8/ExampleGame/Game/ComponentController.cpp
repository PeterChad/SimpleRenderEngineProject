#include "ComponentController.h"

#include "glm/glm.hpp"
#include "SDL.h"

#include "Engine/Components/ComponentPhysicsBody.h"

float linear_velocity = 5.0;
float impulse_strength = 0.5;

void ComponentController::Init(rapidjson::Value& serializedData) {
	// TODO load necessary data (linear velocity, inpulse strenght, etc) and add the to `scene.json`
	/*float linear_velocity = serializedData["linearVelocity"].GetFloat();
	float impulse_strength = serializedData["impulseStrength"].GetFloat();*/
	std::weak_ptr<ComponentPhysicsBody> cpb = GetGameObject().lock()->FindComponent<ComponentPhysicsBody>();
	cpb.lock()->addForce(glm::vec2(linear_velocity, 0));
	//auto gameObject = GetGameObject().lock();
	/*ComponentPhysicsBody cpb;
	cpb.addImpulse(glm::vec2(0, impulse_strength));*/
	
}

void ComponentController::Update(float deltaTime) {
	// TODO, if you need to do anything here
}

void ComponentController::KeyEvent(SDL_Event& event)
{
	// TODO listen for spacebar
	if (event.type == SDL_KEYDOWN) // When a key is pressed down
	{
		if (event.key.keysym.sym == SDLK_SPACE)
		{
			std::weak_ptr<ComponentPhysicsBody> cpb = GetGameObject().lock()->FindComponent<ComponentPhysicsBody>();
			cpb.lock()->addImpulse(glm::vec2(0, impulse_strength));
		}
	}
	
}

void ComponentController::OnCollisionStart(ComponentPhysicsBody* other) {
	// TODO gameOver on touching pipes, despawn coins
}

//auto gameObject = GetGameObject();

//ComponentPhysicsBody* physicsComponent = gameObject->Get