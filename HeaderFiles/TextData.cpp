#include "TextData.h"

bool TextData::Init() {
	font = TTF_OpenFont("font.ttf", 96);
	if (!font) {
		SDL_Log("Failed to load font: %s", SDL_GetError());
		return false;
	}

	TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
	TTF_SetFontOutline(font, 1);
	TTF_SetFontHinting(font, TTF_HINTING_NORMAL);
}

SDL_Texture* TextData::GetTexture(std::string& text, SDL_Renderer* ren) {

	int count = text.length();

	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), count, color, 0);
	if (!surface) {
		printf("Failed to render text: %s", SDL_GetError());

	}

	texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_DestroySurface(surface);

	if (!texture) {
		printf("Failed to create texture: %s", SDL_GetError());
	}

	return texture;
}

void TextData::Quit() {
	if (surface) SDL_DestroyTexture(texture);
	if (texture) SDL_DestroySurface(surface);
	if (font) TTF_CloseFont(font);
}