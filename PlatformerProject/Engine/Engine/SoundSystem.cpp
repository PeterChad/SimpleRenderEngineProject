//#include "SoundSystem.h"
//
//namespace MyEngine {
//
//
//	void SoundSystem::Init() {
//		int init = Mix_OpenAudio(
//			22050,
//			MIX_DEFAULT_FORMAT,
//			2,
//			2048
//		);
//	}
//
//	void SoundSystem::PlayMusic() {
//		int playing = Mix_PlayMusic(music_file, 0);
//	}
//
//	void SoundSystem::PlaySFX(Mix_Chunk* sound_file) {
//		Mix_PlayChannel(
//			-1, // int channel to play on (-1 is first available)
//			sound_file, // Mix_Chunk* chunk to play
//			0 // int number loops
//		);
//	}
//}