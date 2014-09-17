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
    }//if

    // lineDDA_impl must ensure:
    // 1. start.x < end.x
    // 2. slope is in range (-1, 1)
    auto lineDDA_impl = [](
            const glm::vec2 & start,
            const glm::vec2 & end,
            const float slope,
            float deltaPixel)
    {
        std::vector<glm::vec2> ret;
        auto reserveSize = static_cast<std::size_t>((end.x - start.x) / deltaPixel);
        ret.reserve(reserveSize);

        float x = start.x;
        float y = start.y;
        while(x < end.x) {
            ret.push_back(glm::vec2(x, y));
            x += deltaPixel;
            y += slope * deltaPixel;
        }//for

        return ret;
    }//lineDDA_impl(start, end, deltaPixel)
    
    glm::vec2 implStart, implEnd;
    float slope;
    if(dx < 0) {
        implStart = end;
        implEnd = start;
    } else {
    }
}//lineDDA(start, end, deltaPixel)

std::vector<glm::vec2>
drawLineHorizontal(const glm::vec2 & start, const glm::vec2 & end, float deltaPixel) {

}//drawLineHorizontal(start, end, deltaPixel) {

std::vector<glm::vec2>
drawLineVertical(const glm::vec2 & start, const glm::vec2 & end, float deltaPixel) {

}//drawLineVertical(start, end, deltaPixel)

