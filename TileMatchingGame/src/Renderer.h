#pragma once

/*
	Renderer is responsible for wrapping the rendering provided
	by SDL as well as rendering the game
*/

class IGridRepresentation;
class Rect;

class Renderer
{
public:
	Renderer(SDL_Window* const window);

	void ClearScreen();
	void Draw(Rect* aTextureRect, int aScreenPosX, int aScreenPosY);
	void Display();

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
private:
	auto LoadTexture(const std::string& texturePath);
	void InitRenderer(SDL_Window* const window);

	std::unique_ptr<SDL_Renderer,decltype(&SDL_DestroyRenderer)> m_renderer{ nullptr, SDL_DestroyRenderer };
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>  m_texture{ nullptr, SDL_DestroyTexture };
};