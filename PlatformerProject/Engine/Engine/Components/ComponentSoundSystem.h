#pragma once

#include "Engine/Component.h"
#include "SDL_mixer.h"


class ComponentSoundSystem : public MyEngine::Component {

private:
	Mix_Music* music_file;

public:
	void Init(rapidjson::Value& serializedData);
	void LoadMusic();
	void PlayMusic();
	void PlaySFX(Mix_Chunk* sound_file);
};

