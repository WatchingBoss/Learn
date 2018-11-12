#ifndef MY_NET_H
#define MY_NET_H

#include <vector>

#include "def.h"
#include "neuron.h"

class Net {
  public:
	Net( const std::vector<uint> & );
	~Net( );

	void FeedForward( const std::vector<double> & );
	void BackPropagation( const std::vector<double> & );
	void GetResults( std::vector<double> & ) const;

  private:
	std::vector<Layer> m_Layers;

	double m_Error;
	double m_RecentAverageError;
	double m_RecentAverageSmoothingFactor;
};

#endif
