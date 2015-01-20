#include "Matrix.h"


Matrix::Matrix(int size)
{
	init(size, false);
}
Matrix::Matrix(void)
{
	init(4, false);
}
Matrix::Matrix(bool identity) 
{
	init(4, true);
}
Matrix::Matrix(int size, bool identity) 
{
	init(size, true);
}

void Matrix::init(int size, bool idenity)
{
	_size = size;
	_elem = new float*[size];
	for (int i = 0; i < size; i++)
	{
		_elem[i] = new float[size];
		for (int j = 0; j < size; j++)
		{
			if (idenity && i == j)
				_elem[i][j] = 1;
			else _elem[i][j] = 0;
		}
	}
}

unique_ptr<float[]> Matrix::getList()
{
	unique_ptr<float[]> outArray(new float[_size*_size]);
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
			outArray[i*_size + j] = _elem[i][j];
	return outArray;
}

float** Matrix::getMatrix()
{
	return _elem;
}

int Matrix::getSize() const
{
	return _size;
}

Matrix::~Matrix(void)
{
	for (int i = 0; i < _size; i++)
	{
		delete _elem[i];
	}
	delete[] _elem;
}
