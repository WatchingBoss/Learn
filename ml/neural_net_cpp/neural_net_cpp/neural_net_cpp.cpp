// neural_net_cpp.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <vector>

#include "def.h"
#include "net.h"

int main( ) {
	std::vector<uint> topology;
	for ( uint i = 3; i > 0; --i ) topology.push_back( i );

	Net neuNet( topology );

	std::vector<double> input_values;
	std::vector<double> target_values;
	std::vector<double> result_values;

	neuNet.FeedForward( input_values );
	neuNet.BackPropagation( target_values );
	neuNet.GetResults( result_values );

	std::getc( stdin );

	return 0;
}
