#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <fstream>
#include <sstream>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]


//#define	SAVE_IN_FILE	1 


int string_to_int( std::string s )
{
	int i;
	std::istringstream( s ) >> i;
	return i;
}

std::vector<std::string> split( const std::string &str, char d )
{
	std::vector<std::string> r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of( d );
	while( stop != std::string::npos )
	{
		r.push_back( str.substr( start, stop - start ) );

		start = stop + 1;
		stop = str.find_first_of( d, start );
	}

	r.push_back( str.substr( start ) );

	return r;
}


bool sort_function( const std::vector<std::string>& rval, const std::vector<std::string>& lval )
{
	try
	{
		if( string_to_int( rval.at( 0 ) ) >  string_to_int( lval.at( 0 ) ) )
			return true;
		else if( string_to_int( rval.at( 0 ) ) == string_to_int( lval.at( 0 ) ) )
		{
			if( string_to_int( rval.at( 1 ) ) >  string_to_int( lval.at( 1 ) ) )
				return true;
			else if( string_to_int( rval.at( 1 ) ) == string_to_int( lval.at( 1 ) ) )
			{
				if( string_to_int( rval.at( 2 ) ) >  string_to_int( lval.at( 2 ) ) )
					return true;
				else if( string_to_int( rval.at( 2 ) ) == string_to_int( lval.at( 2 ) ) )
				{
					if( string_to_int( rval.at( 3 ) ) >  string_to_int( lval.at( 3 ) ) )
						return true;
					else
						return false;
				}
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	catch( ... ) { return false; }
}


int main( int argc, char const *argv[] )
{

	using ip_addr_vec = std::vector<std::vector<std::string>>;

	try
	{
		ip_addr_vec ip_pool;
		ip_addr_vec ip_pool_out;

		for( std::string line; std::getline( std::cin, line );)
		{
			std::vector<std::string> v = split( line, '\t' );
			ip_pool.push_back( split( v.at( 0 ), '.' ) );
		}

		
		// reverse lexicographically sort 
		// (I think this is a great function for lambda expression )
		std::sort( ip_pool.begin(), ip_pool.end(), sort_function );

		// copy sorted vector to output vector
		ip_pool_out = ip_pool;

		// Create temp vector for all conditions
		ip_addr_vec ip_temp( ip_pool.size());

		// find all elements by condition
		auto it = std::copy_if( ip_pool.begin(), ip_pool.end(), ip_temp.begin(), [ & ]( const std::vector<std::string>& val )
		{
			try
			{
				if( string_to_int( val.at( 0 ) ) == 1 )
					return true;
				else if( ( string_to_int( val.at( 0 ) ) == 46 )
						 && ( string_to_int( val.at( 1 ) ) == 70 ) )
					return true;
				else if( ( string_to_int( val.at( 0 ) ) == 46 )
						 || ( string_to_int( val.at( 1 ) ) == 46 )
						 || ( string_to_int( val.at( 2 ) ) == 46 )
						 || ( string_to_int( val.at( 3 ) ) == 46 )
						 )
					return true;
				else
					return false;
			}
			catch( ... ) { return false; }
		} );
		ip_temp.resize( std::distance( ip_temp.begin(), it ) );
	
		// 1 condition first byte == 1
		ip_addr_vec ip_cond1( ip_temp.size() );
		auto it1 = std::copy_if( ip_temp.begin(), ip_temp.end(), ip_cond1.begin(), [ & ]( const std::vector<std::string>& val )
		{
			try
			{
				if( std::stoi( val.at( 0 ) ) == 1 )
					return true;
				else
					return false;
			}
			catch( ... ) { return false; }
		} );
		ip_cond1.resize( std::distance( ip_cond1.begin(), it1 ) );
		ip_pool_out.reserve( ip_pool_out.size() + ip_cond1.size() );
		ip_pool_out.insert( ip_pool_out.end(), ip_cond1.begin(), ip_cond1.end() );
		
		// 2 condition 46.70.*.*
		ip_addr_vec ip_cond2( ip_temp.size() );
		auto it2 = std::copy_if( ip_temp.begin(), ip_temp.end(), ip_cond2.begin(), [ & ]( const std::vector<std::string>& val )
		{
			try
			{
				if( ( std::stoi( val.at( 0 ) ) == 46 )
					&& ( std::stoi( val.at( 1 ) ) == 70 ) )
					return true;
				else
					return false;
			}
			catch( ... ) { return false; }
		} );
		ip_cond2.resize( std::distance( ip_cond2.begin(), it2 ) );
		ip_pool_out.reserve( ip_pool_out.size() + ip_cond2.size() );
		ip_pool_out.insert( ip_pool_out.end(), ip_cond2.begin(), ip_cond2.end() );

		// 3 condition  any byte = 46
		ip_addr_vec ip_cond3( ip_temp.size() );
		auto it3 = std::copy_if( ip_temp.begin(), ip_temp.end(), ip_cond3.begin(), [ & ]( const std::vector<std::string>& val )
		{
			try
		{
			if( ( std::stoi( val.at( 0 ) ) == 46 )
				|| ( std::stoi( val.at( 1 ) ) == 46 )
				|| ( std::stoi( val.at( 2 ) ) == 46 )
				|| ( std::stoi( val.at( 3 ) ) == 46 )
				)
				return true;
			else
				return false;
		}
		catch( ... ) { return false; }
		});
		ip_cond3.resize( std::distance( ip_cond3.begin(), it3 ) );
		ip_pool_out.reserve( ip_pool_out.size() + ip_cond3.size() );
		ip_pool_out.insert( ip_pool_out.end(), ip_cond3.begin(), ip_cond3.end() );

#ifdef SAVE_IN_FILE
		std::ofstream file( "ip_out.txt" );
		std::string s;
#endif

		for( ip_addr_vec::const_iterator ip = ip_pool_out.cbegin(); ip != ip_pool_out.cend(); ++ip )
		{
#ifdef SAVE_IN_FILE
			s = "";
#endif
			for( std::vector<std::string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part )
			{
				if( ip_part != ip->cbegin() )
				{
					std::cout << ".";
#ifdef SAVE_IN_FILE
					s.append( "." );
#endif
				}
				std::cout << *ip_part;
#ifdef SAVE_IN_FILE
				s.append( *ip_part );
#endif
			}
			std::cout << std::endl;
#ifdef SAVE_IN_FILE
			file << s;
			file << std::endl;
#endif
		}
#ifdef SAVE_IN_FILE
		file.close();
#endif



		// 222.173.235.246
		// 222.130.177.64
		// 222.82.198.61
		// ...
		// 1.70.44.170
		// 1.29.168.152
		// 1.1.234.8

		// TODO filter by first byte and output
		// ip = filter(1)

		// 1.231.69.33
		// 1.87.203.225
		// 1.70.44.170
		// 1.29.168.152
		// 1.1.234.8

		// TODO filter by first and second bytes and output
		// ip = filter(46, 70)

		// 46.70.225.39
		// 46.70.147.26
		// 46.70.113.73
		// 46.70.29.76

		// TODO filter by any byte and output
		// ip = filter_any(46)

		// 186.204.34.46
		// 186.46.222.194
		// 185.46.87.231
		// 185.46.86.132
		// 185.46.86.131
		// 185.46.86.131
		// 185.46.86.22
		// 185.46.85.204
		// 185.46.85.78
		// 68.46.218.208
		// 46.251.197.23
		// 46.223.254.56
		// 46.223.254.56
		// 46.182.19.219
		// 46.161.63.66
		// 46.161.61.51
		// 46.161.60.92
		// 46.161.60.35
		// 46.161.58.202
		// 46.161.56.241
		// 46.161.56.203
		// 46.161.56.174
		// 46.161.56.106
		// 46.161.56.106
		// 46.101.163.119
		// 46.101.127.145
		// 46.70.225.39
		// 46.70.147.26
		// 46.70.113.73
		// 46.70.29.76
		// 46.55.46.98
		// 46.49.43.85
		// 39.46.86.85
		// 5.189.203.46
	}
	catch( const std::exception &e )
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}


