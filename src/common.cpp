/*!
 *  \file File common.cpp
 *  \brief Implementation of Common class
 *
 *  The class implemented here has methods used by all the other classes
 *
 *  \sa common.hpp
 */

#include <common.hpp>
#include <assert.h>

int debug_count = 0; //!< Global variable used as debug counter

// Hotspot screen positions to be used as shortcuts
// The number on the left is x axis and the right one is y axis
pair<float, float>
    hotspot_positions[] = {
        // TOP_LEFT
        {0.0, 0.0},
        // TOP
        {0.5, 0.0},
        // TOP_RIGHT
        {1.0, 0.0},
        // LEFT
        {0.0, 0.5},
        // CENTER
        {0.5, 0.5},
        // RIGHT
        {1.0, 0.5},
        // BOTTOM_LEFT
        {0.0, 1.0},
        // BOTTOM
        {0.5, 1.0},
        // BOTTOM_RIGHT
        {1.0, 1.0}};

/*!
	@fn       SDL_Color generate_color(int r, int g, int b, int a)
	@brief    Generates color with a alpha channel
	@param    int r, int g, int b, int a
	@return   SDL_Color rgba color value
	@warning  none
*/

SDL_Color generate_color(int red,		// red value, 	range: 0 -> 255
                         int green,		// green value, range: 0 -> 255
                         int blue,		// blue value,	range: 0 -> 255
                         int alpha) {	// alpha value, range: unknown

  LOG_METHOD_START("Common::generate_color");                   

  LOG_VARIABLE("red", red);
  assert(red >= 0 and red <= 255);
  
  LOG_VARIABLE("green", green);
  assert(green >= 0 and green <= 255);
  
  LOG_VARIABLE("blue", blue);
  assert(blue >= 0 and blue <= 255);
  
  LOG_VARIABLE("alpha", alpha);
  assert(alpha >= 0);

  
  SDL_Color color; //!< Object with the 4 color values

  color.r = red;
	color.g = green;
	color.b = blue;
	color.a = alpha;
  
  LOG_METHOD_CLOSE("Common::generate_color", color);
	return color;
}

/*!
	@fn       bool equals(const float &a, const float &b)
	@brief    Compares two float constants and returns the boolean result
	@param    const float &a, const float &b
	@return   boolean value of the comparisson between the two params
  @warning  PRECISION is a constant with 0.0001 as value, it validates the 
comparisson between the two float values
*/

bool equals(const float &a, const float &b) {
  LOG_METHOD_START("Common::equals");

  LOG_VARIABLE("a", a);
  LOG_VARIABLE("b", b);

  LOG_METHOD_CLOSE("Common::equals", (std::fabs((a - b)) <= PRECISION));
  return (std::fabs((a - b)) <= PRECISION);
}

/*!
  @fn       float close_distance(const float &from, const float &to, 
  const float &change)
	@brief    Function that cannot be comprehended by mere human beings
	@param    const float &from, const float &to, const float &change
	@return   A float result (???)
	@warning  TODO: this method must be refactorated for better understanding
*/

float close_distance(const float &from, const float &to, const float &change) {
  LOG_METHOD_START("Common::close_distance");
  
  LOG_VARIABLE("from", from);
  LOG_VARIABLE("to", to);
  LOG_VARIABLE("change", change);

	if (abs(from - to) < change) {
		return to;
  }
  else {
    // Do nothing
  }

	if (from > to) {
		return from - change;
  }
  else {
    // Do nothing
  }

  LOG_METHOD_CLOSE("Common::close_distance", from + change);

  return from + change;
}

/*!
	@fn       string convert_float_to_str(float f)
	@brief    Converts a float number to a string and returns it
	@param    float number f
	@return   The number passed as param transformed in a string
	@warning  none
*/

string convert_float_to_str(float float_number) {
  LOG_METHOD_START("Common::convert_float_to_str");
  LOG_VARIABLE("float_number", float_number);
  
  char string_to_be_saved[15]; //!< Temporary storage variable for saving chars

  sprintf(string_to_be_saved,"%.2f",float_number);

  LOG_METHOD_CLOSE("Common::convert_float_to_str", string_to_be_saved);
	return string_to_be_saved;
}
