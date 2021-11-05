#include "Simulator.hpp"

void Simulator::init()
{
	Renderer::init();
}

void Simulator::update()
{
	
}

void Simulator::check_events(const sf::Event& sf_event)
{
	Renderer::check_events(sf_event);
}

void Simulator::draw()
{
	Renderer::clear();
	Renderer::draw();
}
