#include "Simulator.hpp"

Newton_1::Newton_1()
{
	reset();
}

Fractal::Type Newton_1::get_type() const
{
	return Type::Newton_1;
}

void Newton_1::menu()
{
	bool changed = false;

	ImGui::NewLine();

	ImGui::Text("The max iterations number:");
	changed = ImGui::SliderInt("##max_iteration", &max_iterations, 1, 10000, NULL, ImGuiSliderFlags_Logarithmic) || changed;

	ImGui::NewLine();

	ImGui::Text("The first point value:");
	changed = ImGui::SliderFloat2("##p_1", p_1.data(), -2.f, 2.f) || changed;

	ImGui::NewLine();

	ImGui::Text("The second point value:");
	changed = ImGui::SliderFloat2("##p_2", p_2.data(), -2.f, 2.f) || changed;

	ImGui::NewLine();

	ImGui::Text("The third point value:");
	changed = ImGui::SliderFloat2("##p_3", p_3.data(), -2.f, 2.f) || changed;

	ImGui::NewLine();

	ImGui::Text("Smooth:");
	ImGui::SameLine();
	changed = ImGui::Checkbox("##smooth", &smooth) || changed;

	if (changed)
		Simulator::image_done = false;
}

void Newton_1::reset()
{
	max_iterations = 30;
	p_1 = { 1.f, 0.f };
	p_2 = { -0.5f, (float)sqrt(3.) / 2.f };
	p_3 = { -0.5f, -(float)sqrt(3.) / 2.f };
	smooth = true;
	image.reset(dim::Window::get_size().x, dim::Window::get_size().y);
}

void Newton_1::compute()
{
	ComputeShader::choose_function("newton_1");
	ComputeShader::add_argument(image.buffer);
	ComputeShader::add_argument(max_iterations);
	ComputeShader::add_argument(Simulator::position[0]);
	ComputeShader::add_argument(Simulator::position[1]);
	ComputeShader::add_argument(Simulator::area_width);

	double area_height = Simulator::area_width * ((double)dim::Window::get_size().y / (double)dim::Window::get_size().x);

	ComputeShader::add_argument(area_height);
	ComputeShader::add_argument(p_1);
	ComputeShader::add_argument(p_2);
	ComputeShader::add_argument(p_3);
	ComputeShader::add_argument((int)smooth);

	ComputeShader::launch(cl::NDRange(dim::Window::get_size().x, dim::Window::get_size().y));

	image.update(dim::Window::get_size().x, dim::Window::get_size().y);
}
