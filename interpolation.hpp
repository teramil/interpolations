#ifndef _INTERPOLATION_HPP_
#define _INTERPOLATION_HPP_

#include <cstdlib>
#include <fstream>
#include <iostream>

enum InterpolationType {linear = 1, quadratic, cubic};

template <typename T>
class Interpolation  
{
	class Exception
	{
	private:
		int number_;
		char* line_;
	public:
		Exception (int number, char* line)
		{
			this->number_ = number;
			this->line_ = line;
		}

		void display ()
		{
			std::cout << "Exception " << number_ << ": " << line_ << std::endl;
		}
	};

private:
	struct Point
	{	
		T x;
		T fx;
	};

	size_t inputNumber_; 	// the number of inuput points
	size_t outputNumber_;	// the number of points to interpolate
	Point* iP; 	// input points
	Point* oP;	// iterpolated points
	InterpolationType interpolationType_; // the kind of interpolation
	bool done_;	// this say about output points have been computed or not

public:
	Interpolation ();
	Interpolation (char* inputFile1, char* inputFile2);
	~Interpolation ();
	void showInputPoints();
	void showOutputPoints();
	void interpolate();

};

#include "interpolation_impl.hpp"
 

#endif //