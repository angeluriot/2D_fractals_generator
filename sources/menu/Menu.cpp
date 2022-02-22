#include "menu/Menu.hpp"
#include "Simulator.hpp"

bool	Menu::visible	= true;
bool	Menu::active	= false;

void Menu::check_events(const sf::Event& sf_event)
{
	if (sf_event.type == sf::Event::KeyReleased && sf_event.key.code == sf::Keyboard::Key::F1)
		visible = !visible;
}

void Menu::title(const std::string& text)
{
	float window_width = ImGui::GetWindowSize().x;
	float text_width = ImGui::CalcTextSize(text.data()).x;

	ImGui::NewLine();
	ImGui::SetCursorPosX((window_width - text_width) * 0.5f);
	ImGui::Text(text.data());
	ImGui::Separator();
}

std::vector<bool> Menu::centered_buttons(const std::vector<std::string> texts, float buttons_height, float spaces_size)
{
	float window_width = ImGui::GetWindowSize().x;
	float buttons_widths = (window_width - ((texts.size() + 2) * spaces_size)) / texts.size();
	std::vector<bool> result(texts.size());

	ImGui::NewLine();
	ImGui::NewLine();

	for (int i = 0; i < texts.size(); i++)
	{
		ImGui::SameLine();
		ImGui::SetCursorPosX(spaces_size + buttons_widths * i + spaces_size * i);
		ImGui::Text("");
		ImGui::SameLine();
		result[i] = ImGui::Button(texts[i].data(), ImVec2(buttons_widths, buttons_height));
	}

	return result;
}

void Menu::display()
{
	if (visible)
	{
		ImGui::Begin("Simulation settings (F1 to hide)");
		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.9f);

		ImGui::NewLine();

		Fractal::Type fractal_type = Simulator::fractal->get_type();

		ImGui::Text("The type of fractal:");

		if (ImGui::Combo("##fractal_type", reinterpret_cast<int*>(&fractal_type), "Julia\0Mandelbrot\0Burning Ship\0Buddhabrot\0Newton 1\0Newton 2"))
		{
			delete Simulator::fractal;

			switch (fractal_type)
			{
			case Fractal::Type::Julia:
				Simulator::fractal = new Julia();
				break;

			case Fractal::Type::Mandelbrot:
				Simulator::fractal = new Mandelbrot();
				break;

			case Fractal::Type::BurningShip:
				Simulator::fractal = new BurningShip();
				break;

			case Fractal::Type::Buddhabrot:
				Simulator::fractal = new Buddhabrot();
				break;

			case Fractal::Type::Newton_1:
				Simulator::fractal = new Newton_1();
				break;

			case Fractal::Type::Newton_2:
				Simulator::fractal = new Newton_2();
				break;

			default:
				break;
			}

			Simulator::reset();
		}

		Simulator::fractal->menu();

		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();

		ImGui::Text("Position:");
		ImGui::NewLine();
		ImGui::Text(("Real: " + to_string(Simulator::position[0])).data());
		ImGui::Text(("Imaginary: " + to_string(Simulator::position[1]) + "i").data());

		active = ImGui::IsWindowFocused();

		ImGui::End();
	}
}

std::string to_string(const double& value)
{
	std::ostringstream out;
	out.precision(15);
	out << std::fixed << value;
	return out.str();
}
