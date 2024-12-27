#pragma once

#include "Engine/Component.h"

class ComponentPoints : public MyEngine::Component {
	private: 
		std::shared_ptr<MyEngine::GameObject> playerObject;
		int points = 0;
		int currentHeight;
		int bestHeight;
	public:
		virtual void Init(rapidjson::Value& serializedData) override;
		void Update(float deltaTime) override;
};