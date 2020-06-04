#pragma once
#include "Enums.h"
/*
	Text encapsulates  font loading and destruction as well as 
	the operations needed to create a texture with text 
	that 'Renderer' can render.
*/

class Renderer;

class Text
{
public:
	Text(SDL_Renderer* renderer);
	SDL_Texture* GetTextureForString(SDL_Renderer* aRenderer, const std::string& textToDisplay);
private:
	auto CreateTexture(SDL_Renderer* renderer, const std::string& text, SDL_Color colorOfText, FontSize fontSize);

	static std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> m_fontBig;
	static std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> m_fontSmall;
	
	static std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_LevelCompletedTexture;
	static std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_GameLostTexture;
	static std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_currentLevelTextTexture;

	static std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_genericTextTexture;
};