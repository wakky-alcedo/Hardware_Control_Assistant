#ifndef JOYSTICK_HPP_
#define JOYSTICK_HPP_

#include <cmath>

namespace hca {

template<typename T>
struct Position {
	T x;
	T y;
	
	Position() : x(static_cast<T>(0)), y(static_cast<T>(0)) {}
	Position(T x, T y) : x(x), y(y) {}
	
	// Operators for convenience
	Position operator+(const Position& other) const {
		return Position(x + other.x, y + other.y);
	}
	
	Position operator-(const Position& other) const {
		return Position(x - other.x, y - other.y);
	}
	
	Position& operator+=(const Position& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	
	Position& operator-=(const Position& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
	
	// Distance and angle methods
	double get_magnitude() const {
		return std::sqrt(static_cast<double>(x * x + y * y));
	}
	
	double get_angle_radians() const {
		return std::atan2(static_cast<double>(y), static_cast<double>(x));
	}
	
	double get_angle_degrees() const {
		return get_angle_radians() * 180.0 / M_PI;
	}
	
	// Get distance from another position
	double get_distance_to(const Position& other) const {
		Position diff = *this - other;
		return diff.get_magnitude();
	}
	
	// Get angle to another position
	double get_angle_to(const Position& other) const {
		Position diff = other - *this;
		return diff.get_angle_radians();
	}
};

template<typename T>
struct PolarCoordinate {
	double magnitude;  // 距離（常にdouble型で精度を保つ）
	double angle;      // 角度（ラジアン、常にdouble型で精度を保つ）
	
	PolarCoordinate() : magnitude(0.0), angle(0.0) {}
	PolarCoordinate(double mag, double ang) : magnitude(mag), angle(ang) {}
	
	// Convert from Cartesian coordinates
	PolarCoordinate(const Position<T>& pos) {
		magnitude = pos.get_magnitude();
		angle = pos.get_angle_radians();
	}
	
	// Convert to Cartesian coordinates
	Position<T> to_cartesian() const {
		return Position<T>(
			static_cast<T>(magnitude * std::cos(angle)),
			static_cast<T>(magnitude * std::sin(angle))
		);
	}
	
	// Get angle in degrees
	double get_angle_degrees() const {
		return angle * 180.0 / M_PI;
	}
	
	// Set angle in degrees
	void set_angle_degrees(double degrees) {
		angle = degrees * M_PI / 180.0;
	}
};

template<typename T>
class Joystick {
private:
	T x_offset;
	T y_offset;
	T raw_x;
	T raw_y;
	bool calibrated_flag; // キャリブレーション状態を保持

public:
	Joystick() : x_offset(static_cast<T>(0)), y_offset(static_cast<T>(0)), 
	             raw_x(static_cast<T>(0)), raw_y(static_cast<T>(0)), calibrated_flag(false) {
		// Initialize all values to zero and not calibrated
	}
	
	virtual ~Joystick() {
		// Destructor
	}
	
	// Origin offset methods
	void set_origin_offset(T x_offset, T y_offset) {
		this->x_offset = x_offset;
		this->y_offset = y_offset;
		this->calibrated_flag = true; // 手動でオフセットを設定した場合もキャリブレーション済みとする
	}
	
	void set_origin_offset(const Position<T>& offset) {
		this->x_offset = offset.x;
		this->y_offset = offset.y;
		this->calibrated_flag = true; // 手動でオフセットを設定した場合もキャリブレーション済みとする
	}
	
	void calibrate_origin() {
		// Set current raw position as the origin offset
		this->x_offset = this->raw_x;
		this->y_offset = this->raw_y;
		this->calibrated_flag = true; // キャリブレーション完了
	}
	
	void reset_origin_offset() {
		this->x_offset = static_cast<T>(0);
		this->y_offset = static_cast<T>(0);
		this->calibrated_flag = false; // リセット時はキャリブレーション未完了状態に戻す
	}
	
	// Calibration status methods
	bool is_calibrated() const {
		return this->calibrated_flag;
	}
	
	void set_calibrated(bool calibrated) {
		this->calibrated_flag = calibrated;
	}
	
	// Input methods
	void set_raw_values(T x, T y) {
		this->raw_x = x;
		this->raw_y = y;
	}
	
	void set_raw_values(const Position<T>& pos) {
		this->raw_x = pos.x;
		this->raw_y = pos.y;
	}
	
	// Output methods (with offset applied)
	T get_x() const {
		return this->raw_x - this->x_offset;
	}
	
	T get_y() const {
		return this->raw_y - this->y_offset;
	}
	
	Position<T> get_position() const {
		return Position<T>(this->raw_x - this->x_offset, this->raw_y - this->y_offset);
	}
	
	// Polar coordinate methods (with offset applied)
	PolarCoordinate<T> get_polar_coordinate() const {
		return PolarCoordinate<T>(get_position());
	}
	
	double get_magnitude() const {
		return get_position().get_magnitude();
	}
	
	double get_angle_radians() const {
		return get_position().get_angle_radians();
	}
	
	double get_angle_degrees() const {
		return get_position().get_angle_degrees();
	}
	
	// Raw values (without offset)
	T get_raw_x() const {
		return this->raw_x;
	}
	
	T get_raw_y() const {
		return this->raw_y;
	}
	
	Position<T> get_raw_position() const {
		return Position<T>(this->raw_x, this->raw_y);
	}
	
	// Raw polar coordinate methods (without offset)
	PolarCoordinate<T> get_raw_polar_coordinate() const {
		return PolarCoordinate<T>(get_raw_position());
	}
	
	double get_raw_magnitude() const {
		return get_raw_position().get_magnitude();
	}
	
	double get_raw_angle_radians() const {
		return get_raw_position().get_angle_radians();
	}
	
	double get_raw_angle_degrees() const {
		return get_raw_position().get_angle_degrees();
	}
	
	// Offset values
	T get_x_offset() const {
		return this->x_offset;
	}
	
	T get_y_offset() const {
		return this->y_offset;
	}
	
	Position<T> get_offset() const {
		return Position<T>(this->x_offset, this->y_offset);
	}
};

// Common type aliases for convenience
using PositionFloat = Position<float>;
using PositionDouble = Position<double>;
using PositionInt = Position<int>;
using PositionInt16 = Position<int16_t>;
using PositionInt32 = Position<int32_t>;

using PolarCoordinateFloat = PolarCoordinate<float>;
using PolarCoordinateDouble = PolarCoordinate<double>;
using PolarCoordinateInt = PolarCoordinate<int>;
using PolarCoordinateInt16 = PolarCoordinate<int16_t>;
using PolarCoordinateInt32 = PolarCoordinate<int32_t>;

using JoystickFloat = Joystick<float>;
using JoystickDouble = Joystick<double>;
using JoystickInt = Joystick<int>;
using JoystickInt16 = Joystick<int16_t>;
using JoystickInt32 = Joystick<int32_t>;

} /* namespace hca */

#endif /* JOYSTICK_HPP_ */