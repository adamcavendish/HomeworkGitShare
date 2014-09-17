#include "drawLine.hpp"

std::vector<glm::vec2>
lineDDA(const glm::vec2 & start, const glm::vec2 & end, float deltaPixel) {
        float dx = end.x - start.x;
        float dy = end.y - start.y;
        if(dx == 0) {
            return drawLineVertical(start, end, deltaPixel);
        }//if

        if(dy == 0) {
            return drawLineHorizontal(start, end, deltapixel);
        }
}//lineDDA(start, end, deltaPixel)

std::vector<glm::vec2>
drawLineHorizontal(const glm::vec2 & start, const glm::vec2 & end, float deltaPixel) {
}//drawLineHorizontal(start, end, deltaPixel) {

std::vector<glm::vec2>
drawLineVertical(const glm::vec2 & start, const glm::vec2 & end, float deltaPixel) {
}

