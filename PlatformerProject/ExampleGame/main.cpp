#include "sre/SpriteAtlas.hpp"

#include "Engine/MyEngine.h"
#include "Engine/ComponentFactory.h"

#include "Game/ComponentController.h"
#include "Game/ComponentFollowTarget.h"
#include "Game/ComponentPlatform.h"
#include "Game/ComponentPlatformMove.h"
#include "Game/ComponentSpline.h"
#include "Game/ComponentPlatformBounce.h"
#include "Game/ComponentJetpack.h"

MyEngine::Engine engine;

int main() {
	MyEngine::ComponentFactory::RegisterComponentOfType("CONTROLLER", []() { return std::make_shared<ComponentController>(); });
	MyEngine::ComponentFactory::RegisterComponentOfType("FOLLOW_TARGET", []() { return std::make_shared<ComponentFollowTarget>(); });
	MyEngine::ComponentFactory::RegisterComponentOfType("PLATFORM_BUILDER", []() { return std::make_shared<ComponentPlatform>(); });
	MyEngine::ComponentFactory::RegisterComponentOfType("PLATFORM_MOVER", []() { return std::make_shared<ComponentPlatformMove>(); });
	MyEngine::ComponentFactory::RegisterComponentOfType("SPLINE", []() { return std::make_shared<ComponentSpline>(); });
	MyEngine::ComponentFactory::RegisterComponentOfType("PLATFORM_BOUNCER", []() { return std::make_shared<ComponentPlatformBounce>(); });
	MyEngine::ComponentFactory::RegisterComponentOfType("JETPACK", []() { return std::make_shared<ComponentJetpack>(); });
	
	engine.Init("data/scene.json");
}
