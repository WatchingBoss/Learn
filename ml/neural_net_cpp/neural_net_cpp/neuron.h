#ifndef MY_NEURON_H
#define MY_NEURON_H

#include "def.h"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

struct Connection {
	double Weight, DeltaWeight;
};

class Neuron;
using Layer = std::vector<Neuron>;

class Neuron {
  public:
	Neuron( uint, uint );
	~Neuron( );

	void   SetOutputVal( double );
	double GetOutputVal( ) const { return m_OutputVal; }
	void   FeedForward( std::vector<Neuron> & );

	void CalcOutputGradients( double );
	void CalcHiddenGradients( const Layer & );
	void UpdateInputWeights( Layer & );

  private:
	static double eta;    // overall net training rate
	static double alpha;  // multiplier of last weight change

	double m_OutputVal;
	double m_Gradient;

	std::vector<Connection> m_OutputWeights;

	uint m_MyIndex;

  private:
	static inline double TransferFunction( double x ) { return std::tanh( x ); }
	static inline double TransferFunctionDerivation( double x ) { return 1. - x * x; }

	static inline uint m_GetRand( ) {
		std::srand( static_cast<uint>( time( NULL ) ) );
		return std::rand( ) % 2;
	}

	double sumDOW( const Layer & ) const;
};

#endif
