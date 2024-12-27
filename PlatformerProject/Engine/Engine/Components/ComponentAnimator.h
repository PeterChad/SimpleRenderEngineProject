#pragma once

#include "sre/SpriteAtlas.hpp"
#include "sre/Sprite.hpp"

#include "Engine/Component.h"
#include "ComponentPhysicsBody.h"

class ComponentAnimator : public MyEngine::Component {
public:
	virtual void Init(rapidjson::Value& serializedData) override;
	virtual void Render(sre::RenderPass& renderPass) override;
	void Update(float deltaTime) override;

	sre::Sprite* GetSprite() { return &_spriteCurrent; }
	void SetSpritePosition(glm::vec2& position);
	std::weak_ptr<ComponentPhysicsBody> _body;

protected:
	sre::Sprite _spriteCurrent;
	sre::Sprite _spriteFalling;
	sre::Sprite _spriteJumping;
	sre::Sprite _spriteDead;

private:
	std::shared_ptr<sre::SpriteAtlas> _atlas;
	std::string _atlasName;
};