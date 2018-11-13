#ifndef MY_TRAIN_DATA_H
#define MY_TRAIN_DATA_H

#include <fstream>
#include <sstream>
#include <vector>

#include "def.h"

class TrainData {
  public:
	TrainData( const char * );
	~TrainData( );

	inline bool IsEOF( ) { return m_TrainDataFile.eof( ); }

	void GetTopology( std::vector<uint> & );

	uint GetNextInputs( std::vector<double> & );
	uint GetTargetOutputs( std::vector<double> & );

  private:
	std::fstream m_TrainDataFile;

  private:
	uint GetNums( std::vector<double> &, const char * );
};

#endif
