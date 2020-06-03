#pragma once
/*
	Renderer is responsible for wrapping the rendering provided
	by SDL as well as rendering the game
*/

class IGridRepresentation;
class Rect;
class Vector2;
class Text;

class Renderer
{
public:
	Renderer(SDL_Window* const window);
	~Renderer();

	void ClearScreen();
	void DrawBackground();
	void DrawPiece(Rect* textureRect, int screenPosX, int screenPosY);
	void DrawPiece(Rect* textureRect, const Vector2& screenPos);
	void DrawUI(Rect* textureRect, const Vector2& screenPos, const Vector2& dimensions);
	void DrawText(const std::string& textToDisplay, const Vector2& screenPos, const Vector2& dimension);
	void Display();

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
private:
	auto LoadTexture(const std::string& texturePath);
	void InitRenderer(SDL_Window* const window);

	std::unique_ptr<SDL_Renderer,decltype(&SDL_DestroyRenderer)> m_renderer{ nullptr, SDL_DestroyRenderer };
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>  m_texture{ nullptr, SDL_DestroyTexture };
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>  m_background{ nullptr, SDL_DestroyTexture };
	std::unique_ptr<Text> m_text{ nullptr };
};