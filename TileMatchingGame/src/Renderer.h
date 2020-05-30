#pragma once
/*
	Renderer is responsible for wrapping the rendering provided
	by SDL as well as rendering the game
*/

class IGridRepresentation;
class Rect;
class Vector2;

class Renderer
{
public:
	Renderer(SDL_Window* const window);

	void ClearScreen();
	void Draw(Rect* textureRect, int screenPosX, int screenPosY);
	void Draw(Rect* textureRect, const Vector2& screenPos);
	void DrawUI(Rect* textureRect, const Vector2& screenPos, const Vector2& dimensions);
	void Display();

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
private:
	auto LoadTexture(const std::string& texturePath);
	void InitRenderer(SDL_Window* const window);

	std::unique_ptr<SDL_Renderer,decltype(&SDL_DestroyRenderer)> m_renderer{ nullptr, SDL_DestroyRenderer };
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>  m_texture{ nullptr, SDL_DestroyTexture };
};