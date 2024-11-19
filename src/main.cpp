#include <sil/sil.hpp>
#include "random.hpp"
#include <iostream>
#include <cmath>


// Exercice "Ne gardez que le vert"
void green_only(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = 0;
            image.pixel(x, y).b = 0;
        }
    }
}

// Exercice
void channels_swap(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x, y).r, image.pixel(x, y).b);
        }
    }
}

void black_white(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {

            glm::vec3 &pixel = image.pixel(x, y);
            float gray = 0.21 * pixel.r + 0.72 * pixel.g + 0.07 * pixel.b;

            pixel.r = gray;
            pixel.g = gray;
            pixel.b = gray;
        }
    }
}

void negative(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {

            glm::vec3 &pixel = image.pixel(x, y);
            pixel.r = 1.0f - pixel.r;
            pixel.g = 1.0f - pixel.g;
            pixel.b = 1.0f - pixel.b;
        }
    }
}

void gradiant(sil::Image &image)
{
    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            image.pixel(x, y) = glm::vec3{static_cast<float>(x) / static_cast<float>(image.width() - 1)};
        }
    }
}

void mirror(sil::Image &image)
{
    for (int x{0}; x < image.width() / 2; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x, y), image.pixel(image.width() - (x + 1), y));
        }
    }
}

void noise(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (true_with_probability(0.2f))
            {
                image.pixel(x, y).r = random_float(0, 1);
                image.pixel(x, y).g = random_float(0, 1);
                image.pixel(x, y).b = random_float(0, 1);
            }
        }
    }
}

void rotating(sil::Image &image)
{
    int new_width = image.height();
    int new_height = image.width();

    sil::Image new_image{new_width, new_height};
    for (int y{0}; y < new_image.height(); y++)
    {
        for (int x{0}; x < new_image.width(); x++)
        {
            new_image.pixel(x, y) = image.pixel(image.width() - 1 - y, x);
        }
    }
    image = new_image;
}

void rgb_split(sil::Image &image)
{
    sil::Image splitImage{image};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (x < 30)
            {
                splitImage.pixel(x, y).b = image.pixel(x + 30, y).b;
            }
            else if (x > image.width() - 31)
            {
                splitImage.pixel(x, y).r = image.pixel(x - 30, y).r;
            }
            else
            {
                splitImage.pixel(x, y).r = image.pixel(x - 30, y).r;
                splitImage.pixel(x, y).b = image.pixel(x + 30, y).b;
            }
        }
    }
    image = splitImage;
}

void dark_luminosity(sil::Image &image)
{

    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            image.pixel(x, y).r = std::pow(image.pixel(x, y).r, 2);
            image.pixel(x, y).g = std::pow(image.pixel(x, y).g, 2);
            image.pixel(x, y).b = std::pow(image.pixel(x, y).b, 2);
        }
    }
}

void light_luminosity(sil::Image &image)
{

    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            image.pixel(x, y).r = std::sqrt(image.pixel(x, y).r);
            image.pixel(x, y).g = std::sqrt(image.pixel(x, y).g);
            image.pixel(x, y).b = std::sqrt(image.pixel(x, y).b);
        }
    }
}

int main()
{
    {
        sil::Image image{"images/logo.png"};
        green_only(image);
        image.save("output/green_only.png");
    }

    {
        sil::Image image{"images/logo.png"};
        channels_swap(image);
        image.save("output/channels_swap.png");
    }

    {
        sil::Image image{"images/logo.png"};
        black_white(image);
        image.save("output/black_white.png");
    }

    {
        sil::Image image{"images/logo.png"};
        negative(image);
        image.save("output/negative.png");
    }

    {
        sil::Image image{300, 200};
        gradiant(image);
        image.save("output/gradiant.png");
    }

    {
        sil::Image image{"images/logo.png"};
        mirror(image);
        image.save("output/mirror.png");
    }

    {
        sil::Image image{"images/logo.png"};
        noise(image);
        image.save("output/noise.png");
    }

    {
        sil::Image image{"images/logo.png"};
        rotating(image);
        image.save("output/rotation.png");
    }
    {
        sil::Image image{"images/logo.png"};
        rgb_split(image);
        image.save("output/rgb_split.png");
    }

    {
        sil::Image image{"images/photo.jpg"};
        dark_luminosity(image);
        image.save("output/dark_luminosity.png");
    }

    {
        sil::Image image{"images/photo.jpg"};
        light_luminosity(image);
        image.save("output/light_luminosity.png");
    }
}
