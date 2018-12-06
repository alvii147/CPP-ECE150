#include <iostream>
#include <math.h>
#include "SafeMatrix.h"

using namespace std;

// Methods
void SafeMatrix::transpose()
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "transpose()");
	RESET_NAN;
	float* m;
	int temp;
	temp = _numCols;
	_numCols = _numRows;
	_numRows = temp;
	m = new (std::nothrow) float[_dataSpaceAllocated];
	int j = 0;
	for(int k = 0; k<_numRows; k++)
	{
		for(int i = k; i<_dataSpaceAllocated; i=i+_numRows)
		{
			m[j] = _data[i];
			j++;
		}
	}
	delete[] _data;
	_data = new (std::nothrow) float[_dataSpaceAllocated];
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		_data[i] = m[i];
	}
	delete[] m;
}

bool SafeMatrix::invert()
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "invert()");
	RESET_NAN;
	if(identityTest(*this))
	{
		return 1;
	}
	if(_numRows == 1 && _numCols == 1)
	{
		_data[0] = 1/_data[0];
		return 1;
	}
	float determinant = 0;
	determinant = det(*this);
	if((determinant<0.00001 && determinant>-0.00001) || _numRows != _numCols || _numRows<0 || _numCols<0)
	{
		return 0;
	}
	float* cofactors;
	cofactors = new (std::nothrow) float[_dataSpaceAllocated];
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		SafeMatrix x(_numRows - 1, _numCols - 1);
		x = reduce(*this, i/_numCols, i%_numCols);
		cofactors[i] = pow(-1, (i/_numCols)+(i%_numCols))*det(x);
	}
	cout<<endl;
	delete[] _data;
	_data = new (std::nothrow) float[_dataSpaceAllocated];
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		_data[i] = cofactors[i]/determinant;
		if(_data[i]<0.00001 && _data[i]>-0.00001)
		{
			_data[i] = 0;
		}
	}
	delete[] cofactors;
	this->transpose();
	return 1;
}

float SafeMatrix::det(SafeMatrix& m)
{
	float determinant = 0;
	if(m._numRows != m._numCols || m._numRows<0 || m._numCols<0 || m._dataSpaceAllocated<0)
	{
		return m._nan;
	}
	if(m._dataSpaceAllocated == 1)
	{
		determinant = m._data[0];
		return determinant;
	}
	if(m._dataSpaceAllocated == 4)
	{
		determinant = (m._data[0]*m._data[3])-(m._data[1]*m._data[2]);
		return determinant;
	}
	if(m._dataSpaceAllocated == 9)
	{
		float a = m._data[0]*((m._data[4]*m._data[8])-(m._data[5]*m._data[7]));
		float b = m._data[1]*((m._data[3]*m._data[8])-(m._data[5]*m._data[6]));
		float c = m._data[2]*((m._data[3]*m._data[7])-(m._data[4]*m._data[6]));
		determinant = a-b+c;
		return determinant;
	}
	if(m._dataSpaceAllocated == 16)
	{
		float t1 = m._data[5]*(m._data[10]*m._data[15]-m._data[11]*m._data[14]);
		float t2 = m._data[6]*(m._data[9]*m._data[15]-m._data[11]*m._data[13]);
		float t3 = m._data[7]*(m._data[9]*m._data[14]-m._data[10]*m._data[13]);
		float a = m._data[0]*(t1-t2+t3);
		
		t1 = m._data[4]*(m._data[10]*m._data[15]-m._data[11]*m._data[14]);
		t2 = m._data[6]*(m._data[8]*m._data[15]-m._data[11]*m._data[12]);
		t3 = m._data[7]*(m._data[8]*m._data[14]-m._data[10]*m._data[12]);
		float b = m._data[1]*(t1-t2+t3);
		
		t1 = m._data[4]*(m._data[9]*m._data[15]-m._data[11]*m._data[13]);
		t2 = m._data[5]*(m._data[8]*m._data[15]-m._data[11]*m._data[12]);
		t3 = m._data[7]*(m._data[8]*m._data[13]-m._data[9]*m._data[12]);
		float c = m._data[2]*(t1-t2+t3);
		
		t1 = m._data[4]*(m._data[9]*m._data[14]-m._data[10]*m._data[13]);
		t2 = m._data[5]*(m._data[8]*m._data[14]-m._data[10]*m._data[12]);
		t3 = m._data[7]*(m._data[8]*m._data[13]-m._data[9]*m._data[12]);
		float d = m._data[3]*(t1-t2+t3);
		
		determinant = a-b+c-d;
		return determinant;
	}
	for(int i = 0; i<m._numCols; i++)
	{
		SafeMatrix x(m._numRows - 1, m._numCols - 1);
		x = reduce(m, 0, i);
		determinant += pow(-1, i)*m._data[i]*det(x);
	}
	return determinant;
}

SafeMatrix SafeMatrix::reduce(SafeMatrix& m, int i, int j)
{
	SafeMatrix A = SafeMatrix(m._numRows - 1, m._numCols - 1);
	int b = 0;
	for(int a = 0; a<m._dataSpaceAllocated; a++)
	{
		if(a/m._numCols != i && a%m._numCols != j)
		{
			A._data[b] = m._data[a];
			b++;
		}
	}
	return A;
}

bool SafeMatrix::identityTest(SafeMatrix& m)
{
	for(int i = 0; i<m._dataSpaceAllocated; i++)
	{
		if(i/m._numCols == i%m._numCols)
		{
			if(m._data[i] != 1)
			{
				return 0;
			}
		}
		else
		{
			if(m._data[i] != 0)
			{
				return 0;
			}
		}
	}
	return 1;
}

SafeMatrix SafeMatrix::solve(const SafeMatrix& A)
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "solve()");
	RESET_NAN;
	SafeMatrix x(A._numRows, 1);
	float determinant = det(*this);
	if(_numRows != _numCols || A._numCols != 1 || (determinant<0.00001 && determinant>-0.00001))
	{
		x._numRows = NOT_A_MATRIX;
		x._numCols = NOT_A_MATRIX;
		x._dataSpaceAllocated = 0;
		x._data = 0;
		return x;
	}
	if(identityTest(*this))
	{
		return A;
	}
	SafeMatrix iM = *this;
	iM.invert();
	x = iM*A;
	return x;
}

bool SafeMatrix::appendRow(const int cols, const float data[])
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "appendRow()");
	RESET_NAN;
	if(cols != _numCols)
	{
		return 0;
	}
	_numRows = _numRows+1;
	_dataSpaceAllocated = _dataSpaceAllocated + _numCols;
	float* y;
	y = new (std::nothrow) float[_dataSpaceAllocated];
	
	for(int i = 0; i<_dataSpaceAllocated-_numCols; i++)
	{
		y[i] = _data[i];
	}
	int x = 0;
	for(int i = _dataSpaceAllocated-_numCols; i<_dataSpaceAllocated; i++)
	{
		y[i] = data[x];
		x++;
	}
	delete[] _data;
	_data = new (std::nothrow) float[_dataSpaceAllocated];
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		_data[i] = y[i];
	}
	delete[] y;
	return 1;
}

bool SafeMatrix::appendColumn(const int rows, const float data[])
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "appendColumn()");
	RESET_NAN;
	if(rows != _numRows)
	{
		return 0;
	}
	_numCols = _numCols+1;
	_dataSpaceAllocated = _numRows*_numCols;
	float* y;
	y = new (std::nothrow) float[_dataSpaceAllocated];
	
	int j = 0;
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		if((i+1)%_numCols)
		{
			y[i] = _data[j];
			j++;
		}
	}
	int x = 0;
	for(int i = _numCols-1; i<_dataSpaceAllocated; i=i+_numCols)
	{
		y[i] = data[x];
		x++;
	}
	delete[] _data;
	_data = new (std::nothrow) float[_dataSpaceAllocated];
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		_data[i] = y[i];
	}
	delete[] y;
	return 1;
}

bool SafeMatrix::deleteRow(const int rowNumber)
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "deleteRow()");
	RESET_NAN;
	if(rowNumber >= _numRows || rowNumber<0)
	{
		return 0;
	}
	float *y;
	y = new (std::nothrow) float[_dataSpaceAllocated-_numCols];
	for(int i = 0; i<rowNumber*_numCols; i++)
	{
		y[i] = _data[i];
	}
	int j = (rowNumber+1)*_numCols;
	for(int i = rowNumber*_numCols; i<_dataSpaceAllocated-_numCols; i++)
	{
		y[i] = _data[j];
		j++;
	}
	delete[] _data;
	_numRows--;
	_dataSpaceAllocated = _numRows*_numCols;
	_data = new (std::nothrow) float[_dataSpaceAllocated];
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		_data[i] = y[i];
	}
	delete[] y;
	return 1;
}

bool SafeMatrix::deleteColumn(const int columnNumber)
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "deleteColumn()");
	RESET_NAN;
	if(columnNumber >= _numCols || columnNumber<0)
	{
		return 0;
	}
	float* y;
	y = new (std::nothrow) float[_dataSpaceAllocated-_numRows];
	int j = 0;
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		if((i+_numCols-columnNumber)%_numCols != 0)
		{
			y[j] = _data[i];
			j++;
		}
	}
	_numCols--;
	_dataSpaceAllocated = _numRows*_numCols;
	delete[] _data;
	_data = new (std::nothrow) float[_dataSpaceAllocated];
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		_data[i] = y[i];
	}
	delete[] y;
	return 1;
}

bool SafeMatrix::swapRow(const int row1, const int row2)
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "swapRow()");
	RESET_NAN;
	if(row1>=_numRows || row2>=_numRows || row1<0 || row2<0)
	{
		return 0;
	}
	float* y;
	y = new (std::nothrow) float[_dataSpaceAllocated];
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		if(i/_numCols != row1 && i/_numCols != row2)
		{
			y[i] = _data[i];
		}
	}
	int j = row2*_numCols;
	for(int i = row1*_numCols; i<(row1*_numCols)+_numCols; i++)
	{
		y[i] = _data[j];
		j++;
	}
	j = row1*_numCols;
	for(int i = row2*_numCols; i<(row2*_numCols)+_numCols; i++)
	{
		y[i] = _data[j];
		j++;
	}
	delete[] _data;
	_data = new (std::nothrow) float[_dataSpaceAllocated];
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		_data[i] = y[i];
	}
	delete[] y;
	return 1;
}

bool SafeMatrix::swapColumn(const int column1, const int column2)
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "swapColumn()");
	RESET_NAN;
	if(column1>=_numCols || column2>=_numCols || column1<0 || column2<0)
	{
		return 0;
	}
	float* y;
	y = new (std::nothrow) float[_dataSpaceAllocated];
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		if(i%_numCols != column1 && i%_numCols != column2)
		{
			y[i] = _data[i];
		}
	}
	int j = column2;
	for(int i = column1; i<_dataSpaceAllocated; i+=_numCols)
	{
		y[i] = _data[j];
		j+=_numCols;
	}
	j = column1;
	for(int i = column2; i<_dataSpaceAllocated; i+=_numCols)
	{
		y[i] = _data[j];
		j+=_numCols;
	}
	delete[] _data;
	_data = new (std::nothrow) float[_dataSpaceAllocated];
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		_data[i] = y[i];
	}
	delete[] y;
	return 1;
}

bool SafeMatrix::append(const SafeMatrix& m)
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "append()");
	RESET_NAN;
	if(_numRows == m._numRows)
	{
		float* y;
		y = new (std::nothrow) float[_dataSpaceAllocated+m._dataSpaceAllocated];
		int j = 0;
		int k = 0;
		for(int i = 0; i<_dataSpaceAllocated+m._dataSpaceAllocated; i++)
		{
			if((i%(_numCols+m._numCols))<_numCols)
			{
				y[i] = _data[j];
				j++;
			}
			else
			{
				y[i] = m._data[k];
				k++;
			}
		}
		_numCols += m._numCols;
		_dataSpaceAllocated = _numRows*_numCols;
		delete[] _data;
		_data = new (std::nothrow) float[_dataSpaceAllocated];
		for(int i = 0; i<_dataSpaceAllocated; i++)
		{
			_data[i] = y[i];
		}
		delete[] y;
		return 1;
	}
	else if(_numCols == m._numCols)
	{
		float* y;
		y = new (std::nothrow) float[_dataSpaceAllocated+m._dataSpaceAllocated];
		for(int i = 0; i<_dataSpaceAllocated; i++)
		{
			y[i] = _data[i];
		}
		for(int i = _dataSpaceAllocated; i<_dataSpaceAllocated+m._dataSpaceAllocated; i++)
		{
			y[i] = m._data[i-_dataSpaceAllocated];
		}
		_numRows += m._numRows;
		_dataSpaceAllocated = _numRows*_numCols;
		delete[] _data;
		_data = new (std::nothrow) float[_dataSpaceAllocated];
		for(int i = 0; i<_dataSpaceAllocated; i++)
		{
			_data[i] = y[i];
		}
		delete[] y;
		return 1;
	}
	return 0;
}

bool SafeMatrix::isNaM() const
{
	int test = 0;
	if(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0 || _dataSpaceAllocated != _numRows*_numCols)
	{
		test = 1;
	}
	return test;
}

SafeMatrix SafeMatrix::row(const int rowNumber) const
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "row()");
	//RESET_NAN;
	SafeMatrix m = SafeMatrix(1, _numCols);
	if(rowNumber>=_numRows || rowNumber<0)
	{
		m._numRows = NOT_A_MATRIX;
		m._numCols = NOT_A_MATRIX;
		m._dataSpaceAllocated = 0;
		m._data = 0;
		return m;
	}
	for(int i = 0; i<_numCols; i++)
	{
		m._data[i] = _data[(rowNumber*_numCols)+i];
	}
	return m;
}

SafeMatrix SafeMatrix::column(const int columnNumber) const
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "column()");
	//RESET_NAN;
	SafeMatrix m = SafeMatrix(_numRows, 1);
	if(columnNumber>=_numCols || columnNumber<0)
	{
		m._numRows = NOT_A_MATRIX;
		m._numCols = NOT_A_MATRIX;
		m._dataSpaceAllocated = 0;
		m._data = 0;
		return m;
	}
	for(int i = 0; i<_numRows; i++)
	{
		m._data[i] = _data[(i*_numCols)+columnNumber];
	}
	return m;
}

Dimensions SafeMatrix::dimensions() const
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "dimensions()");
	//RESET_NAN;
	Dimensions d;
	d.rows = _numRows;
	d.cols = _numCols;
	return d;
}

SafeMatrix SafeMatrix::identity(const int n)
{
	SafeMatrix m = SafeMatrix(n, n);
	for(int i = 0; i<m._dataSpaceAllocated; i++)
	{
		if(i%(n+1) == 0)
		{
			m._data[i] = 1;
		}
		else
		{
			m._data[i] = 0;
		}
	}
	return m;
}

// Operators
float& SafeMatrix::operator()(int row, int col)
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "operator()");
	//RESET_NAN;
	if(row>=_numRows || col>=_numCols || row<0 || col<0)
	{
		return _nan;
	}
	return _data[((row)*_numCols)+col];
}  

SafeMatrix SafeMatrix::operator+(const SafeMatrix& m) const
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "operator+");
	//RESET_NAN;
	SafeMatrix x = SafeMatrix();
	if(_numRows != m._numRows || _numCols != m._numCols)
	{
		x._numRows = NOT_A_MATRIX;
		x._numRows = NOT_A_MATRIX;
		x._dataSpaceAllocated = 0;
		x._data = 0;
		return x;
	}
	x._numRows = m._numRows;
	x._numCols = m._numCols;
	x._dataSpaceAllocated = m._numRows*m._numCols;
	x._data = new (std::nothrow) float[_numRows*_numCols];
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		x._data[i] = _data[i] + m._data[i];
	}
	return x;
}

SafeMatrix SafeMatrix::operator- (const SafeMatrix& m) const
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "operator-");
	//RESET_NAN;
	SafeMatrix x = SafeMatrix();
	if(_numRows != m._numRows || _numCols != m._numCols)
	{
		x._numRows = NOT_A_MATRIX;
		x._numRows = NOT_A_MATRIX;
		x._dataSpaceAllocated = 0;
		x._data = 0;
		return x;
	}
	x._numRows = m._numRows;
	x._numCols = m._numCols;
	x._dataSpaceAllocated = m._numRows*m._numCols;
	x._data = new (std::nothrow) float[_numRows*_numCols];
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		x._data[i] = _data[i] - m._data[i];
	}
	return x;
}

SafeMatrix SafeMatrix::operator*(const SafeMatrix& m) const
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "operator*");
	//RESET_NAN;
	SafeMatrix x = SafeMatrix();
	if(_numCols != m._numRows)
	{
		x._numRows = NOT_A_MATRIX;
		x._numRows = NOT_A_MATRIX;
		x._dataSpaceAllocated = 0;
		x._data = 0;
		return x;
	}
	x._numRows = _numRows;
	x._numCols = m._numCols;
	x._dataSpaceAllocated = _numRows*m._numCols;
	x._data = new (std::nothrow) float[_numRows*m._numCols];
	float sum = 0;
	int i = 0;
	int j = 0;
	for(int k = 0; k<x._dataSpaceAllocated; k++)
	{
		i = k/m._numCols;
		j = k%m._numCols;
		sum = 0;
		for(int a = 0; a<m._numRows; a++)
		{
			sum += _data[(_numCols*i)+a]*m._data[j+(m._numCols*a)];
		}
		x._data[k] = sum;
	}
	return x;
}

void SafeMatrix::operator=(const SafeMatrix& m)
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "operator=");
	//RESET_NAN;
	_numRows = m._numRows;
	_numCols = m._numCols;
	_dataSpaceAllocated = m._dataSpaceAllocated;
	delete[] _data;
	_data = new (std::nothrow) float[m._dataSpaceAllocated];
	
	for(int i = 0; i<m._dataSpaceAllocated; i++)
	{
		_data[i] = m._data[i];
	}
}

bool SafeMatrix::operator==(const SafeMatrix& m) const
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "operator==");
	//RESET_NAN;
	if(_numRows<0 || _numCols<0 || m._numRows<0 || m._numCols<0)
	{
		return 0;
	}
	int test = 1;
	if(_numRows != m._numRows)
	{
		test = 0;
	}
	if(_numCols != m._numCols)
	{
		test = 0;
	}
	if(_dataSpaceAllocated != m._dataSpaceAllocated)
	{
		test = 0;
	}
	if(test == 1)
	{
		for(int i = 0; i<_dataSpaceAllocated; i++)
		{
			if((_data[i] - m._data[i])>0.00001 || (_data[i] - m._data[i])<-0.00001)
			{
				test = 0;
			}
		}
	}
	return test;
}

bool SafeMatrix::operator!=(const SafeMatrix& m) const
{
	INVARIANT_TEST(_numRows<0 || _numCols<0 || _dataSpaceAllocated<0, "operator!=");
	//RESET_NAN;
	int test = 0;
	if(_numRows != m._numRows)
	{
		test = 1;
	}
	if(_numCols != m._numCols)
	{
		test = 1;
	}
	if(_dataSpaceAllocated != m._dataSpaceAllocated)
	{
		test = 1;
	}
	if(test == 0)
	{
		for(int i = 0; i<_dataSpaceAllocated; i++)
		{
			if((_data[i] - m._data[i])>0.00001 || (_data[i] - m._data[i])<-0.00001)
			{
				test = 1;
			}
		}
	}
	return test;
}

  // Constructors/Destructor
SafeMatrix::SafeMatrix()
{
	_numRows = 0;
	_numCols = 0;
	_dataSpaceAllocated = 0;
	_data = NULL;
}

SafeMatrix::SafeMatrix(const SafeMatrix& m)
{
	_numRows = m._numRows;
	_numCols = m._numCols;
	_dataSpaceAllocated = m._dataSpaceAllocated;
	_data = new (std::nothrow) float[m._dataSpaceAllocated];
	if(_data == 0)
	{
		_numRows = NOT_A_MATRIX;
		_numCols = NOT_A_MATRIX;
		return;
	}
	for(int i = 0; i<m._dataSpaceAllocated; i++)
	{
		_data[i] = m._data[i];
	}
}

SafeMatrix::SafeMatrix(const Dimensions& d)
{
	int rows = d.rows;
	int cols = d.cols;
	if(rows<0 || cols<0)
	{
		_numRows = NOT_A_MATRIX;
		_numCols = NOT_A_MATRIX;
		_data = 0;
		_dataSpaceAllocated = 0;
		return;
	}
	_numRows = rows;
	_numCols = cols;
	if(rows == 0 || cols == 0)
	{
		_data = 0;
		_dataSpaceAllocated = 0;
		return;
	}
	_dataSpaceAllocated = _numRows*_numCols;
	_data = new (std::nothrow) float[_dataSpaceAllocated];
	if(_data == 0)
	{
		_numRows = NOT_A_MATRIX;
		_numCols = NOT_A_MATRIX;
	}
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		_data[i] = 0;
	}
}

SafeMatrix::SafeMatrix(const int rows, const int cols)
{
	if(rows<0 || cols<0)
	{
		_numRows = NOT_A_MATRIX;
		_numCols = NOT_A_MATRIX;
		_data = 0;
		_dataSpaceAllocated = 0;
		return;
	}
	_numRows = rows;
	_numCols = cols;
	if(rows == 0 || cols == 0)
	{
		_data = 0;
		_dataSpaceAllocated = 0;
		return;
	}
	_dataSpaceAllocated = _numRows*_numCols;
	_data = new (std::nothrow) float[_dataSpaceAllocated];
	if(_data == 0)
	{
		_numRows = NOT_A_MATRIX;
		_numCols = NOT_A_MATRIX;
	}
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		_data[i] = 0;
	}
}

SafeMatrix::SafeMatrix(const Dimensions& d, const float initVal)
{
	int rows = d.rows;
	int cols = d.cols;
	if(rows<0 || cols<0)
	{
		_numRows = NOT_A_MATRIX;
		_numCols = NOT_A_MATRIX;
		_data = 0;
		return;
	}
	_numRows = rows;
	_numCols = cols;
	if(rows == 0 || cols == 0)
	{
		_data = 0;
		_dataSpaceAllocated = 0;
		return;
	}
	_dataSpaceAllocated = _numRows*_numCols;
	_data = new (std::nothrow) float[_dataSpaceAllocated];
	if(_data == 0)
	{
		_numRows = NOT_A_MATRIX;
		_numCols = NOT_A_MATRIX;
		return;
	}
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		_data[i] = initVal;
	}
}

SafeMatrix::SafeMatrix(const int rows, const int cols, const float initVal)
{
	if(rows<0 || cols<0)
	{
		_numRows = NOT_A_MATRIX;
		_numCols = NOT_A_MATRIX;
		_data = 0;
		return;
	}
	_numRows = rows;
	_numCols = cols;
	if(rows == 0 || cols == 0)
	{
		_data = 0;
		_dataSpaceAllocated = 0;
		return;
	}
	_dataSpaceAllocated = _numRows*_numCols;
	_data = new (std::nothrow) float[_dataSpaceAllocated];
	if(_data == 0)
	{
		_numRows = NOT_A_MATRIX;
		_numCols = NOT_A_MATRIX;
		return;
	}
	for(int i = 0; i<_dataSpaceAllocated; i++)
	{
		_data[i] = initVal;
	}
}

SafeMatrix::SafeMatrix(const int rows, const float data[])
{
	if(rows<0)
	{
		_numRows = NOT_A_MATRIX;
		_numCols = NOT_A_MATRIX;
		_dataSpaceAllocated = 0;
		_data = 0;
		return;
	}
	_numRows = rows;
	_numCols = 1;
	_dataSpaceAllocated = rows;
	_data = new (std::nothrow) float[rows];
	if(_data == 0)
	{
		_numRows = NOT_A_MATRIX;
		_numCols = NOT_A_MATRIX;
		_dataSpaceAllocated = 0;
		return;
	}
	for(int i = 0; i<rows; i++)
	{
		_data[i] = data[i];
	}
}

SafeMatrix::~SafeMatrix()
{
	_numRows = 0;
	_numCols = 0;
	_dataSpaceAllocated = 0;
	delete[] _data;
}

std::ostream& operator<<(std::ostream& os, const SafeMatrix& m)
{
	INVARIANT_TEST(m._numRows<NOT_A_MATRIX, "ostream::operator<<()");
	if(m._numRows<NOT_A_MATRIX)
	{
		m.errorMsg("Method ostream::operator<<: attempting to output deleted SafeMatrix");
		abort();
	}
	if(m._numRows == NOT_A_MATRIX)
	{
		os<<"Not-a-Matrix";
		return os;
	}
	if(m._numRows == 0)
	{
		os<<"[]";
	}
	for(int i = 0; i < m._numRows; i++)
	{
		os<<"[";
		for(int j = 0; j<m._numCols; j++)
		{
			os<<MATRIX(m, i, j);
			if(j<(m._numCols - 1))
			{
				os<<", ";
			}
		}
		os<<"]";
		if(i<(m._numRows - 1))
		{
			os<<std::endl;
		}
	}
	return os;
}

void SafeMatrix::errorMsg(const char msg[]) const
{
	std::cerr<<msg<<std::endl;
}

#ifndef MARMOSET_TESTING
/*
int main()
{
	float data1[10] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	float data2[10] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0};
	float data3[10] = {0, 0, 1, 0, 0, 0, 0, 0, 0, 0};
	float data4[10] = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
	float data5[10] = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
	float data6[10] = {0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
	float data7[10] = {0, 0, 0, 0, 0, 0, 1, 0, 0, 0};
	float data8[10] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
	float data9[10] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
	float data10[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
	SafeMatrix m1(10, data1);
	m1.appendColumn(10, data2);
	m1.appendColumn(10, data3);
	m1.appendColumn(10, data4);
	m1.appendColumn(10, data5);
	m1.appendColumn(10, data6);
	m1.appendColumn(10, data7);
	m1.appendColumn(10, data8);
	m1.appendColumn(10, data9);
	m1.appendColumn(10, data10);
	float data11[10] = {1, 4, 2, -4, -4, 32, 4, 6, 1, 0};
	SafeMatrix m2(10, data11);
	/*float data1[11] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	float data2[11] = {0, 1, 0, 0, 0, 0, 8, 0, 0, 0, 0};
	float data3[11] = {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0};
	float data4[11] = {0, 0, -8, 1, 0, 0, 0, 0, 0, 0, 0};
	float data5[11] = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
	float data6[11] = {0, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0};
	float data7[11] = {0, 0, 0, -5, 0, 0, 1, 0, 0, 0, 0};
	float data8[11] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0};
	float data9[11] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
	float data10[11] = {0, 0, 0, 0, 3, 0, 0, 0, 0, 1, 0};
	float data11[11] = {0, 0, 2, 0, 3, 0, -7, 0, 0, 0, 1};
	SafeMatrix m1(11, data1);
	m1.appendColumn(11, data2);
	m1.appendColumn(11, data3);
	m1.appendColumn(11, data4);
	m1.appendColumn(11, data5);
	m1.appendColumn(11, data6);
	m1.appendColumn(11, data7);
	m1.appendColumn(11, data8);
	m1.appendColumn(11, data9);
	m1.appendColumn(11, data10);
	m1.appendColumn(11, data11);
	cout<<"Matrix m1:\n"<<m1<<endl;
	//cout<<"Matrix m1 invert:\n"<<m1<<endl;
	cout<<"Matrix m1x = m2:\n"<<m1.solve(m2)<<endl;
	return 0;
}*/
#endif