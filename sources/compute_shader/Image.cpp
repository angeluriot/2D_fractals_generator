#include "Simulator.hpp"

void Image::reset(unsigned int width, unsigned int height)
{
	data.clear();
	data.resize(width * height);
	buffer = ComputeShader::Buffer(data, Permissions::Write);

	GLuint id;
	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
		glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	texture = dim::Texture(id);
}

void Image::update(unsigned int width, unsigned int height)
{
	ComputeShader::get_data(buffer, data);

	texture.bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, (GLvoid*)data.data());
		glGenerateMipmap(GL_TEXTURE_2D);
	texture.unbind();
}

void Image::save(const std::string& filename)
{
	static int nb = 1;
	sf::Image sf_image;
	sf_image.create(dim::Window::get_size().x, dim::Window::get_size().y);

	for (int i = 0; i < dim::Window::get_size().x; i++)
		for (int j = 0; j < dim::Window::get_size().y; j++)
			sf_image.setPixel(i, j, data[j * dim::Window::get_size().x + i].to_sf());

	sf_image.saveToFile(filename + "_" + std::to_string(nb++));
}
