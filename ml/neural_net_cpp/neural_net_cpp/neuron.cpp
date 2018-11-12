#include "neuron.h"

double Neuron::eta   = .15;
double Neuron::alpha = .5;

Neuron::Neuron( uint outputs_num, uint my_index ) : m_MyIndex( my_index ) {
	for ( uint i = 0; i < outputs_num; ++i ) {
		double weight       = m_GetRand( );
		double delta_weight = 0;
		m_OutputWeights.push_back( { weight, delta_weight } );
	}
}
Neuron::~Neuron( ) {}

void Neuron::SetOutputVal( double val ) {}

void Neuron::FeedForward( std::vector<Neuron> &prev_layer ) {
	double sum = 0;

	for ( uint i = 0; i < prev_layer.size( ); ++i )
		sum += prev_layer.at( i ).GetOutputVal( ) *
		       prev_layer.at( i ).m_OutputWeights.at( m_MyIndex ).Weight;

	m_OutputVal = TransferFunction( sum );
}

void Neuron::CalcOutputGradients( double target_val ) {
	double delta = target_val - m_OutputVal;
	m_Gradient   = delta * TransferFunctionDerivation( m_OutputVal );
}

void Neuron::CalcHiddenGradients( const Layer &next_layer ) {
	double dow = sumDOW( next_layer );
	m_Gradient = dow * TransferFunctionDerivation( m_OutputVal );
}

void Neuron::UpdateInputWeights( Layer &prev_layer ) {
	for ( auto &neuron : prev_layer ) {
		double old_delta_weight = neuron.m_OutputWeights.at( m_MyIndex ).DeltaWeight;
		double new_delta_weight =
		    eta * neuron.GetOutputVal( ) * m_Gradient + alpha * old_delta_weight;

		neuron.m_OutputWeights.at( m_MyIndex ).DeltaWeight = new_delta_weight;
		neuron.m_OutputWeights.at( m_MyIndex ).Weight += new_delta_weight;
	}
}

double Neuron::sumDOW( const Layer &next_layer ) const {
	double sum = 0;
	for ( uint i = 0; i < next_layer.size( ); ++i ) sum += m_OutputWeights.at( i ).Weight;
	return sum;
}
