#include "Simulator.hpp"

dim::VertexBuffer	Renderer::screen;

void Renderer::init()
{
	dim::Shader::add("post", "shaders/post.vert", "shaders/post.frag");
	screen.send_data("post", dim::Mesh::screen, dim::DataType::Positions | dim::DataType::TexCoords);
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
