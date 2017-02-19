#ifndef _INTERPOLATION_IMPL_HPP_
#define _INTERPOLATION_IMPL_HPP_

template <typename T>
Interpolation<T>::Interpolation(char* inputFile1, char* inputFile2)
{
	char buff[20];

	std::ifstream fin1(inputFile1);
	std::ifstream fin2(inputFile2);

	try
	{
		if ( !fin1.is_open() )
			throw Exception(0,
				"The path of the firts input file is wrong! The file is not open!");

		if ( !fin2.is_open() )
			throw Exception(1,
				"The path of the second input file is wrong! The file is not open!");

		fin1 >> buff;
		inputNumber_ = atoi(buff);
	 	iP = new Point[inputNumber_];

		fin2 >> buff;
		outputNumber_ = atoi(buff);
		oP = new Point[outputNumber_];

		for ( int i = 0; i < inputNumber_; i++ )
		{
			fin1 >> buff;
		 iP[i].x = (T)atof(buff);

			fin1 >> buff;
		 iP[i].fx = (T)atof(buff);
		}

		for ( int i = 0; i < outputNumber_; i++ )
		{
			fin2 >> buff;
			oP[i].x = (T)atof(buff);
		}

	}
	catch ( Exception e )
	{
		e.display();
		exit(1);
	}

	interpolationType_ = linear;
	done_ = false;
}

template <typename T>
Interpolation<T>::~Interpolation()
{

}

template <typename T>
void Interpolation<T>::showInputPoints()
{
	for ( int i = 0; i < inputNumber_; i++ )
		std::cout << iP[i].x << " " << iP[i].fx << std::endl;
}

template <typename T>
void Interpolation<T>::showOutputPoints()
{
	if ( done_ == false )
	{
		std::cout << "Interpolation is not done yet!" << std::endl;
		return;
	}

	for ( int i = 0; i < outputNumber_; i++ )
		std::cout << oP[i].x << " " << oP[i].fx << std::endl;
}

template <typename T>
void Interpolation<T>::interpolate()
{
	switch ( interpolationType_ )
	{
		case linear: 
		{
			size_t ic = 0;
			size_t oc = 0;

			while ( oc < outputNumber_ )
			{
				if ( oP[oc].x > iP[ic].x )
				{
					if ( oP[oc].x < iP[ic+1].x )
					{
						// std::cout << "x0 = " << iP[ic].x << " " << "y0 = " << iP[ic].fx << std::endl;
						// std::cout << "x0 = " << oP[oc].x << " " << "y0 = ???" << std::endl;
						// std::cout << "x1 = " << iP[ic+1].x << " " << "y1 = " << iP[ic+1].fx << std::endl;
						// std::cout << std::endl;
						
						// interpolation the point
						T dx = iP[ic+1].x - iP[ic].x;

						T dy = iP[ic+1].fx - iP[ic].fx;

						oP[oc].fx = iP[ic].fx + 
									((oP[oc].x - iP[ic].x)/dx)*dy;

						++oc;
					}
					else
					{
						++ic;
					}
				}
				else 
					throw Exception ( 2, "Something goes badly!" );
			}

			done_ = true;
		}
		break;
		
		case quadratic: 
		{

		}
		break;
		case cubic: 
		{

		}

		break;
		default:
		break;
	}
}

























#endif //