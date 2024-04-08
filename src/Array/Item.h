#ifndef ITEM_H
#define ITEM_H
#include <sstream>
#include <string>

#include "../colors.h"

class Item {
    int data;
    std::string color;
    float hue2rgb(float p, float q, float t) {
        if (t < 0)
            t += 1;
        if (t > 1)
            t -= 1;
        if (t < 1. / 6)
            return p + (q - p) * 6 * t;
        if (t < 1. / 2)
            return q;
        if (t < 2. / 3)
            return p + (q - p) * (2. / 3 - t) * 6;

        return p;
    }

    void hsl2rgb(float data,float s, float l) {
        this->color = "\033[38;2;";

        if (0 == s) {
            this->color += std::to_string(l * 255) + ";";
            this->color += std::to_string(l * 255) + ";";
            this->color += std::to_string(l * 255) + "m";
        } else {
            float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
            float p = 2 * l - q;
            this->color += std::to_string(int(hue2rgb(p, q, data + 1. / 3) * 255)) + ";";
            this->color += std::to_string(int(hue2rgb(p, q, data) * 255)) + ";";
            this->color += std::to_string(int(hue2rgb(p, q, data - 1. / 3) * 255)) + "m";
        }
    }

   public:
    Item(int data = 0, std::string color = reset) {
        this->color = color;
        this->data = data;
    }
    void setData(int data) {
        this->data = data;
    }
    void unMark(int size) {
        hsl2rgb(data/double(size),0.8, 0.6);
    }
    void setColor(std::string color) {
        this->color = color;
    }
    int getData() { return data; }
    std::string getColor() { return this->color; }
    bool operator<(Item& item) {
        return this->data < item.data;
    }
    bool operator>(Item& item) {
        return this->data > item.data;
    }
    bool operator>=(int item) {
        return this->data >= item;
    }
    bool operator>(int item) {
        return this->data > item;
    }
};
#endif