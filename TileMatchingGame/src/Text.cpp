#include "pch.h"
#include "Text.h"
#include "Constants.h"

#include "Renderer.h"

Text::Text()
{
	TTF_Init();
	m_font.reset(TTF_OpenFont(Consts::FONT_PATH, 12));
	if (!m_font) printf("TTF_OpenFont: %s\n", TTF_GetError());
}

SDL_Texture* Text::GetTextureForString(SDL_Renderer* aRenderer, const std::string& aTextToDisplay)
{
	m_textSurface.reset(TTF_RenderText_Solid(m_font.get(), aTextToDisplay.c_str(), Consts::TEXT_COLOR));
	m_textTexture.reset(SDL_CreateTextureFromSurface(aRenderer, m_textSurface.get()));
	return m_textTexture.get();
}
