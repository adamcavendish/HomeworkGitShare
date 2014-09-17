#include "drawLine.hpp"
// C-Standard
#include <cstdio>
#include <cassert>
#include <cmath>
// STL
#include <iostream>

std::vector<glm::vec2>
lineDDA(const glm::vec2 & start, const glm::vec2 & end, float deltaPixel) {
    float dx = end.x - start.x;
    float dy = end.y - start.y;

    if(dx == 0) {
        return drawLineVertical(start, end, deltaPixel);
    }//if

    if(dy == 0) {
        return drawLineHorizontal(start, end, deltaPixel);
    }//if

    // lineDDA_impl_incx() must ensure:
    // 1. start.x < end.x
    // 2. slope in range [-1, 1]
    auto lineDDA_impl_incx = [](
            const glm::vec2 & start,
            const glm::vec2 & end,
            float slope,
            float deltaPixel)
    {
        std::vector<glm::vec2> ret;
        auto reserveSize =
            static_cast<std::size_t>(std::abs(end.x - start.x) / deltaPixel);
        ret.reserve(reserveSize);

        float x = start.x;
        float y = start.y;
        while(x < end.x) {
            ret.push_back(glm::vec2(x, y));
            x += deltaPixel;
            y += slope * deltaPixel;
        }//while

        return ret;
    };//lineDDA_impl_incx(start, end, slope, deltaPixel)

    // lineDDA_impl_incy() must ensure:
    // 1. start.y < end.y
    // 2. slope not in range [-1, 1]
    auto lineDDA_impl_incy = [](
            const glm::vec2 & start,
            const glm::vec2 & end,
            float slope,
            float deltaPixel)
    {
        std::vector<glm::vec2> ret;
        auto reserveSize =
            static_cast<std::size_t>(std::abs(end.y - start.y) / deltaPixel);
        ret.reserve(reserveSize);

        slope = 1.0 / slope;

        float x = start.x;
        float y = start.y;
        while(y < end.y) {
            ret.push_back(glm::vec2(x, y));
            y += deltaPixel;
            x += slope * deltaPixel;
        }//while

        return ret;
    };//lineDDA_impl_incy(start, end, slope, deltaPixel)
    
    glm::vec2 implStart = start;
    glm::vec2 implEnd = end;
    float slope = dy / dx;

    // slope not in range [-1, 1]
    if(slope < -1.0 || slope > 1.0) {
        // swap start and end point if dy < 0
        if(dy < 0) {
            implStart = end;
            implEnd = start;
        }//if

        return lineDDA_impl_incy(implStart, implEnd, slope, deltaPixel);
    }//if

    // slope in range [-1, 1]
    // swap start and end point if dx < 0
    if(dx < 0) {
        implStart = end;
        implEnd = start;
    }//if

    return lineDDA_impl_incx(implStart, implEnd, slope, deltaPixel);
}//lineDDA(start, end, deltaPixel)

std::vector<glm::vec2>
drawLineHorizontal(const glm::vec2 & start, const glm::vec2 & end, float deltaPixel) {
    assert(end.y - start.y == 0 && "drawLineHorizontal: slope must be 0");
    std::vector<glm::vec2> ret;
    float y = start.y;
    for(float x = start.x; x < end.x; x += deltaPixel)
        ret.push_back(glm::vec2(x, y));
    return ret;
}//drawLineHorizontal(start, end, deltaPixel) {

std::vector<glm::vec2>
drawLineVertical(const glm::vec2 & start, const glm::vec2 & end, float deltaPixel) {
    assert(end.x - start.x == 0 && "drawLineVertical: slope must be Infinity");
    std::vector<glm::vec2> ret;
    float x = start.x;
    for(float y = start.y; y < end.y; y += deltaPixel)
        ret.push_back(glm::vec2(x, y));
    return ret;
}//drawLineVertical(start, end, deltaPixel)

