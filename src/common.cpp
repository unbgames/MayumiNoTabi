/*!
 *  \file File common.cpp
 *  \brief Implementation of Common class
 *
 *  The class implemented here has methods used by all the other classes
 *
 *  \sa common.hpp
 */

#include <common.hpp>

int debugCount = 0; //!< Global variable used as debug counter

// Hotspot screen positions to be used as shortcuts
// The number on the left is x axis and the right one is y axis
pair<float, float>
    HotspotPos[] = {
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
	@fn       SDL_Color MakeColor(int r, int g, int b, int a)
	@brief    Generates color with a alpha channel
	@param    int r, int g, int b, int a
	@return   SDL_Color rgba color value
	@warning  none
*/

SDL_Color MakeColor(int r,		// red value, 	range: 0 -> 255
										int g,		// green value, range: 0 -> 255
										int b,		// blue value,	range: 0 -> 255
										int a) {	// alpha value, range: unknown

  SDL_Color color; //!< Object with the 4 color values

  color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;

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
	return (std::fabs((a - b)) <= PRECISION);
}

/*!
  @fn       float closeDist(const float &from, const float &to, 
  const float &change)
	@brief    Function that cannot be comprehended by mere human beings
	@param    const float &from, const float &to, const float &change
	@return   A float result (???)
	@warning  TODO: this method must be refactorated for better understanding
*/

float closeDist(const float &from, const float &to, const float &change) {
	if (abs(from - to) < change) {
		return to;
	}

	if (from > to) {
		return from - change;
	}

	return from + change;
}

/*!
	@fn       string FloatToStr(float f)
	@brief    Converts a float number to a string and returns it
	@param    float number f
	@return   The number passed as param transformed in a string
	@warning  none
*/

string FloatToStr(float f) {
  char s[15]; //!< Temporary storage variable for saving chars

  sprintf(s,"%.2f",f);

	return s;
}
