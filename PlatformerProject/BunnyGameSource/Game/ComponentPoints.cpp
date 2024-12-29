#include "ComponentPoints.h"
#include "Engine/Components/ComponentPhysicsBody.h"
#include "Engine/MyEngine.h"
#include <iostream>

void ComponentPoints::Init(rapidjson::Value& serializedData) {
	playerObject = GetGameObject().lock();
	_bestPoints = 0;
	_bestHeight = playerObject->GetPosition()[1];
	_currentHeight = _bestHeight;
}

void ComponentPoints::Update(float deltaTime) {
	_currentHeight = playerObject->GetPosition()[1];

	if (_currentHeight > _bestHeight) {
		_currentBest += (_currentHeight - _bestHeight);
		_bestHeight = _currentHeight;
		//std::cout << points << std::endl;
	}

	if (_currentBest > _bestPoints) {
		_bestPoints = _currentBest;
	}

}

void ComponentPoints::Render(sre::RenderPass& renderPass) {
	ImGui::SetNextWindowSize(ImVec2(300, 150));
	ImGui::Begin("Points");
	ImGui::Text("High Score: %i", _bestPoints);
	ImGui::Text("Current Score: %i", _currentBest);
	ImGui::End();
}