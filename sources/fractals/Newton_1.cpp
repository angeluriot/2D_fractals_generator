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
	changed = ImGui::SliderInt("##max_iteration", &max_iterations, 1, 15000, NULL, ImGuiSliderFlags_Logarithmic) || changed;

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

	sf::CircleShape circle(8);
	circle.setOrigin(8, 8);
	circle.setOutlineThickness(3);
	circle.setOutlineColor(sf::Color::White);

	circle.setFillColor(dim::Color(1.f, 0.f, 0.3f).to_sf());
	circle.setPosition(Simulator::world_to_screen({ p_1[0], p_1[1] }).to_sf_float());
	dim::Window::draw(circle);

	circle.setFillColor(dim::Color(0.f, 1.f, 0.3f).to_sf());
	circle.setPosition(Simulator::world_to_screen({ p_2[0], p_2[1] }).to_sf_float());
	dim::Window::draw(circle);

	circle.setFillColor(dim::Color(0.f, 0.3f, 1.f).to_sf());
	circle.setPosition(Simulator::world_to_screen({ p_3[0], p_3[1] }).to_sf_float());
	dim::Window::draw(circle);

	static dim::Vector2int prev_mouse_pos = sf::Mouse::getPosition(dim::Window::get_window());
	static bool currently_moving_point = false;
	static std::array<float, 2>* moved_point = &p_1;
	dim::Vector2int mouse_pos = sf::Mouse::getPosition(dim::Window::get_window());

	float min_prev_dist = std::min(std::min(dim::distance(prev_mouse_pos, Simulator::world_to_screen({ p_1[0], p_1[1] })),
		dim::distance(prev_mouse_pos, Simulator::world_to_screen({ p_2[0], p_2[1] }))),
		dim::distance(prev_mouse_pos, Simulator::world_to_screen({ p_3[0], p_3[1] })));

	float min_dist = std::min(std::min(dim::distance(mouse_pos, Simulator::world_to_screen({ p_1[0], p_1[1] })),
		dim::distance(mouse_pos, Simulator::world_to_screen({ p_2[0], p_2[1] }))),
		dim::distance(mouse_pos, Simulator::world_to_screen({ p_3[0], p_3[1] })));

	if (min_dist <= 10.f && min_prev_dist > 10.f)
		Simulator::moving_point = true;

	if (min_prev_dist <= 10.f && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		currently_moving_point = true;

		if (dim::distance(prev_mouse_pos, Simulator::world_to_screen({ p_3[0], p_3[1] })) <= 10.f)
			moved_point = &p_3;
		else if (dim::distance(prev_mouse_pos, Simulator::world_to_screen({ p_2[0], p_2[1] })) <= 10.f)
			moved_point = &p_2;
		else
			moved_point = &p_1;
	}

	if (min_dist > 10.f && min_prev_dist <= 10.f && !currently_moving_point)
		Simulator::moving_point = false;

	if (min_dist > 10.f && min_prev_dist > 10.f)
	{
		currently_moving_point = false;
		Simulator::moving_point = false;
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		currently_moving_point = false;

	if (currently_moving_point)
	{
		(*moved_point)[0] += Simulator::screen_to_world(mouse_pos)[0] - Simulator::screen_to_world(prev_mouse_pos)[0];
		(*moved_point)[1] += Simulator::screen_to_world(mouse_pos)[1] - Simulator::screen_to_world(prev_mouse_pos)[1];
		Simulator::image_done = false;
	}

	prev_mouse_pos = sf::Mouse::getPosition(dim::Window::get_window());
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

	image.update();
}
