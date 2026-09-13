#include "engine/graphics/Renderer.h"
#include <algorithm>

namespace pe::graphics {

void Renderer::init(sf::RenderWindow& window) {
    m_window = &window;
}

void Renderer::clear(const sf::Color& color) {
    m_commands.clear();
    m_drawCallCount = 0;
    m_vertexCount = 0;

    if (m_window) {
        m_window->clear(color);
    }
}

void Renderer::present() {
    flush();
}

void Renderer::drawSprite(const sf::Texture& texture, const sf::IntRect& rect,
                          const sf::Vector2f& position, const sf::Vector2f& scale,
                          f32 rotation, const sf::Color& color, u32 layer) {
    RenderCommand cmd;
    cmd.texture = &texture;
    cmd.layer = layer;
    cmd.sortKey = position.y + (static_cast<f32>(layer) * 10000.0f);

    sf::Vector2f size(static_cast<f32>(rect.width) * scale.x,
                      static_cast<f32>(rect.height) * scale.y);

    sf::Vector2f origin(size.x * 0.5f, size.y * 0.5f);

    sf::Transform transform;
    transform.translate(position + origin);
    transform.rotate(rotation);
    transform.translate(-origin);

    sf::Vector2f positions[4] = {
        {0.0f, 0.0f},
        {size.x, 0.0f},
        {size.x, size.y},
        {0.0f, size.y}
    };

    sf::Vector2f texCoords[4] = {
        {static_cast<f32>(rect.left), static_cast<f32>(rect.top)},
        {static_cast<f32>(rect.left + rect.width), static_cast<f32>(rect.top)},
        {static_cast<f32>(rect.left + rect.width), static_cast<f32>(rect.top + rect.height)},
        {static_cast<f32>(rect.left), static_cast<f32>(rect.top + rect.height)}
    };

    for (int i = 0; i < 4; i++) {
        cmd.vertices[i].position = transform.transformPoint(positions[i]);
        cmd.vertices[i].texCoords = texCoords[i];
        cmd.vertices[i].color = color;
    }

    m_commands.push_back(cmd);
}

void Renderer::drawRect(const sf::Vector2f& position, const sf::Vector2f& size,
                        const sf::Color& color, u32 layer) {
    RenderCommand cmd;
    cmd.texture = nullptr;
    cmd.layer = layer;
    cmd.sortKey = position.y + (static_cast<f32>(layer) * 10000.0f);

    cmd.vertices[0] = sf::Vertex(position, color);
    cmd.vertices[1] = sf::Vertex({position.x + size.x, position.y}, color);
    cmd.vertices[2] = sf::Vertex({position.x + size.x, position.y + size.y}, color);
    cmd.vertices[3] = sf::Vertex({position.x, position.y + size.y}, color);

    m_commands.push_back(cmd);
}

void Renderer::drawLine(const sf::Vector2f& start, const sf::Vector2f& end,
                        const sf::Color& color, f32 thickness, u32 layer) {
    RenderCommand cmd;
    cmd.texture = nullptr;
    cmd.layer = layer;
    cmd.sortKey = (start.y + end.y) * 0.5f + (static_cast<f32>(layer) * 10000.0f);

    sf::Vector2f direction = end - start;
    f32 length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f normal = {-direction.y / length * thickness * 0.5f,
                           direction.x / length * thickness * 0.5f};

    cmd.vertices[0] = sf::Vertex(start + normal, color);
    cmd.vertices[1] = sf::Vertex(end + normal, color);
    cmd.vertices[2] = sf::Vertex(end - normal, color);
    cmd.vertices[3] = sf::Vertex(start - normal, color);

    m_commands.push_back(cmd);
}

void Renderer::flush() {
    sortCommands();

    const sf::Texture* currentTexture = nullptr;
    u32 batchStart = 0;
    u32 batchCount = 0;

    for (u32 i = 0; i < m_commands.size(); i++) {
        const auto& cmd = m_commands[i];

        if (cmd.texture != currentTexture || m_currentVertexCount + 4 > MAX_VERTICES) {
            if (batchCount > 0) {
                flushBatch(currentTexture, &m_vertexBuffer[batchStart], batchCount * 4);
            }
            batchStart = m_currentVertexCount;
            batchCount = 0;
            currentTexture = cmd.texture;
        }

        for (int v = 0; v < 4; v++) {
            m_vertexBuffer[m_currentVertexCount++] = cmd.vertices[v];
        }
        batchCount++;
    }

    if (batchCount > 0) {
        flushBatch(currentTexture, &m_vertexBuffer[batchStart], batchCount * 4);
    }

    m_commands.clear();
    m_currentVertexCount = 0;
    currentTexture = nullptr;
}

void Renderer::setView(const sf::View& view) {
    if (m_window) {
        m_window->setView(view);
    }
}

void Renderer::sortCommands() {
    std::stable_sort(m_commands.begin(), m_commands.end(),
        [](const RenderCommand& a, const RenderCommand& b) {
            if (a.layer != b.layer) return a.layer < b.layer;
            return a.sortKey < b.sortKey;
        });
}

void Renderer::flushBatch(const sf::Texture* texture, const sf::Vertex* vertices, u32 count) {
    if (!m_window || count == 0) return;

    if (texture) {
        m_window->draw(vertices, count, sf::Quads, *texture);
    } else {
        m_window->draw(vertices, count, sf::Quads);
    }

    m_drawCallCount++;
    m_vertexCount += count;
}

} // namespace pe::graphics
