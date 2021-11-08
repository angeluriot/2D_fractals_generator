#include "Simulator.hpp"

Mandelbrot::Mandelbrot()
{
	reset();
}

Fractal::Type Mandelbrot::get_type() const
{
	return Type::Mandelbrot;
}

void Mandelbrot::menu()
{
	bool changed = false;

	ImGui::NewLine();

	ImGui::Text("The maximum number of iterations :");
	changed = ImGui::SliderInt("##max_iteration", &max_iterations, 1, 10000, NULL, ImGuiSliderFlags_Logarithmic) || changed;

	if (changed)
		Simulator::image_done = false;
}

void Mandelbrot::reset()
{
	max_iterations = 100;

	Renderer::fractal.send_data("mandelbrot", mesh, dim::DataType::Positions | dim::DataType::TexCoords);
	glGetError();
}

void Mandelbrot::render()
{
	Renderer::frame_buffer.bind();
		Renderer::frame_buffer.clear();
		dim::Shader::get("mandelbrot").bind();
			Renderer::fractal.bind();

				dim::Shader::get("mandelbrot").send_uniform("u_max_iterations", max_iterations);
				dim::Shader::get("mandelbrot").send_uniform("u_position", Simulator::position);
				dim::Shader::get("mandelbrot").send_uniform("u_area", dim::Vector2(Simulator::area_width,
					Simulator::area_width * (static_cast<float>(dim::Window::get_size().y) / static_cast<float>(dim::Window::get_size().x))));

				Renderer::fractal.draw();

			Renderer::fractal.unbind();
		dim::Shader::get("mandelbrot").unbind();
	Renderer::frame_buffer.unbind();
}
