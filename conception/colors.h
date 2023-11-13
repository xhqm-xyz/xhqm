#ifndef XHQM_COLORS
#define XHQM_COLORS
#include "../head.h"
namespace xhqm
{
    using rgb = std::array<xhqm::byte, 3>;
    using rgba = std::array<xhqm::byte, 4>;

    inline std::vector<xhqm::color> assignment(xhqm::size size, std::vector<xhqm::color> colors)
    {
        std::vector<xhqm::color> asscolors;
        if (colors.size()) {
            xhqm::size pos = 0;
            double len = size / (colors.size() - 1.0);

            xhqm::size ind = 0;
            while (ind < size) {
                if (ind < pos * len) {
                    double val = ind / len - pos;
                    xhqm::color color = xhqm_rgba(0, 0, 0, 255);
                    std::array<xhqm::measure, 4> tempcolor{0.0,0.0,0.0,0.0};
                    tempcolor[0] = (1 - val) * xhqmcolor_r(colors[pos - 1]) + val * xhqmcolor_r(colors[pos]);
                    tempcolor[1] = (1 - val) * xhqmcolor_g(colors[pos - 1]) + val * xhqmcolor_g(colors[pos]);
                    tempcolor[2] = (1 - val) * xhqmcolor_b(colors[pos - 1]) + val * xhqmcolor_b(colors[pos]);
                    tempcolor[3] = (1 - val) * xhqmcolor_a(colors[pos - 1]) + val * xhqmcolor_a(colors[pos]);
                    xhqmcolor_r(color) = static_cast<xhqm::byte>(tempcolor[0]);
                    xhqmcolor_g(color) = static_cast<xhqm::byte>(tempcolor[1]);
                    xhqmcolor_b(color) = static_cast<xhqm::byte>(tempcolor[2]);
                    xhqmcolor_a(color) = static_cast<xhqm::byte>(tempcolor[3]);
                    asscolors.push_back(color);
                    ++ind;
                }
                else {
                    ++pos;
                }
            }

            return asscolors;
        }
    }
    inline xhqm::color assignment(xhqm::measure pos, std::vector<xhqm::color> colors)
    {
        //pos 0.0--1.0
        xhqm::measure val = pos * colors.size();
        xhqm::size ind = static_cast<xhqm::size>(val);
        val -= ind;

        xhqm::color value = 0;
        if (colors.empty())
            value = 0;
        else if (colors.size() == 1)
            value = colors[0];
        else if (colors.size() >= 1) {
            std::array<xhqm::measure, 4> tempcolor{ 0.0,0.0,0.0,0.0 };
            tempcolor[0] = (1 - val) * xhqmcolor_r(colors[ind]) + val * xhqmcolor_r(colors[ind + 1]);
            tempcolor[1] = (1 - val) * xhqmcolor_g(colors[ind]) + val * xhqmcolor_g(colors[ind + 1]);
            tempcolor[2] = (1 - val) * xhqmcolor_b(colors[ind]) + val * xhqmcolor_b(colors[ind + 1]);
            tempcolor[3] = (1 - val) * xhqmcolor_a(colors[ind]) + val * xhqmcolor_a(colors[ind + 1]);
            xhqmcolor_r(value) = static_cast<xhqm::byte>(tempcolor[0]);
            xhqmcolor_g(value) = static_cast<xhqm::byte>(tempcolor[1]);
            xhqmcolor_b(value) = static_cast<xhqm::byte>(tempcolor[2]);
            xhqmcolor_a(value) = static_cast<xhqm::byte>(tempcolor[3]);
        }
        return value;
    }

    inline xhqm::rgb color2rgb(const xhqm::color& color) {
        return { xhqmcolor_r(color) , xhqmcolor_g(color) , xhqmcolor_b(color) };
    }

    inline xhqm::rgba color2rgba(const xhqm::color& color) {
        return { xhqmcolor_r(color) , xhqmcolor_g(color) , xhqmcolor_b(color) , xhqmcolor_a(color) };
    }
}
#endif