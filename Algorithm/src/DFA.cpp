#include "DFA.h"
namespace algorithms {
	template<T, U>
		DFA::DFA(const unordered_map<T*, int>& stateMap, const unordered_map<U*, int>& inputsMap 
				,int** transitionTable, int rows, int cols) {
			mStateMap = stateMap;
			mInputsMap = inputsMap;
			mTransitionTable = new int*[rows];
		}

	bool DFA::transition(const T&) {
	}
}

int main(int argc, char** argv) {
	using namespace algorithms;
	return 0;
}
