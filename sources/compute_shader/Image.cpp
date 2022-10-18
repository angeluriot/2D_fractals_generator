#include "Simulator.hpp"

void Image::reset(unsigned int width, unsigned int height)
{
	size = dim::Vector2int(width, height);
	data.clear();
	data.resize(size.x * size.y);
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

void Image::fill(const dim::Color& color)
{
	ComputeShader::get_data(buffer, data);

	for (auto& d : data)
		d = color;

	buffer = ComputeShader::Buffer(data, Permissions::Write);
}

void Image::update()
{
	ComputeShader::get_data(buffer, data);

	texture.bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_FLOAT, (GLvoid*)data.data());
		glGenerateMipmap(GL_TEXTURE_2D);
	texture.unbind();
}

int get_value_from_name(std::string name)
{
	if (name.substr(0, 7) == "screen_")
	{
		name = name.substr(7);

		if (name.substr(name.size() - 4) == ".png")
		{
			name = name.substr(0, name.size() - 4);

			try
			{
				return std::stoi(name);
			}

			catch (const std::exception& e)
			{
				return -1;
			}
		}
	}

	return -1;
}

void Image::save(std::string folder)
{
	folder += folder.back() == '/' ? "" : "/";
	std::filesystem::create_directories("./" + folder);

	sf::Image sf_image;
	sf_image.create(size.x, size.y);

	for (int i = 0; i < size.x; i++)
		for (int j = 0; j < size.y; j++)
		{
			dim::Color color = data[j * size.x + i];

			if (color.r > 1.f) color.r = 1.f;
			if (color.g > 1.f) color.g = 1.f;
			if (color.b > 1.f) color.b = 1.f;
			color.a = 1.f;

			sf_image.setPixel(i, j, color.to_sf());
		}

	int nb = -1;

	for (const auto & entry : std::filesystem::directory_iterator(folder))
	{
		int value = get_value_from_name(entry.path().filename().string());

		if (value > nb)
			nb = value;
	}

	sf_image.saveToFile(folder + "screen_" + std::to_string(nb + 1) + ".png");
}
