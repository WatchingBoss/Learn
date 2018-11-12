#include "net.h"

#include <cassert>
#include <iostream>

Net::Net( const std::vector<uint> &topology ) {
	uint layers_count = topology.size( );

	for ( uint layer_num = 0; layer_num < layers_count; ++layer_num ) {
		m_Layers.push_back( Layer( ) );

		uint outputs_num = layer_num == layers_count ? 0 : topology.at( layer_num + 1 );

		for ( uint neuron_num = 0; neuron_num <= topology.at( layer_num );
		      ++neuron_num ) {
			m_Layers.back( ).push_back( Neuron( outputs_num, neuron_num ) );
		}
	}
}
Net::~Net( ) {}

void Net::FeedForward( const std::vector<double> &input_vals ) {
	uint input_num = input_vals.size( );
	assert( input_num == m_Layers.at( 0 ).size( ) - 1 );

	for ( uint i = 0; i < input_num; ++i )
		m_Layers.at( 0 ).at( i ).SetOutputVal( input_vals.at( i ) );

	for ( uint layer_num = 1; layer_num < m_Layers.size( ); ++layer_num ) {
		auto &prev_layer = m_Layers.at( layer_num - 1 );
		auto &layer      = m_Layers.at( layer_num );
		for ( uint i = 0; i < layer.size( ); ++i )
			layer.at( i ).FeedForward( prev_layer );
	}
}

void Net::BackPropagation( const std::vector<double> &target_vals ) {
	// Calculate overall net error (RMS of ouput neuron error)
	Layer &     output_layer      = m_Layers.back( );
	std::size_t output_layer_size = output_layer.size( );
	std::size_t layers_size       = m_Layers.size( );
	m_Error                       = 0;

	for ( uint i = 0; i < output_layer_size; ++i ) {
		double delta = target_vals.at( i ) - output_layer.at( i ).GetOutputVal( );
		m_Error += delta * delta;
	}
	m_Error /= output_layer_size - 1;
	m_Error = std::sqrt( m_Error );

	// Implement resent average measurement
	m_RecentAverageError =
	    ( m_RecentAverageError * m_RecentAverageSmoothingFactor + m_Error ) /
	    ( m_RecentAverageSmoothingFactor + 1. );

	// Calculate output layer gradients
	for ( uint i = 0; i < output_layer_size - 1; ++i )
		output_layer.at( i ).CalcOutputGradients( target_vals.at( i ) );

	// Calculate gradients on hidden layer
	for ( uint layers_num = layers_size - 2; layers_num > 0; --layers_num ) {
		Layer &hidden_layer = m_Layers.at( layers_num );
		Layer &next_layer   = m_Layers.at( layers_num + 1 );

		for ( auto &neuron : hidden_layer ) neuron.CalcHiddenGradients( next_layer );
	}

	// For all layers form outputs to first hidden layer, update connection weights
	for ( uint layer_num = layers_size - 1; layer_num > 0; --layer_num ) {
		Layer &layer      = m_Layers.at( layer_num );
		Layer &prev_layer = m_Layers.at( layer_num );

		for ( auto &neuron : layer ) neuron.UpdateInputWeights( prev_layer );
	}
}

void Net::GetResults( std::vector<double> &result_vals ) const {
	result_vals.clear( );

	for ( uint i = 0; i < m_Layers.back( ).size( ); ++i )
		result_vals.push_back( m_Layers.back( ).at( i ).GetOutputVal );
}
