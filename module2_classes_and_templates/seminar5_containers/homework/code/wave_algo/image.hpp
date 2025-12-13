/*
    Создадим класс изображения
*/
#pragma once

#include <iostream>
#include <vector>
#include <fstream>

namespace {

class Image
{
private:
    int mWidth  {0};
    int mHeight {0};
    std::vector<unsigned char> mData {};

public:

    struct Color
    {
        unsigned char r, g, b;

        bool operator==(const Color& c) 
        {
            return r == c.r && g == c.g && b == c.b;
        }

        bool operator!=(const Color& c) 
        {
            return !(*this == c);
        }

        Color& operator+=(const Color& c) 
        {
            r = saturateCast(r + c.r);
            g = saturateCast(g + c.g);
            b = saturateCast(b + c.b);
            return *this;
        }

        Color operator+(const Color& c) const
        {
            Color result = *this;
            result += c;
            return result;
        }

    private:

        unsigned char saturateCast(int a)
        {
            if (a > 255)
                a = 255;
            return static_cast<unsigned char>(a);
        }
        
    };

    Image() {}

    Image(const std::string& filename)
    {
        loadPPM(filename);
    }

    Image(int width, int height) : mWidth(width), mHeight(height)
    {
        mData.resize(3 * mWidth * mHeight);
        std::fill(mData.begin(), mData.end(), 0);
    }

    Image(int width, int height, Color c) : mWidth(width), mHeight(height)
    {
        mData.resize(3 * mWidth * mHeight);
        for (int j = 0; j < mHeight; ++j)
        {
            for (int i = 0; i < mWidth; ++i)
            {
                setPixel(i, j, c);
            }
        }
    }

    int getWidth() const {return mWidth;}
    int getHeight() const {return mHeight;}
    unsigned char* getData() {return mData.data();}

    void setPixel(int i, int j, Color c)
    {
        mData[3 * (j * mWidth + i) + 0] = c.r;
        mData[3 * (j * mWidth + i) + 1] = c.g;
        mData[3 * (j * mWidth + i) + 2] = c.b;
    }

    Color getPixel(int i, int j) const
    {
        std::size_t index = j * mWidth + i;
        return {mData[3 * index + 0], mData[3 * index + 1], mData[3 * index + 2]};
    }

    void loadPPMText(const std::string& filename)
    {
        std::ifstream in(filename);
        if (in.fail())
        {
            std::cerr << "Error. Can't open file" << filename << "!" << std::endl;
            std::exit(1);
        }

        std::string type;
        in >> type;
        if (type != "P3")
        {
            std::cerr << "Error. File should be type P3 .ppm file!" << std::endl;
            std::exit(1);
        }

        in >> mWidth >> mHeight;

        int maxValue;
        in >> maxValue;

        mData.resize(3 * mWidth * mHeight);
        for (int j = 0; j < mHeight; ++j)
        {
            for (int i = 0; i < mWidth; ++i)
            {
                int r, g, b;
                in >> r >> g >> b;
                Color pixel = {static_cast<unsigned char>(r), 
                               static_cast<unsigned char>(g), 
                               static_cast<unsigned char>(b)};
                setPixel(i, j, pixel);
            }
        }
    }

    void savePPMText(const std::string& filename) const
    {
        std::ofstream out(filename);
        if (out.fail())
        {
            std::cerr << "Error. Can't create file " << filename << "!" << std::endl;
            std::exit(1);
        }

        out << "P3\n" << mWidth << " " << mHeight << "\n255\n";
        for (int j = 0; j < mHeight; ++j)
        {
            for (int i = 0; i < mWidth; ++i)
            {
                out << static_cast<int>(mData[3 * (j * mWidth + i) + 0]) << " " 
                    << static_cast<int>(mData[3 * (j * mWidth + i) + 1]) << " " 
                    << static_cast<int>(mData[3 * (j * mWidth + i) + 2]) << "\n";
            }
        }
    }

    void loadPPMBinary(const std::string& filename)
    {
        std::ifstream in {filename, std::ios::binary};
        if (in.fail())
        {
            std::cerr << "Error. Can't open file" << filename << "!" << std::endl;
            std::exit(1);
        }

        std::string type;
        in >> type;
        if (type != "P6")
        {
            std::cerr << "Error. File should be type P6 .ppm file!" << std::endl;
            std::exit(1);
        }

        in >> mWidth >> mHeight;

        int maxValue;
        in >> maxValue;

        char temp;
        in >> std::noskipws >> temp;

        mData.resize(3 * mWidth * mHeight);
        in.read(reinterpret_cast<char*>(&mData[0]), mData.size());
    }

    void savePPMBinary(const std::string& filename) const
    {
        std::ofstream out(filename, std::ios::binary);
        if (out.fail())
        {
            std::cerr << "Error. Can't create file " << filename << "!" << std::endl;
            std::exit(1);
        }
        out << "P6\n" << mWidth << " " << mHeight << "\n255\n";
        out.write(reinterpret_cast<const char*>(&mData[0]), mData.size());
    }

    void loadPPM(const std::string& filename)
    {
        std::ifstream in(filename, std::ios::binary);
        if (in.fail())
        {
            std::cerr << "Error. Can't open file!" << std::endl;
            std::exit(1);
        }

        std::string type;
        in >> type;
        if (type == "P3")
        {
            loadPPMText(filename);
        }
        else if (type == "P6")
        {
            loadPPMBinary(filename);
        }
        else
        {
            std::cerr << "Error. File should be type P3 or P6 .ppm file!" << std::endl;
        }
    }

    void printInfo() const
    {
        std::cout << "Width = " << mWidth << std::endl;
        std::cout << "Height = " << mHeight << std::endl;
        std::cout << "Colors:\n";
        for (int j = 0; j < mHeight; ++j)
        {
            for (int i = 0; i < mWidth; ++i)
            {
                auto pixel = getPixel(i, j);
                std::cout << "(" << static_cast<int>(pixel.r) << ", " <<
                                    static_cast<int>(pixel.g) << ", " <<
                                    static_cast<int>(pixel.b) << ") ";
            }
            std::cout << "\n";
        }
    }
};

}