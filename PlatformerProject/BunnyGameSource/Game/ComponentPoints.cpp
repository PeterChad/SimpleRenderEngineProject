#include "ComponentPoints.h"
#include "Engine/Components/ComponentPhysicsBody.h"
#include "Engine/MyEngine.h"
#include <iostream>

void ComponentPoints::Init(rapidjson::Value& serializedData) {
	playerObject = GetGameObject().lock();
	points = 0;
	bestHeight = playerObject->GetPosition()[1];
	currentHeight = bestHeight;
}

void ComponentPoints::Update(float deltaTime) {
	currentHeight = playerObject->GetPosition()[1];

	if (currentHeight > bestHeight) {
		points += (currentHeight - bestHeight);
		bestHeight = currentHeight;
		//std::cout << points << std::endl;
	}

}