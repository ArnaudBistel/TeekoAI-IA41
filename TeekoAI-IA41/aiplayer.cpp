#include "aiplayer.h"

// todo changer les if id == 2 par un controle qui checke l'ia courante

AIPlayer::AIPlayer(QString name, int id, int difficulty )
    : Player(name, true, id), move(), difficulty(difficulty), pawn_to_move(-1), where_to_move_pawn(-1)
{
}

AIPlayer& AIPlayer::operator=(const AIPlayer& pl)
{
    if ( this == &pl)	return *this;
    this->id = pl.id;
    this->name 	= pl.name;
    this->ia    = pl.ia;
    this->move = pl.move;
    this->difficulty = pl.difficulty;

    return *this;
}


bool AIPlayer::operator== (AIPlayer &rhs)
{
    if (rhs.isIA() == this->isIA() &&
            rhs.getID() == this->getID() &&
            rhs.getName() == this->getName() &&
            rhs.move == this->move &&
            rhs.difficulty == this->difficulty
            )
        return true;
    return false;
}



int AIPlayer::getIAMove(int  board [5][5])
{
    this->findMove(board);
    return this->move;
}


int AIPlayer::getDifficulty()
{
    return this->difficulty;
}

void AIPlayer::findMove(int  board [5][5])
{
    // AI's pawns
    std::vector< int > pawns;
    int move(-1);

    // récupère la liste des index des pions de l'IA
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            if (board[i][j] == this->id)
            {
                pawns.push_back(i*5 + j);
            }
        }
    }

    // Difficulté facile
    if (this->difficulty == 1 )
    {
        // si l'IA a déjà placé ses 4 pions et qu'elle n'a pas encore choisi
        // quel pion elle va déplacer
        if (this->pionOnBoard() >= 4 && !this->chosePionToMove()) {
            int MAX = 3, MIN = 0;

            // choisi au hasard un pion à déplacer parmis ses 4 pions
            srand(time(NULL));
            move = (rand() % (MAX - MIN + 1)) + MIN;
            move = pawns[move];

        // si l'IA a déjà placé ses 4 pions et qu'elle a choisi
        // quel pion elle va déplacer
        } else if (this->pionOnBoard() >= 4 && this->chosePionToMove())
        {
            // cherche les déplacements possibles pour le pion qu'elle souhaite déplacer
            // qui se trouve dans previous_index
            pawns = this->computePossibleMoves(this->previous_index, board);
            int MAX = pawns.size() - 1;
            int MIN = 0;
            // choisi au hasard un déplacement parmis les déplacements possibles
            srand(time(NULL));
            move = (rand() % (MAX - MIN + 1)) + MIN;
            move = pawns[move];

        // si l'IA n'a pas encore placé ses 4 pions
        } else if (this->pionOnBoard() < 4) {
            int MAX = 24, MIN = 0;

            // Génération du nombre aléatoire
            srand(time(NULL));
            // choisi une case au hasard sur le plateau
            move = (rand() % (MAX - MIN + 1)) + MIN;

            // si la case est déjà occupée on en cherche une autre
            while (board[(int) move / 5][move % 5] != 0)
            {
                move = (rand() % (MAX - MIN + 1)) + MIN;
            }

//            std::cout << "move : " << move << std::endl;
        }
    }
    else{
        int bestValue, moveValue, bestIndex;
        bestValue = INT32_MIN;

        if (this->pionOnBoard()>=4){
            int bestPrevious;
            for(int i = 0 ; i<5 ; i++){
                for(int j =0; j < 5 ; j++){
                    if (board[i][j] == this->getID()){
                        for (int index : computePossibleMoves(i*5 + j, board)){
                            int new_board[5][5];
                            this->copyBoard(board,new_board);
                            new_board[i][j] = 0;
                            new_board[index/5][index%5] = this->getID();
                            moveValue = minMax(new_board,this->getDifficulty(), false,INT32_MIN,INT32_MAX);
                            if(moveValue > bestValue){
                                bestValue = moveValue;
                                bestIndex = index;
                                bestPrevious = i*5 + j;
                            }
                        }
                    }
                }
            }
            this->setChosePionToMove(true);
            this->setPreviousIndex(bestPrevious);
        }
        else{
            for(int i = 0 ; i<5 ; i++){
                for(int j =0; j < 5 ; j++){
                    if (board[i][j] == 0){
                        int new_board[5][5];
                        this->copyBoard(board,new_board);
                        new_board[i][j] = this->getID();
                        moveValue = minMax(new_board,this->getDifficulty(), false,INT32_MIN,INT32_MAX);

                        if(moveValue > bestValue){
                            bestValue = moveValue;
                            bestIndex = i*5 + j;
                        }
                    }
                }
            }
        }
        move = bestIndex;
    }

    this->move = move;
}


int AIPlayer::minMax(int (*board)[5], int depth, bool is_maximizing, int alpha, int beta){

    vector <int> ai, player;

    for(int i = 0 ; i<5 ; i++){
        for (int j = 0 ; j<5 ; j++){
            if(board[i][j] == this->id){
                ai.push_back(i*5  + j);
            }
            else if (board[i][j] != 0){
                player.push_back(i*5+j);
            }
        }
    }

    if(depth == 0 || checkWin(ai) == 1 || checkWin(player) == 1){
        return evaluateBoard(board);
    }

    if(is_maximizing){
        int bestValue = INT32_MIN;
        if(ai.size() < 4){
            for(int i = 0 ; i<5 ; i++){
                for(int j =0; j < 5 ; j++){
                    if (board[i][j] == 0){
                        int new_board[5][5];
                        this->copyBoard(board,new_board);
                        new_board[i][j] = this->getID();
                        bestValue = max(bestValue,minMax(new_board,depth-1, false,alpha,beta));
                        alpha = max(alpha,bestValue);
                        if(alpha >= beta)
                            return bestValue;

                    }
                }
            }
        }
        else{
            for(int i = 0 ; i<5 ; i++){
                for(int j =0; j < 5 ; j++){
                    if (board[i][j] == this->getID()){
                        for (int index : computePossibleMoves(i*5 + j, board)){
                            int new_board[5][5];
                            this->copyBoard(board,new_board);
                            new_board[i][j] = 0;
                            new_board[index/5][index%5] = this->getID();
                            bestValue = max(bestValue,minMax(new_board,depth-1, false,alpha,beta));
                            alpha = max(alpha,bestValue);
                            if(alpha >= beta)
                                return bestValue;
                        }
                    }
                }
            }
        }
        return bestValue;
    }
    else{
        int bestValue = INT32_MAX;
        int playerID = ((this->getID() == 1) ? 2 : 1);
        if(player.size() < 4){
            for(int i = 0 ; i<5 ; i++){
                for(int j =0; j < 5 ; j++){
                    if (board[i][j] == 0){
                        int new_board[5][5];
                        this->copyBoard(board,new_board);
                        new_board[i][j] = playerID;
                        bestValue = min(bestValue,minMax(new_board,depth-1, true,alpha,beta));
                        beta = min(beta,bestValue);
                        if(alpha >= beta)
                            return bestValue;

                    }
                }
            }
        }
        else{
            for(int i = 0 ; i<5 ; i++){
                for(int j =0; j < 5 ; j++){
                    if (board[i][j] == playerID){
                        for (int index : computePossibleMoves(i*5 + j, board)){
                            int new_board[5][5];
                            this->copyBoard(board,new_board);
                            new_board[i][j] = 0;
                            new_board[index/5][index%5] = playerID;
                            bestValue = min(bestValue,minMax(new_board,depth-1, true,alpha,beta));
                            beta = min(beta,bestValue);
                            if(alpha >= beta)
                                return bestValue;
                        }
                    }
                }
            }
        }
        return bestValue;
    }
}


int AIPlayer::evaluateBoard(int board[5][5]){
    int value;

    vector <int> ai, player;

    for(int i = 0 ; i<5 ; i++){
        for (int j = 0 ; j<5 ; j++){
            if(board[i][j] == this->id){
                ai.push_back(i*5  + j);
            }
            else if (board[i][j] != 0){
                player.push_back(i*5+j);
            }
        }
    }

    switch(this->getDifficulty()){
        case 2:
            value = 30*(checkWin(ai) - checkWin(player));
            value += 0.6*(checkPawnAlign(ai,board) - checkPawnAlign(player,board));
            value += checkPawnPotential(ai) - checkPawnPotential(player);
            break;
        case 3:
            value = 30*(checkWin(ai) - checkWin(player));
            value += 0.4*(checkPawnAlign(ai,board) - checkPawnAlign(player,board));
            value += 1.5*(checkPawnDistance(ai) - checkPawnDistance(player));
            value += 0.8*(checkPawnPotential(ai) - checkPawnPotential(player));

    }
    return value;
}


int AIPlayer::checkPawnDistance(vector<int> pawns){
    int value = 0;
        if(pawns.size() > 1){
            for(int i = 1 ; i < (int) pawns.size(); i++){
                value += (int) sqrt(std::pow((pawns[i] / 5) - (pawns[i-1] / 5),2 ) + std::pow((pawns[i] % 5) - (pawns[i-1] % 5),2));
            }
            value = (pawns.size() *5)/value;
        }

        return value;
}

int AIPlayer::checkPawnPotential(vector<int> pawns){

    vector <int> corner = {0,4,20,24}, sideMid = {2,10,14,22}, sideCorner = {1,3,5,9,15,19,21,23}, middleCorner = {6,7,8,11,13,16,17,18}; //Number of possible combinaisons : corner (4) sideMid (5) sideCorner(6) middleCorner(10) middle (12)

    int value = 0;
    if(pawns.size()>1){
        for(int i = 0 ; i< (int) pawns.size() ; i++){
            if (std::find(corner.begin(),corner.end(), pawns[i]) != corner.end()){
                value += 2;
            }
            else if (std::find(sideMid.begin(),sideMid.end(), pawns[i]) != sideMid.end()){
                value += 4;
            }
            else if (std::find(sideCorner.begin(),sideCorner.end(), pawns[i]) != sideCorner.end()){
                value += 7;
            }
            else if (std::find(middleCorner.begin(),middleCorner.end(), pawns[i]) != middleCorner.end()){
                value += 11;
            }
            else{
                value += 16;
            }
        }
        value /= pawns.size();
    }
    return value;
}

int AIPlayer::checkPawnAlign(vector<int> pawns, int board[5][5]){
    int value = 0;
    if(pawns.size() > 0){
        vector <vector <int>> sub;
        createSubSequences(sub, pawns);
        int maxSquare = 0, maxLine = 0, maxCol = 0, maxLDiag = 0, maxRDiag = 0;
        for (int i = 0 ; i < (int) sub.size() ; i++){
            if(isValidSquare(sub[i]) && canMakeSquare(sub[i],board)){
                maxSquare = max(maxSquare,(int) pow(sub[i].size(),2));
            }
            if(isValidLine(sub[i]) && canMakeLine(sub[i],board)){
                maxLine = max(maxLine,(int) pow(sub[i].size(),2));
            }
            if(isValidColumn(sub[i]) && canMakeCol(sub[i],board)){
                maxCol = max(maxCol,(int) pow(sub[i].size(),2));
            }
            if(isValidDiag(sub[i],true) && canMakeRDiag(sub[i],board)){
                maxRDiag = max(maxRDiag,(int) pow(sub[i].size(),2));
            }
            if(isValidDiag(sub[i], false) && canMakeLDiag(sub[i],board)){
                maxLDiag = max(maxLDiag,(int) pow(sub[i].size(),2));
            }
        }
        value = maxSquare + maxCol + maxLDiag + maxLine + maxRDiag;
    }
    return value;
}


bool AIPlayer::isValidSquare(vector<int> pawns){
    bool valid = false;
    if(pawns.size() == 1){
        valid = true;
    }
    else if (pawns.size() == 2){ //Any linked line, column or diag is a 2 pawns square
        if (pawns[0] + 1 == pawns[1] && pawns[1] %5 != 0){
            valid = true;
        }
        else if (pawns[0] + 5 == pawns[1]){
            valid = true;
        }
        else if (pawns[0] + 6 == pawns[1] && pawns[1] %5 != 0){
            valid = true;
        }
        else if (pawns[0] + 4 == pawns[1] && pawns[1] % 5 != 4){
            valid = true;
        }
    }
    else if (pawns.size() == 3){ //3 pawns square forms a L shape
        if (pawns[0] + 1 == pawns[1] && pawns[1] %5 != 0){
            if(pawns[2] == pawns[0] + 5 || pawns[2] == pawns[0] + 6){
                valid = true;
            }
        }
        else if (pawns[1] + 1 == pawns[2] && pawns[2] %5 != 0){
            if(pawns[0] == pawns[1] - 5 || pawns[0] == pawns[1] - 4){
                valid = true;
            }
        }
    }
    else{
        if (pawns[0] / 5 != 4 && pawns[0] % 5 != 4 && pawns[1] == pawns[0] + 1 && pawns[2] == pawns[0] + 5 && pawns[3] == pawns[0] + 6){
            valid = true;
        }
    }
    return valid;
}

bool AIPlayer::isValidColumn(vector<int> pawns){
    bool valid = false;
    if(pawns.size() == 1){
        valid = true;
    }
    else{
        for(int i = 1 ; i< (int) pawns.size() ; i++){
            if(pawns[i] % 5 == pawns[i-1] % 5 && pawns[pawns.size() -1 ] - pawns[0] < 16 ){
                valid = true;
            }
            else{
                valid = false;
                i=4;
            }
        }
    }
    return valid;
}

bool AIPlayer::isValidLine(vector<int> pawns){
    bool valid = false;

    if(pawns.size() == 1){
        valid = true;
    }
    else{
        for(int i = 1 ; i< (int) pawns.size() ; i++){
            if(pawns[i] / 5 == pawns[i-1] / 5 && pawns[pawns.size() -1 ] - pawns[0] < 4 ){
                valid = true;
            }
            else{
                valid = false;
                i=4;
            }
        }
    }
    return valid;
}

bool AIPlayer::isValidDiag(vector<int> pawns, bool right){

    bool valid = false;
    vector <int> possible_r = {0,1,5,6,7,11,12,13,17,18,19,23,24}, possible_l = {3,4,7,8,9,11,12,13,15,16,17,20,21};

    if(right){
        if(std::find(possible_r.begin(),possible_r.end(),pawns[0]) != possible_r.end()){
            if(pawns.size() == 1){
                valid = true;
            }
            else{
                for(int i = 1; i<(int)pawns.size();i++){
                    if ((pawns[i] - pawns[i-1]) % 6 == 0 && pawns[i]%5 >= i){
                        valid = true;
                    }
                    else{
                        valid = false;
                        i=4;
                    }
                }
            }
        }

    }
    else{
        if(std::find(possible_l.begin(),possible_l.end(),pawns[0]) != possible_l.end()){
            if(pawns.size() == 1){
                valid = true;
            }
            else{
                for(int i = 1; i<(int)pawns.size();i++){
                    if ((pawns[i] - pawns[i-1]) % 4 == 0 && pawns[i]%5 <= (4-i)){
                        valid = true;
                    }
                    else{
                        valid = false;
                        i = 4;
                    }
                }
            }
        }

    }
    return valid;
}

bool AIPlayer::canMakeSquare(vector<int> pawns, int board[5][5]){
    bool result = false;
    int x,row,col,thisId,otherId;
    x = pawns[0];
    row = x / 5;
    col = x%5;
    thisId = board[row][col];
    otherId = (thisId == 1) ? 2 : 1;
    if(pawns.size() == 1){

        if(row > 0 && col > 0){
            if(board[row-1][col-1] != otherId && board[row-1][col] != otherId && board[row][col-1] != otherId)
                result = true;
        }
        if(row > 0 && col < 4){
            if(board[row-1][col+1] != otherId && board[row-1][col] != otherId && board[row][col+1] != otherId)
                result = true;
        }
        if(row < 4 && col < 4){
            if(board[row+1][col+1] != otherId && board[row+1][col] != otherId && board[row][col+1] != otherId)
                result = true;
        }
        if(row < 4 && col > 0){
            if(board[row+1][col-1] != otherId && board[row+1][col] != otherId && board[row][col-1] != otherId)
                result = true;
        }
    }
    else if (pawns.size() == 2){
        if(pawns[1] == x +1){
            if(row > 0 && board[row-1][col] != otherId && board[row-1][col+1] != otherId)
                result = true;
            if(row < 4 && board[row+1][col] != otherId && board[row+1][col+1] != otherId)
                result = true;
        }
        else if(pawns[1] == x +4){
            if(board[row+1][col] != otherId && board[row][col-1] != otherId)
                result = true;
        }
        else if(pawns[1] == x +5){
            if(col > 0 && board[row][col-1] != otherId && board[row+1][col-1] != otherId)
                result = true;
            if(col < 4 && board[row][col+1] != otherId && board[row+1][col+1] != otherId)
                result = true;
        }
        else if(pawns[1] == x +6){
            if(board[row+1][col] != otherId && board[row][col+1] != otherId)
                result = true;
        }
    }
    else if (pawns.size() == 3){
        if(pawns[2] == x +5){
            if(pawns[1] == x+1 && board[row+1][col+1] != otherId)
                result = true;
            if(pawns[1] == x+4 && board[row][col-1] != otherId)
                result = true;
        }
        else{
            if(pawns[1] == x+1 && board[row+1][col] != otherId)
                result = true;
            if(pawns[1] == x+5 && board[row][col+1] != otherId)
                result = true;
        }
    }
    else{
        result = true;
    }
    return result;
}

bool AIPlayer::canMakeLine(vector<int> pawns, int board[5][5]){
    bool result = false;
    int x,row,col,thisId,otherId;
    x = pawns[0];
    row = x / 5;
    col = x%5;
    thisId = board[row][col];
    otherId = (thisId == 1) ? 2 : 1;
    if(board[row][1] != otherId && board[row][2] != otherId && board[row][3] != otherId){
        if(board[row][0] != otherId || board[row][4] != otherId)
            result = true;
    }
    return result;
}
bool AIPlayer::canMakeCol(vector<int> pawns, int board[5][5]){
    bool result = false;
    int x,row,col,thisId,otherId;
    x = pawns[0];
    row = x / 5;
    col = x%5;
    thisId = board[row][col];
    otherId = (thisId == 1) ? 2 : 1;
    if(board[1][col] != otherId && board[2][col] != otherId && board[3][col] != otherId){
        if(board[0][col] != otherId || board[4][col] != otherId)
            result = true;
    }
    return result;
}
bool AIPlayer::canMakeRDiag(vector<int> pawns, int board[5][5]){
    bool result = false;
    int x,row,col,thisId,otherId;
    x = pawns[0];
    row = x / 5;
    col = x%5;
    thisId = board[row][col];
    otherId = (thisId == 1) ? 2 : 1;
    if(row == col){
        if(board[1][1] != otherId && board[2][2] != otherId && board[3][3] != otherId){
            if(board[0][0] != otherId || board[4][4] != otherId)
                result = true;
        }
    }
    else{
        while(row > 0 && col > 0){
            row--;
            col--;
        }
        for(int i = 0;i<4;i++){
            if (board[row][col] != otherId){
                result = true;
            }
            else{
                result = false;
                i=4;
            }
            row++;
            col++;
        }
    }
    return result;
}
bool AIPlayer::canMakeLDiag(vector<int> pawns, int board[5][5]){
    bool result = false;
    int x,row,col,thisId,otherId;
    x = pawns[0];
    row = x / 5;
    col = x%5;
    thisId = board[row][col];
    otherId = (thisId == 1) ? 2 : 1;
    if(row + col == 4){
        if(board[1][3] != otherId && board[2][2] != otherId && board[3][1] != otherId){
            if(board[0][4] != otherId || board[4][0] != otherId)
                result = true;
        }
    }
    else{
        while(row > 0 && col <4){
            row--;
            col++;
        }
        for(int i = 0;i<4;i++){
            if (board[row][col] != otherId){
                result = true;
            }
            else{
                result = false;
                i=4;
            }
            row++;
            col--;
        }
    }
    return result;
}



int AIPlayer::checkWin(vector <int> pawns ){
    int won, lineCount = 1, columnCount = 1, diag_rCount = 1, diag_lCount = 1, squareCount = 1;
    if(pawns.size() < 4){
        won = 0;
    }
    else{
        int pawn = pawns[0];
        for(int i = 1 ; i<4 ; i++ ){
            if (pawns[i] == pawn + 1 && pawns[2] == pawns[0] + 5 && pawns[0] % 5 < 4 && pawns[0] < 20){
                if(i == 2){
                    pawn = pawns[i];
                }
                else{
                    pawn +=4;
                }
                squareCount++;
            }
            else if(pawns[i] == pawn +1 && pawns[0]%5 <2){
                pawn = pawns[i];
                lineCount++;
            }
            else if (pawns[i] == pawn +5 && pawns[0] < 10){
                pawn = pawns[i];
                columnCount++;
            }
            else if(pawns[i] == pawn + 6 && pawns[0] % 5 < 2 && pawns[0] <7){
                pawn = pawns[i];
                diag_rCount++;
            }
            else if (pawns[i] == pawn + 4 && pawns[0] % 5 > 2 && pawns[0] < 10){
                pawn = pawns[i];
                diag_lCount++;
            }

        }
        if(lineCount == 4 || columnCount == 4 || diag_lCount == 4 || diag_rCount == 4 || squareCount == 4)
            won = 1;
        else
            won = 0;
    }
    return won;
}

// retourne un vecteur contenant les index des déplacements possibles pour le
// pion dont l'index est passé en paramètre
// Donc l'ensemble des cases adjacentes qui ne sont pas déjà occupées
std::vector<int> AIPlayer::computePossibleMoves(int index, int  board [5][5])
{
//    std::cout << "AIPlayer::computePossibleMoves : " << std::endl;
    int line = (int) index / 5;
    int col = index % 5;
    std::vector< int > pawns;

    // évaluation des choix possibles
    int i, j = 0;

    if (line - 1 >= 0 && col - 1 >= 0 )
    {
        i = line - 1;
        j = col - 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        }
    }

    if (line - 1 >= 0)
    {
        i = line - 1;
        j = col;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        }
    }

    if (line - 1 >= 0 && col + 1 <= 4)
    {
        i = line - 1;
        j = col + 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        }
    }

    if (col + 1 <= 4)
    {
        i = line;
        j = col + 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        }
    }

    if (line + 1 <= 4 && col + 1 <= 4 )
    {
        i = line + 1;
        j = col + 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        }
    }

    if (line + 1 <= 4)
    {
        i = line + 1;
        j = col;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        }
    }

    if (line + 1 <= 4 && col - 1 >= 0)
    {
        i = line + 1;
        j = col - 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        }
    }

    if (col - 1 >= 0)
    {
        i = line;
        j = col - 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        }
    }

    return pawns;
}




// retourne un vecteur contenant les index des déplacements possibles pour le
// pion dont l'index est passé en paramètre
// Donc l'ensemble des cases adjacentes qui ne sont pas déjà occupées
std::vector<int> AIPlayer::computeSquaresAroundSquare(int index, int  board [5][5])
{
//    std::cout << "AIPlayer::computeSquaresAroundSquare : " << std::endl;
    int line = (int) index / 5;
    int col = index % 5;
    std::vector< int > pawns;

    // évaluation des choix possibles
    int i, j = 0;

    if (line - 1 >= 0 && col - 1 >= 0 )
    {
        i = line - 1;
        j = col - 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        } else {
            pawns.push_back(-1);
        }
    } else {
        pawns.push_back(-1);
    }

    if (line - 1 >= 0)
    {
        i = line - 1;
        j = col;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        } else {
            pawns.push_back(-1);
        }
    } else {
        pawns.push_back(-1);
    }

    if (line - 1 >= 0 && col + 1 <= 4)
    {
        i = line - 1;
        j = col + 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        } else {
            pawns.push_back(-1);
        }
    } else {
        pawns.push_back(-1);
    }

    if (col + 1 <= 4)
    {
        i = line;
        j = col + 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        } else {
            pawns.push_back(-1);
        }
    } else {
        pawns.push_back(-1);
    }

    if (line + 1 <= 4 && col + 1 <= 4 )
    {
        i = line + 1;
        j = col + 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        } else {
            pawns.push_back(-1);
        }
    } else {
        pawns.push_back(-1);
    }

    if (line + 1 <= 4)
    {
        i = line + 1;
        j = col;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        } else {
            pawns.push_back(-1);
        }
    } else {
        pawns.push_back(-1);
    }

    if (line + 1 <= 4 && col - 1 >= 0)
    {
        i = line + 1;
        j = col - 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        } else {
            pawns.push_back(-1);
        }
    } else {
        pawns.push_back(-1);
    }

    if (col - 1 >= 0)
    {
        i = line;
        j = col - 1;
        if (board[i][j] == 0 )
        {
            pawns.push_back(i*5 + j);
        } else {
            pawns.push_back(-1);
        }
    } else {
        pawns.push_back(-1);
    }

    return pawns;
}


void AIPlayer::createSubSequences(vector<vector<int>> &sub, vector<int> vec){
    int n = vec.size();
        int num = pow(2,n);
        for (int i = 0; i< num ; i++){
            vector <int> tmp;
            for (int j = 0;j<n;j++){
                if (((i>>j) & 1) == 1){
                   tmp.push_back(vec[j]);
                }
            }
            if (tmp.size() != 0)
                sub.push_back(tmp);
        }
}


void AIPlayer::copyBoard(int board [5][5], int new_board [5][5])
{
//    std::cout << "AIPlayer::copyBoard : " << std::endl;
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            new_board[i][j] = board[i][j];
        }
    }
}

void AIPlayer::printBoard(int b [5][5])
{
    for(int i=0; i<5; i++)
    {
            for(int j=0; j<5; j++)
            {
                    std::cout<<" "<<b[i][j]<<" ";
            }
            std::cout<<"\n";
    }

}
