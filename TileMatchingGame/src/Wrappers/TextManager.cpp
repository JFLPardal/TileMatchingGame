#include "pch.h"
#include "TextManager.h"
#include "Constants.h"

#include "Wrappers/Renderer.h"

std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> Text::m_fontBig{ nullptr, TTF_CloseFont };
std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> Text::m_fontSmall{ nullptr, TTF_CloseFont };

std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> Text::m_LevelCompletedTexture{ nullptr, SDL_DestroyTexture };
std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> Text::m_GameLostTexture{ nullptr, SDL_DestroyTexture };
std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> Text::m_currentLevelTextTexture{ nullptr, SDL_DestroyTexture };
std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> Text::m_genericTextTexture{ nullptr, SDL_DestroyTexture };

auto Text::CreateTexture(SDL_Renderer* aRenderer, const std::string& aText, SDL_Color aColorOfText, FontSize aFontSize)
{
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> textSurface{ nullptr, SDL_FreeSurface };
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture(nullptr, SDL_DestroyTexture);

	if(aFontSize == FontSize::small)
		textSurface.reset(TTF_RenderText_Solid(m_fontSmall.get(), aText.c_str(), aColorOfText));
	else if (aFontSize == FontSize::big)
		textSurface.reset(TTF_RenderText_Solid(m_fontBig.get(), aText.c_str(), aColorOfText));
	if (textSurface != nullptr)
	{
		texture.reset(SDL_CreateTextureFromSurface(aRenderer, textSurface.get()));
		if (texture == nullptr)
			printf("texture not loaded: %s\n", SDL_GetError());
	}
	else
		printf("surface not loaded: %s\n", SDL_GetError());
	return texture;
}

Text::Text(SDL_Renderer* aRenderer)
{
	TTF_Init();
	m_fontBig.reset(TTF_OpenFont(Consts::FONT_PATH, Consts::TEXT_POINTS_BIG));
	m_fontSmall.reset(TTF_OpenFont(Consts::FONT_PATH, Consts::TEXT_POINTS_SMALL));
	if (!m_fontBig || !m_fontSmall) printf("TTF_OpenFont: %s\n", TTF_GetError());

	m_GameLostTexture =			CreateTexture(aRenderer, Consts::GAME_LOST_TEXT, Consts::TEXT_COLOR_GAME_LOST, FontSize::big);
	m_LevelCompletedTexture =	CreateTexture(aRenderer,  Consts::LEVEL_COMPLETED_TEXT, Consts::TEXT_COLOR_DEFAULT, FontSize::big);
	m_currentLevelTextTexture = CreateTexture(aRenderer, Consts::CURRENT_LEVEL_TEXT, Consts::TEXT_COLOR_DEFAULT, FontSize::small);
}

SDL_Texture* Text::GetTextureForString(SDL_Renderer* aRenderer, const std::string& aTextToDisplay)
{
	if (aTextToDisplay == Consts::GAME_LOST_TEXT)	// this would be better as an enum
		return m_GameLostTexture.get();
	else if (aTextToDisplay == Consts::LEVEL_COMPLETED_TEXT)
		return m_LevelCompletedTexture.get();
	else if (aTextToDisplay == Consts::CURRENT_LEVEL_TEXT)
		return m_currentLevelTextTexture.get();
	else
	{
		m_genericTextTexture = CreateTexture(aRenderer, aTextToDisplay, Consts::TEXT_COLOR_DEFAULT, FontSize::big);
		return m_genericTextTexture.get();
	}
}