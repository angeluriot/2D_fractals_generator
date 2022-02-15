#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "libraries.hpp"

class Image
{
public:

	dim::Texture texture;
	std::vector<dim::Color> data;
	cl::Buffer buffer;

	Image() = default;
	Image(const Image& other) = default;

	void reset(unsigned int width, unsigned int height);
	void update(unsigned int width, unsigned int height);
	void save(const std::string& filename);
};

#endif
