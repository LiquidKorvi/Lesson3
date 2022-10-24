#include "SpriteFonts.h"
#include "Texture2D.h"

#include <iostream>

namespace Renderer {

    SpriteFonts::SpriteFonts(std::shared_ptr<Texture2D> pTexture,
        std::string initialSubTexture,
        std::shared_ptr<ShaderProgram> pShaderProgram,
        const glm::vec2& position,
        const glm::vec2& size,
        const float rotation)

        : Sprite(std::move(pTexture), std::move(initialSubTexture), std::move(pShaderProgram), position, size, rotation)
    {
        m_pCurrentAnimationDurations = m_statesMap.end();
        m_dirty = true;
    }




    void SpriteFonts::render() const
    {
        if (m_dirty)
        {
            auto subTexture = m_pTexture->getSubTexture(m_pCurrentAnimationDurations->second[m_currentFrame].first);

            const GLfloat textureCoords[] = {
                // U  V
                subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
                subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
                subTexture.rightTopUV.x,   subTexture.rightTopUV.y,

                subTexture.rightTopUV.x,   subTexture.rightTopUV.y,
                subTexture.rightTopUV.x,   subTexture.leftBottomUV.y,
                subTexture.leftBottomUV.x, subTexture.leftBottomUV.y
            };

            glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordsVBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(textureCoords), &textureCoords);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            m_dirty = false;
        }
        Sprite::render();
    }
}