#pragma once
#include <time.h>
#include <stdlib.h>


class Random {
	protected:
		static bool IsInited;
	public:
		Random() {
			if( !IsInited ) {
				srand( time(0) );
				IsInited = true;
			}
		}
		
		int get_random( int to ) {
			return get_random( 0, to );
		}
		
		int get_random(int from, int to) {
			int result = rand() % (to - from + 1) + from;
			return result;
		}
		
		
};

bool Random::IsInited = false;