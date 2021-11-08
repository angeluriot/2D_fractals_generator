#include "renderer/Renderer.hpp"
#include "Simulator.hpp"

dim::FrameBuffer	Renderer::frame_buffer;
dim::VertexBuffer	Renderer::fractal;
dim::VertexBuffer	Renderer::screen;

void Renderer::init()
{
	dim::Shader::add("julia", "shaders/julia.vert", "shaders/julia.frag");
	dim::Shader::add("mandelbrot", "shaders/mandelbrot.vert", "shaders/mandelbrot.frag");
	dim::Shader::add("post", "shaders/post.vert", "shaders/post.frag");

	frame_buffer.create(dim::Window::get_size());
	screen.send_data("post", dim::Mesh::screen, dim::DataType::Positions | dim::DataType::TexCoords);
}

void Renderer::check_events(const sf::Event& sf_event)
{
	if (sf_event.type == sf::Event::Resized)
	{
		Simulator::image_done = false;
		frame_buffer.set_size(dim::Window::get_size());
	}
}

void Renderer::draw()
{
	dim::Shader::get("post").bind();
		screen.bind();
			frame_buffer.get_texture().bind();
				dim::Shader::get("post").send_uniform("u_texture", frame_buffer.get_texture());
				screen.draw();
			frame_buffer.get_texture().unbind();
		screen.unbind();
	dim::Shader::get("post").unbind();
}
