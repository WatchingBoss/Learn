// neural_net_cpp.cpp : Defines the entry point for the application.
//

#include <cassert>

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "def.h"
#include "net.h"
#include "train_data.h"

void show_vector_values( const char *label, std::vector<double> &v, std::ofstream &out ) {
	out << label << " ";
	for ( const double &i : v ) out << i << " ";
	out << "\n";
}

void train_neu_net( Net *neuNet, std::vector<uint> &topology ) {
	constexpr uint buf_size = 100;
	char           train_data_in[buf_size], train_data_out[buf_size];

	std::snprintf( train_data_in, buf_size, "%s/data/in.txt", PROJECT_PATH_NAME );
	std::snprintf( train_data_out, buf_size, "%s/data/out.txt", PROJECT_PATH_NAME );

	TrainData train_data( train_data_in );

	std::vector<double> input_values, target_values, result_values;

	std::ofstream out_data( train_data_out, 'w' );

	int train_pass = 0;

	while ( !train_data.IsEOF( ) ) {
		++train_pass;
		out_data << "\nPass";

		if ( train_data.GetNextInputs( input_values ) != topology.at( 0 ) ) break;

		show_vector_values( ": Inputs :", input_values, out_data );
		neuNet->FeedForward( input_values );

		neuNet->GetResults( result_values );
		show_vector_values( "Outputs:", result_values, out_data );

		train_data.GetTargetOutputs( target_values );
		show_vector_values( "Targets:", target_values, out_data );
		assert( target_values.size( ) == topology.back( ) );

		neuNet->BackPropagation( target_values );

		out_data << "Next recent average error: " << neuNet->GetRecentAverageError( )
		         << "\n";
	}

	out_data << "Done\n";

	out_data.close( );
}

int main( ) {
	std::vector<uint> topology;
	Net *             neuNet = new Net( topology );
	train_neu_net( neuNet, topology );

	delete neuNet;

	std::cout << "Done\n";

	std::getc( stdin );

	return 0;
}
