#include "Simulator.hpp"

void Image::reset(unsigned int width, unsigned int height)
{
	data.clear();
	data.resize(width * height, dim::Vector4(0.f, 1.f, 0.f, 1.f));
	buffer = ComputeShader::Buffer(data, Permissions::All);

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
