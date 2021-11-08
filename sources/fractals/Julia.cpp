#include "Simulator.hpp"

Julia::Julia()
{
	reset();
}

Fractal::Type Julia::get_type() const
{
	return Type::Julia;
}

void Julia::menu()
{
	bool changed = false;
	float temp[2];
	temp[0] = c.x;
	temp[1] = c.y;

	ImGui::NewLine();

	ImGui::Text("The inital C value :");
	changed = ImGui::SliderFloat2("##c", temp, -2.f, 2.f) || changed;

	c.x = temp[0];
	c.y = temp[1];

	ImGui::NewLine();

	ImGui::Text("The maximum number of iterations :");
	changed = ImGui::SliderInt("##max_iteration", &max_iterations, 1, 10000, NULL, ImGuiSliderFlags_Logarithmic) || changed;

	if (changed)
		Simulator::image_done = false;
}

void Julia::reset()
{
	c = dim::Vector2(0.f, 0.f);
	max_iterations = 100;

	Renderer::fractal.send_data("julia", mesh, dim::DataType::Positions | dim::DataType::TexCoords);
	glGetError();
}

void Julia::render()
{
	Renderer::frame_buffer.bind();
		Renderer::frame_buffer.clear();
		dim::Shader::get("julia").bind();
			Renderer::fractal.bind();

				dim::Shader::get("julia").send_uniform("u_c", c);
				dim::Shader::get("julia").send_uniform("u_max_iterations", max_iterations);
				dim::Shader::get("julia").send_uniform("u_position", Simulator::position);
				dim::Shader::get("julia").send_uniform("u_area", dim::Vector2(Simulator::area_width,
					Simulator::area_width * (static_cast<float>(dim::Window::get_size().y) / static_cast<float>(dim::Window::get_size().x))));

				Renderer::fractal.draw();

			Renderer::fractal.unbind();
		dim::Shader::get("julia").unbind();
	Renderer::frame_buffer.unbind();
}
