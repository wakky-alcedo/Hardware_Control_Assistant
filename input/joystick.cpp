#include "joystick.hpp"

namespace hca {

Joystick::Joystick() : x_offset(0.0f), y_offset(0.0f), raw_x(0.0f), raw_y(0.0f) {
	// Initialize all values to zero
}

Joystick::~Joystick() {
	// TODO Auto-generated destructor stub
}

void Joystick::setOriginOffset(float x_offset, float y_offset) {
	this->x_offset = x_offset;
	this->y_offset = y_offset;
}

void Joystick::calibrateOrigin() {
	// Set current raw position as the origin offset
	this->x_offset = this->raw_x;
	this->y_offset = this->raw_y;
}

void Joystick::resetOriginOffset() {
	this->x_offset = 0.0f;
	this->y_offset = 0.0f;
}

void Joystick::setRawValues(float x, float y) {
	this->raw_x = x;
	this->raw_y = y;
}

float Joystick::getX() const {
	return this->raw_x - this->x_offset;
}

float Joystick::getY() const {
	return this->raw_y - this->y_offset;
}

float Joystick::getRawX() const {
	return this->raw_x;
}

float Joystick::getRawY() const {
	return this->raw_y;
}

float Joystick::getXOffset() const {
	return this->x_offset;
}

float Joystick::getYOffset() const {
	return this->y_offset;
}

} /* namespace hca */