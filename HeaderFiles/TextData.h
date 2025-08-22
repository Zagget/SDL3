#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include <iostream>

class TextData {
public:
	TextData() = default;
	~TextData() { Quit(); }

	bool Init();

	SDL_Texture* GetTexture(std::string& text, SDL_Renderer* ren);
	void Quit();

protected:
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;

	TTF_Font* font = nullptr;

	SDL_Color color{ 255, 255, 255, 255 };
	SDL_FRect rect{ 0.f, 0.f, 0.f, 0.f };
};