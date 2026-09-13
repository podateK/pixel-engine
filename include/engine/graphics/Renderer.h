#pragma once

#include "engine/Core.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

namespace pe::graphics {

struct RenderCommand {
    const sf::Texture* texture = nullptr;
    sf::Vertex vertices[4];
    u32 layer = 0;
    f32 sortKey = 0.0f;
};

class Renderer {
public:
    Renderer() = default;

    void init(sf::RenderWindow& window);

    void clear(const sf::Color& color = sf::Color::Black);
    void present();

    void drawSprite(const sf::Texture& texture, const sf::IntRect& rect,
                    const sf::Vector2f& position, const sf::Vector2f& scale,
                    f32 rotation, const sf::Color& color, u32 layer);

    void drawRect(const sf::Vector2f& position, const sf::Vector2f& size,
                  const sf::Color& color, u32 layer);

    void drawLine(const sf::Vector2f& start, const sf::Vector2f& end,
                  const sf::Color& color, f32 thickness, u32 layer);

    void flush();

    void setView(const sf::View& view);

    u32 getDrawCallCount() const { return m_drawCallCount; }
    u32 getVertexCount() const { return m_vertexCount; }

private:
    void sortCommands();
    void flushBatch(const sf::Texture* texture, const sf::Vertex* vertices, u32 count);

    sf::RenderWindow* m_window = nullptr;
    std::vector<RenderCommand> m_commands;
    u32 m_drawCallCount = 0;
    u32 m_vertexCount = 0;

    static constexpr u32 MAX_VERTICES = 65536;
    std::array<sf::Vertex, MAX_VERTICES> m_vertexBuffer;
    u32 m_currentVertexCount = 0;
    const sf::Texture* m_currentTexture = nullptr;
};

} // namespace pe::graphics
