#pragma once

/*
	Text encapsulates  font loading and destruction as well as 
	the operations needed to create a texture with text 
	that 'Renderer' can render.
*/

class Renderer;

class Text
{
public:
	Text();
	SDL_Texture* GetTextureForString(SDL_Renderer* aRenderer, const std::string& textToDisplay);
private:
	std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> m_font{ nullptr, TTF_CloseFont };
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> m_textSurface{ nullptr, SDL_FreeSurface };
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_textTexture{ nullptr, SDL_DestroyTexture };
};