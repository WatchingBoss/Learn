#include "train_data.h"

TrainData::TrainData( const char *file_name ) { m_TrainDataFile.open( file_name, 'r' ); }
TrainData::~TrainData( ) { m_TrainDataFile.close( ); }

void TrainData::GetTopology( std::vector<uint> &topology ) {
	std::string line, label;
	std::getline( m_TrainDataFile, line );

	std::stringstream ss( line );
	ss >> label;

	if ( IsEOF( ) || label.compare( "topology:" ) ) exit( EXIT_FAILURE );

	while ( !ss.eof( ) ) {
		uint n;
		ss >> n;
		topology.push_back( n );
	}
}

uint TrainData::GetNextInputs( std::vector<double> &input_values ) {
	return GetNums( input_values, "in:" );
}

uint TrainData::GetTargetOutputs( std::vector<double> &target_output_values ) {
	return GetNums( target_output_values, "out:" );
}

uint TrainData::GetNums( std::vector<double> &vec, const char *comp_str ) {
	vec.clear( );

	std::string line, label;
	std::getline( m_TrainDataFile, line );

	std::stringstream ss( line );
	ss >> label;

	if ( !label.compare( comp_str ) ) {
		double value;
		while ( ss >> value ) vec.push_back( value );
	}

	return static_cast<uint>( vec.size( ) );
}
