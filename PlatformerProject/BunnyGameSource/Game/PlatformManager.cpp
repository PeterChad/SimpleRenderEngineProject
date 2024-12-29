#include "PlatformManager.h"
#include "Engine/MyEngine.h"
#include "Engine/ComponentFactory.h"
#include "rapidjson/document.h"
#include <sstream>

void PlatformManager::Init(rapidjson::Value& serializedData) {
}

void PlatformManager::Update(float deltaTime) {
	auto player = GetGameObject().lock();
	if (!player) return;

	float currentHeight = player->GetPosition().y;
	int platformSpaceing = 200;
	if ((int)currentHeight/platformSpaceing > (int)_playerMaxHeight/platformSpaceing) {
		// Player has reached a new height
		_playerMaxHeight = currentHeight;
		auto platform = MyEngine::Engine::GetInstance()->CreateGameObject("NewPlatform"+ std::to_string(platformCounter));
		platformCounter++;
		auto platformPtr = platform.lock();
		if (!platformPtr) return;

		glm::vec2 screenSize = MyEngine::Engine::GetInstance()->GetScreenSize();

		// Adjust spawn position to ensure at least 50 % visibility
		int platformWidth = 380; // Assuming platform width is 380, adjust based on actual platform size
		int halfWidth = platformWidth / 2;

		// Limit the range of spawnPositionX
		int minX = -((int)screenSize.x / 2) + halfWidth;
		int maxX = ((int)screenSize.x / 2) - halfWidth;

		int spawnPositionX = rand() % (maxX - minX + 1) + minX;
		int spawnPositionY = _playerMaxHeight + (int)screenSize.y / 2 + 100;

		bool isPorous = rand() % 100 < 35;
		bool isMoving = rand() % 100 < 10;
		rapidjson::Document platformSpawnParameters;
		std::stringstream ss;
		ss << "{";
		ss <<	"\"name\": \"NewPlatform" << std::to_string(platformCounter) << "\",";
		ss <<	"\"transform\" : {";
		ss <<		"\"position\":[ "<< spawnPositionX <<", " << spawnPositionY << ", 0], ";
		ss <<		"\"rotation\" : [0, 0, 0] ,";
		ss <<		"\"scale\" : [0.5, 0.5, 0.5]";
		ss <<	"},";
		ss <<	"\"components\" : [";
		ss <<		"{";
		ss <<			"\"typeId\": \"PLATFORM_BUILDER\",";
		ss <<			"\"serializedData\" : {";
		ss <<				"\"size\": 1,";
		ss <<				"\"type\" : 0,";
		ss <<				"\"bouncy\": " << (isPorous ? "true" : "false") << "";
		ss <<			"}";
		ss <<		"}";
		ss << ",{\"typeId\": \"COLLISION_SOUND\",\"serializedData\": { \"sound_file\": " << (isPorous ? "\"data/iceplatformcrack.mp3\", \"sound_volume\": 55}" : "\"data/350903__cabled_mess__jump_c_03.wav\", \"sound_volume\": 85}") << "}";
		ss <<			"" << (isMoving ? ",{\"typeId\": \"PLATFORM_MOVER\", \"serializedData\" : {\"yoyo\": true, \"duration\" : 2.0, \"start\" : [0, 0, 0] , \"end\" : [200, 0, 0] , \"easing\" : 2}}" : "");
		ss <<	"]";
		ss << "}";
		platformSpawnParameters.Parse(ss.str().c_str());
		platformPtr->Init(platformSpawnParameters);
	}
}