#include <iostream>
#include <math.h>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <functional>

using namespace std;

const int SIDE_SIZE = 3;

#define TARGET(i,j) ((SIDE_SIZE*i+j+1) % (SIDE_SIZE*SIDE_SIZE))

struct State;
typedef priority_queue<State*, vector<State*>, function<bool(State*, State*)>> CustomPQ;



int initial[SIDE_SIZE][SIDE_SIZE];

enum MoveType {
    MOVE_LEFT, MOVE_DOWN, MOVE_RIGHT, MOVE_UP
};

struct State {
    vector<MoveType> moves;
    int score;
    int xPos;

    int board[SIDE_SIZE][SIDE_SIZE];

    State(const State& other) {
        cout << "DEBUG: Fazendo copia" << endl;
        moves = other.moves;
        score = other.score;
        xPos = other.xPos;
        for (int i = 0; i < SIDE_SIZE; i++)
            for (int j = 0; j < SIDE_SIZE; j++)
                board[i][j] = other.board[i][j];
    }

    State(const int initial[SIDE_SIZE][SIDE_SIZE]) {
        copy_board(initial);
        calcScore();
    }

    State(const State* last_state, MoveType current_move) {
        if (last_state == nullptr) exit(200);
        copy_board(last_state->board);
        this->score = last_state->score;
        this->moves = last_state->moves;
        this->move(current_move);
    }

    vector<MoveType> getPossibleMoves() const {
        vector<MoveType> allowedMoves;
        if (xPos < SIDE_SIZE*2) allowedMoves.push_back(MOVE_DOWN);              //4
        if (xPos > SIDE_SIZE) allowedMoves.push_back(MOVE_UP);                  //3
        if (xPos % SIDE_SIZE != 0) allowedMoves.push_back(MOVE_LEFT);           //1
        if ( (xPos + 1) % SIDE_SIZE != 0) allowedMoves.push_back(MOVE_RIGHT);   //2
        return allowedMoves;
    }
    
    void printMoves() {
        for (auto &move : moves)
            cout << (move == MOVE_LEFT? 'l':
                    move == MOVE_RIGHT?'r':
                    move == MOVE_DOWN? 'd':'u');
        cout << endl;
    }

    bool operator<(const State& state) const {
        return this->score >= state.score;
    }

    long unsigned int calcHash() {
        int hash = 1;
        for (int i = 0; i < SIDE_SIZE*SIDE_SIZE; i++)
        {
            hash *= 10;
            hash += board[i/SIDE_SIZE][i%SIDE_SIZE];
        }
        return hash;
    }

private:
    void move(MoveType move) {
        moves.push_back(move);

        //TODO: remove debug if in possibleMoves
        vector<MoveType> possibleMoves = getPossibleMoves();
        if (find(possibleMoves.begin(), possibleMoves.end(), move) == possibleMoves.end()) {
            exit(222);
        }

        int pos1 = xPos, pos2;
        switch (move)
        {
            case MOVE_LEFT:
                pos2 = xPos-1;
            break;
            
            case MOVE_RIGHT:
                pos2 = xPos+1;
            break;

            case MOVE_UP:
                pos2 = xPos-SIDE_SIZE;
            break;

            case MOVE_DOWN:
                pos2 = xPos+SIDE_SIZE;
            break;
        
            default:
                pos2=-1;
                exit(156);
            return;
        }

        swap(pos1, pos2);
        calcScore();
    }

    void copy_board(const int otherboard[SIDE_SIZE][SIDE_SIZE]) {
        int tiles_qty = SIDE_SIZE*SIDE_SIZE;
        for (int i = 0; i < tiles_qty; i++){
            this->board[i/SIDE_SIZE][i%SIDE_SIZE] = otherboard[i/SIDE_SIZE][i%SIDE_SIZE];
            if (this->board[i/SIDE_SIZE][i%SIDE_SIZE] == 0) xPos = i;
        }
    }

    void swap(int pos1, int pos2) {
        static int tmp;
        tmp = board[pos1/SIDE_SIZE][pos1%SIDE_SIZE];
        board[pos1/SIDE_SIZE][pos1%SIDE_SIZE] = board[pos2/SIDE_SIZE][pos2%SIDE_SIZE];
        board[pos2/SIDE_SIZE][pos2%SIDE_SIZE] = tmp;
        if (pos1 == xPos) xPos = pos2;
        else if (pos2 == xPos) xPos = pos1;
    }

    // int heuristic() {
    //     int difference = 0;
    //     for (int i = 0; i < SIDE_SIZE; i++)
    //         for (int j = 0; j < SIDE_SIZE; j++)
    //             difference += abs(board[i][j] - (SIDE_SIZE*i+j+1) % (SIDE_SIZE*SIDE_SIZE));
    //     return difference;
    // }

    int heuristic() {
        int tile, shouldc, shouldl;
        int accum = 0;
        for (int i = 0; i < SIDE_SIZE; i++)
            for (int j = 0; j < SIDE_SIZE; j++) {
                tile = board[i][j];
                if (tile == 0)  {
                    shouldc = shouldl = SIDE_SIZE-1;
                } else {
                    shouldc = (tile-1) % SIDE_SIZE;
                    shouldl = (tile-1) / SIDE_SIZE;
                }

                accum += abs(shouldc-j) + abs(shouldl-i);
            }
        return accum;
    }


    void calcScore() {
        score = heuristic() + moves.size(); //Considerando o melhor caminho deu tle, e o enunciado não pede pelo melhor caminho
    }

    // void updateScore(int pos1, int pos2) {
    //     score -= abs(board[pos1/SIDE_SIZE][pos1%SIDE_SIZE] - TARGET(pos2/SIDE_SIZE,pos2%SIDE_SIZE));
    //     score -= abs(board[pos2/SIDE_SIZE][pos2%SIDE_SIZE] - TARGET(pos1/SIDE_SIZE,pos1%SIDE_SIZE));
    //     score += abs(board[pos1/SIDE_SIZE][pos1%SIDE_SIZE] - TARGET(pos1/SIDE_SIZE,pos1%SIDE_SIZE));
    //     score += abs(board[pos2/SIDE_SIZE][pos2%SIDE_SIZE] - TARGET(pos2/SIDE_SIZE,pos2%SIDE_SIZE));
    // }

};

int _get_tile(int pos) {
    char c = -1;
    cin >> c;
    return c == 'x'? 0: c - '0';
}

void input_puzzle() {
    int tiles_qty = SIDE_SIZE*SIDE_SIZE;
    for (int i = 0; i < tiles_qty; i++)
        initial[i/SIDE_SIZE][i%SIDE_SIZE] = _get_tile(i);
}


void exploreNeighbors(const State& currState, CustomPQ& pq, const unordered_set<long unsigned int>& forbidden_states) {
    auto possibleMoves = currState.getPossibleMoves();
    State *newState;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++) {
        newState = new State(&currState, *it);
        if (forbidden_states.find(newState->calcHash()) != forbidden_states.end()) {
            delete newState;
            continue;
        };

        pq.push(newState);
    }
}

bool compareStatePointer(const State* A, const State* B) {
    return *A < *B;
}

State *A_star() {
    unordered_set<long unsigned int> forbidden_states_hashes;

    CustomPQ neighbor_states(compareStatePointer);
    neighbor_states.push(new State(initial));

    while (!neighbor_states.empty())
    {
        State *state = neighbor_states.top();
        neighbor_states.pop();

        forbidden_states_hashes.insert(state->calcHash());

        exploreNeighbors(*state, neighbor_states, forbidden_states_hashes);

        //TODO: se der merda deve ser aqui
        if ((long unsigned int) state->score == state->moves.size())
            return state;
        else
            delete state;
    }
    
    return nullptr;
}   

bool isSolvable() {
    int inversions = 0;
    int total = SIDE_SIZE*SIDE_SIZE;
    for (int i = 0; i < total; i++)
    {
        for (int j = i+1; j < total; j++)
        {
            if (initial[i/SIDE_SIZE][i%SIDE_SIZE] == 0 || initial[j/SIDE_SIZE][j%SIDE_SIZE] == 0) continue;

            if (initial[i/SIDE_SIZE][i%SIDE_SIZE] > initial[j/SIDE_SIZE][j%SIDE_SIZE])
                inversions++;
        }
    }
    return inversions % 2 == 0;
}

void solve() {
    if (isSolvable()) {
        State *final_state = A_star();
        if (final_state != nullptr){
            final_state->printMoves();
            return;
        }
    }
    cout << "unsolvable" << endl;
} 

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        input_puzzle();
        solve();
        if (i + 1 < n)
            cout << endl;
    }
    

    return 0;
}
