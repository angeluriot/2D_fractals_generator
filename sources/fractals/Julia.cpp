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

	ImGui::NewLine();

	ImGui::Text("The inital C value:");
	changed = ImGui::SliderFloat2("##c", c.data(), -2.f, 2.f) || changed;

	ImGui::NewLine();

	ImGui::Text("The max iterations number:");
	changed = ImGui::SliderInt("##max_iteration", &max_iterations, 10, 15000, NULL, ImGuiSliderFlags_Logarithmic) || changed;

	changed = ColorPallet::menu(pallet_index) || changed;

	ImGui::NewLine();

	ImGui::Text("The range of the colors:");
	changed = ImGui::SliderFloat("##color_range", &color_range, 0.01f, 10.f, NULL, ImGuiSliderFlags_Logarithmic) || changed;

	ImGui::NewLine();

	ImGui::Text("The shift of the colors:");
	changed = ImGui::SliderFloat("##color_shift", &color_shift, 0.f, 1.f) || changed;

	ImGui::NewLine();

	ImGui::Text("Smooth:");
	ImGui::SameLine();
	changed = ImGui::Checkbox("##smooth", &smooth) || changed;

	if (changed)
		Simulator::image_done = false;
}

void Julia::reset()
{
	c = { 0.f, 0.f };
	max_iterations = 100;
	pallet_index = 0;
	color_range = 3.f;
	color_shift = 0.f;
	smooth = true;
	image.reset(dim::Window::get_size().x, dim::Window::get_size().y);
}

void Julia::compute()
{
	ComputeShader::choose_function("julia");
	ComputeShader::add_argument(image.buffer);
	ComputeShader::add_argument(c[0]);
	ComputeShader::add_argument(c[1]);
	ComputeShader::add_argument(max_iterations);
	ComputeShader::add_argument(Simulator::position[0]);
	ComputeShader::add_argument(Simulator::position[1]);
	ComputeShader::add_argument(Simulator::area_width);

	double area_height = Simulator::area_width * ((double)dim::Window::get_size().y / (double)dim::Window::get_size().x);

	ComputeShader::add_argument(area_height);

	cl::Buffer pallet = ComputeShader::Buffer(ColorPallet::pallets[pallet_index], Permissions::Read);
	int size;

	if (pallet_index == ColorPallet::rgb)
		size = -1;

	else if (pallet_index == ColorPallet::black_or_white)
		size = -2;

	else
		size = (int)ColorPallet::pallets[pallet_index].size() - 1;

	ComputeShader::add_argument(pallet);
	ComputeShader::add_argument(size);
	ComputeShader::add_argument(color_range);
	ComputeShader::add_argument(color_shift);

	int smooth_int = (size > 0 ? smooth : 1);
	ComputeShader::add_argument(smooth_int);

	ComputeShader::launch(cl::NDRange(dim::Window::get_size().x, dim::Window::get_size().y));

	image.update();
}
