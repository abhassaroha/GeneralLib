#ifndef GENERALLIB_DFA_H
#define GENERALLIB_DFA_H

namespace algorithms {
	template<T, U>
		class DFA {
			DFA(const unordered_map<T*, int>&, const unordered_map<U*, int>&, int**, int, int);
		public:
			bool transition(const T&);
			int currentState();
			U* currentState();
		private:
			unordered_map<T*, int> mStateMap;
			unordered_map<U*, int> mInputsMap;
			int** mTransitionTable;
			int mRows;
			int mCols;
		}
}

#endif
