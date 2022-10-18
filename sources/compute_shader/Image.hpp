#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "libraries.hpp"

class Image
{
public:

	dim::Texture texture;			// The texture filled with the image data.
	std::vector<dim::Color> data;	// The image data.
	cl::Buffer buffer;				// The OpenCL buffer containing the image data.
	dim::Vector2int size;

	Image() = default;
	Image(const Image& other) = default;

	/**
	 * @brief Clear the texture and the data.
	 *
	 * @param width the new width of the image
	 * @param height the new height of the image
	 */
	void reset(unsigned int width, unsigned int height);

	/**
	 * @brief Fill the image with a color.
	 *
	 * @param color the color to fill the image with
	 */
	void fill(const dim::Color& color);

	/**
	 * @brief Update the texture with the image data.
	 */
	void update();

	/**
	 * @brief Save the image.
	 *
	 * @param folder the folder to save the image to
	 */
	void save(std::string folder);
};

#endif
