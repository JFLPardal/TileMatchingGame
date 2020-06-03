#include "pch.h"
#include "Renderer.h"
#include "Constants.h"

#include "Rect.h"
#include "Vector2.h"

#include "Text.h"

auto Renderer::LoadTexture(const std::string& aTexturePath)
{
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture(nullptr, SDL_DestroyTexture);
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> loadedSurface(IMG_Load(aTexturePath.c_str()), SDL_FreeSurface);

	if (loadedSurface.get() != nullptr)
	{
		texture.reset(SDL_CreateTextureFromSurface(m_renderer.get(), loadedSurface.get()));
		if (texture.get() == nullptr)
		{
			printf("unable to create texture %s\n", SDL_GetError());
		}
	}
	else
		printf("unable to load image %s : %s\n", aTexturePath.c_str(), SDL_GetError());
	return texture;
}

Renderer::Renderer(SDL_Window* const aWindow)
{
	InitRenderer(aWindow);
	m_text = std::make_unique<Text>(m_renderer.get());
	m_texture = LoadTexture("assets\\tilesheet.png");
	m_background = LoadTexture("assets\\background.png");
}

void Renderer::ClearScreen()
{
	SDL_RenderClear(m_renderer.get());
}

void Renderer::DrawBackground()
{
	SDL_RenderCopy(m_renderer.get(), m_background.get(), NULL, NULL);
}

void Renderer::Display()
{
	SDL_RenderPresent(m_renderer.get());
}

void Renderer::DrawPiece(Rect* aTextureRect, int aScreenPosX, int aScreenPosY)
{
	SDL_Rect screenPosAndSize{ aScreenPosX, aScreenPosY, Consts::PIECE_W, Consts::PIECE_H };
	SDL_Rect spriteSheetTexture = aTextureRect->GetAsSDLRect();
	SDL_RenderCopy(m_renderer.get(), m_texture.get(), &spriteSheetTexture, &screenPosAndSize);
}

void Renderer::DrawPiece(Rect* aTextureRect, const Vector2& aScreenPos)
{
	DrawPiece(aTextureRect, aScreenPos.X(), aScreenPos.Y());
}

void Renderer::DrawUI(Rect* aTextureRect, const Vector2& aScreenPos, const Vector2& aDimensions)
{
	SDL_Rect screenPosAndSize{ aScreenPos.X(), aScreenPos.Y(), aDimensions.X(), aDimensions.Y() };
	SDL_Rect spriteSheetTexture = aTextureRect->GetAsSDLRect();
	SDL_RenderCopy(m_renderer.get(), m_texture.get(), &spriteSheetTexture, &screenPosAndSize);
}

void Renderer::DrawText(const std::string& aTextToDisplay, const Vector2& aScreenPos, const Vector2& aDimension)
{
	SDL_Texture* textTexture = m_text->GetTextureForString(m_renderer.get(), aTextToDisplay);
	SDL_Rect textRect{ aScreenPos.X(), aScreenPos.Y(),
					   aDimension.X(), aDimension.Y() };
	SDL_RenderCopy(m_renderer.get(),textTexture , NULL, &textRect);
}

void Renderer::InitRenderer(SDL_Window* const aWindow)
{
	m_renderer.reset(SDL_CreateRenderer(aWindow, -1, SDL_RENDERER_ACCELERATED));
	if (m_renderer != nullptr)
	{
		SDL_SetRenderDrawColor(m_renderer.get(), 100, 0, 200, 255);
	}
	else
		printf("renderer was not created %s\n", SDL_GetError());
}

Renderer::~Renderer() = default;