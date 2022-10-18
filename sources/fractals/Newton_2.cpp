#include "Simulator.hpp"

Newton_2::Newton_2()
{
	reset();
}

Fractal::Type Newton_2::get_type() const
{
	return Type::Newton_2;
}

void Newton_2::menu()
{
	bool changed = false;

	ImGui::NewLine();

	ImGui::Text("The max iterations number:");
	changed = ImGui::SliderInt("##max_iteration", &max_iterations, 1, 15000, NULL, ImGuiSliderFlags_Logarithmic) || changed;

	ImGui::NewLine();

	ImGui::Text("Smooth:");
	ImGui::SameLine();
	changed = ImGui::Checkbox("##smooth", &smooth) || changed;

	if (changed)
		Simulator::image_done = false;
}

void Newton_2::reset()
{
	max_iterations = 30;
	smooth = true;
	image.reset(dim::Window::get_size().x, dim::Window::get_size().y);
}

void Newton_2::compute()
{
	ComputeShader::choose_function("newton_2");
	ComputeShader::add_argument(image.buffer);
	ComputeShader::add_argument(max_iterations);
	ComputeShader::add_argument(Simulator::position[0]);
	ComputeShader::add_argument(Simulator::position[1]);
	ComputeShader::add_argument(Simulator::area_width);

	double area_height = Simulator::area_width * ((double)dim::Window::get_size().y / (double)dim::Window::get_size().x);

	ComputeShader::add_argument(area_height);
	ComputeShader::add_argument((int)smooth);

	ComputeShader::launch(cl::NDRange(dim::Window::get_size().x, dim::Window::get_size().y));

	image.update();
}
