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
	if (!playerDead) {
		ImGui::SetNextWindowSize(ImVec2(175, 70));
		ImGui::Begin("Points");
		ImGui::Text("High Score: %i", _bestPoints);
		ImGui::Text("Current Score: %i", _currentBest);
	}
	else {
		ImGui::SetNextWindowSize(ImVec2(410, 120));
		ImGui::Begin("You fell too far :(");
		ImGui::Text("Falling too far makes the bunny sad, press R to restart. \n ");
		ImGui::Text("High Score: %i", _bestPoints);
		ImGui::Text("Current Score: %i", _currentBest);
	}
	ImGui::End();
}