#include "Simulator.hpp"

dim::VertexBuffer	Renderer::screen;

void Renderer::init()
{
	dim::Shader::add("post", "shaders/post.vert", "shaders/post.frag");
	dim::Mesh temp = dim::Mesh::screen;

	for (auto& pos : temp.positions)
		pos = dim::Vector3(pos.x, -pos.y, 0.5);

	screen.send_data("post", temp, dim::DataType::Positions | dim::DataType::TexCoords);
}

void Renderer::draw()
{
	dim::Shader::get("post").bind();
		screen.bind();
			Fractal::image.texture.bind();
				dim::Shader::get("post").send_uniform("u_texture", Fractal::image.texture);
				screen.draw();
			Fractal::image.texture.unbind();
		screen.unbind();
	dim::Shader::get("post").unbind();
}
