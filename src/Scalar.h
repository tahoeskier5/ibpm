#ifndef _SCALAR_H_
#define _SCALAR_H_

#include <blitz/array.h>
#include "Grid.h"

BZ_USING_NAMESPACE(blitz)

class Flux;

/*!
	\file Scalar.h
	\class Scalar

	\brief Store a 2D array of scalar values, located at cell centers.
	
	Also provides scalar-valued math operations, such as curl and divergence
	of a Flux, discrete sin transform, and Laplacian and its inverse, as well
	as inner product of scalar fields.

	\author Clancy Rowley
	\author $LastChangedBy$
	\date  4 Jul 2008
	\date $LastChangedDate$
	\version $Revision$
*/

class Scalar {
public:
	/// Allocate memory for the 2D array
	Scalar(const Grid& grid) :
		_grid(grid),
		_nx(grid.getNx()),
		_ny(grid.getNy()),
		_data(_nx,_ny) {};
	
	/// Allocate new array, copy the data
	inline Scalar(const Scalar& f) :
		_grid(f._grid),
		_nx(f._nx),
		_ny(f._ny),
		_data(_nx,_ny)
	{
		// copy data
		this->_data = f._data;
	}
	
	/// Deallocate memory in the destructor
	~Scalar() {
		// deallocation automatic for Blitz++ arrays?
	};

	const Grid& getGrid() {
		return _grid;
	}

	/// Copy assignment
	inline Scalar& operator=(const Scalar& f) {
		assert(f._nx == this->_nx);
		assert(f._ny == this->_ny);
		this->_data = f._data;
		return *this;
	};

	/// Copy assignment from double
	inline Scalar& operator=(double a) {
		this->_data = a;
		return *this;
	};

	/// f(i,j) refers to the value at index (i,j)
	inline double& operator()(int i, int j) {
		return _data(i,j);
	};
	
	/// f += g
	inline Scalar& operator+=(const Scalar& f) {
		assert(f._nx == this->_nx);
		assert(f._ny == this->_ny);
		this->_data += f._data;
		return *this;
	}

	/// f += a
	inline Scalar& operator+=(double a) {
		this->_data += a;
		return *this;
	}

	/// f -= g
	inline Scalar& operator-=(const Scalar& f) {
		assert(f._nx == this->_nx);
		assert(f._ny == this->_ny);
		this->_data -= f._data;
		return *this;
	}

	/// f -= a
	inline Scalar& operator-=(double a) {
		this->_data -= a;
		return *this;
	}

	/// f + g
	inline Scalar operator+(const Scalar& f) {
		assert(f._nx == this->_nx);
		assert(f._ny == this->_ny);
		Scalar g = *this;
		g += f;
		return g;
	};
	
	/// f + a
	inline Scalar operator+(double a) {
		Scalar g = *this;
		g += a;
		return g;
	};
	
	/// f - g
	inline Scalar operator-(Scalar& f) {
		assert(f._nx == this->_nx);
		assert(f._ny == this->_ny);
		Scalar g = *this;
		g -= f;
		return g;
	};
	
	/// f - a
	inline Scalar operator-(double a) {
		Scalar g = *this;
		g -= a;
		return g;
	};
	
	/// f *= g
	inline Scalar& operator*=(const Scalar& f) {
		assert(f._nx == this->_nx);
		assert(f._ny == this->_ny);
		this->_data *= f._data;
		return *this;
	}

	/// f *= a
	inline Scalar& operator*=(double a) {
		this->_data *= a;
		return *this;
	}

	/// f * g
	inline Scalar operator*(Scalar& f) {
		assert(f._nx == this->_nx);
		assert(f._ny == this->_ny);
		Scalar g = *this;
		g *= f;
		return g;
	};
	
	/// f * a
	inline Scalar operator*(double a) {
		Scalar g = *this;
		g *= a;
		return g;
	};
	
	/// f /= g
	inline Scalar& operator/=(const Scalar& f) {
		assert(f._nx == this->_nx);
		assert(f._ny == this->_ny);
		this->_data /= f._data;
		return *this;
	}

	/// f /= a
	inline Scalar& operator/=(double a) {
		this->_data /= a;
		return *this;
	}

	/// f / g
	inline Scalar operator/(Scalar& f) {
		assert(f._nx == this->_nx);
		assert(f._ny == this->_ny);
		Scalar g = *this;
		g /= f;
		return g;
	};
	
	/// f / a
	inline Scalar operator/(double a) {
		Scalar g = *this;
		g /= a;
		return g;
	};
	
	
	/// Set *this to the curl of q
	Scalar& curl(const Flux& q);
	
	/// set *this to the discrete sin transform of f
	Scalar& sinTransform(const Scalar& f);

	/// set *this to the inverse discrete sin transform of f
	Scalar& sinTransformInv(const Scalar& f);
	
	/// set *this to the Laplacian of f
	Scalar& laplacian(const Scalar& f);

	/// set *this to the inverse Laplacian of f
	Scalar& laplacianInverse(const Scalar& f);

	/// set *this to the divergence of q
	Scalar& divergence(const Flux& q);

	/// return the inner product of f and *this
	double dot(const Scalar& f);
	
private:
	
	const Grid& _grid;
	const int _nx;
	const int _ny;
	Array<double,2> _data;
	
	// Declare variables for implementation here
};

/// -f
inline Scalar operator-(Scalar& f) {
	Scalar g = f;
	g *= -1;
	return g;
}

/// a + f
inline Scalar operator+(double a, Scalar& f) {
	Scalar g = f;
	g += a;
	return g;
};
	
/// a - f
inline Scalar operator-(double a, Scalar& f) {
	Scalar g = -f;
	g += a;
	return g;
};
	
/// a * f
inline Scalar operator*(double a, Scalar& f) {
	Scalar g = f;
	g *= a;
	return g;
};

/// a / f
inline Scalar operator/(double a, Scalar& f) {
	Scalar g(f.getGrid());
	g = a;
	g /= f;
	return g;
};

#endif /* _SCALAR_H_ */