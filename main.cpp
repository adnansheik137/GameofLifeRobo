//AdnanSheikH1.cpp -- Final Project -- GA Robot
//Adnan Sheik -- CISP 400 -- 2022

#include <iostream>
#include <cstdlib>
using namespace std;

//Generates map
class genMap {
public:
    int map[10][10];
    void newMap();
    void mapPrint();
    int getValue(int i, int j);
    int changeValue(int i, int j, int k);

};

void genMap :: newMap(){
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            map[i][j] = 0;

        }
    }
    

    for (int i = 0; i < 40; i++){

        int validChoice = 0;
        while (validChoice == 0)
        {
            int column = rand() % 10;
            int row = rand() % 10;

            if (map[column][row] == 0){
                map[column][row] = 1;
                validChoice = 1;
            }
        }
    }
}

void genMap :: mapPrint(){
    cout << "\n   0 1 2 3 4 5 6 7 8 9" << endl;
	for (int i = 0; i < 10; i++)
    {   
        cout << i << "  ";
        for (int j = 0; j < 10; j++)
        {
            cout << map[i][j] << " ";
        }

        cout << endl;
    }
    cout << endl;
}


int genMap :: getValue(int i, int j){
    return map[i][j];
}

int genMap :: changeValue(int i, int j, int k){
    return map[i][j] = k;
}


//***********************************************************************************************************
//Generates genes for first generation of robots (200 bots)
class genBot {
public:
    int bots[200][16][5];
    void setGenes();
    void genPrint();
    void botPrint(int i);
    int getValue(int i, int j, int k);
    int changeValue(int i, int j, int k, int n);

};

void genBot :: setGenes(){
    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                bots[i][j][k] = rand() % 3;

            }
            bots[i][j][4] = rand() % 5;
        }
    }
}

void genBot :: genPrint(){
    for (int i = 0; i < 200; i++)
    {
        cout << "bot " << i + 1 << endl;
        for (int j = 0; j < 16; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                cout << bots[i][j][k] << " ";
            }

            cout << endl;
        }
        cout << endl;
    }
}

void genBot :: botPrint(int i){
    cout << "bot " << i + 1 << endl;
    for (int j = 0; j < 16; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            cout << bots[i][j][k] << " ";
        }

        cout << endl;
    }
    cout << endl;
}

int genBot :: getValue(int i, int j, int k){
    return bots[i][j][k];
}

int genBot :: changeValue(int i, int j, int k, int n){
    return bots[i][j][k] = n;
}




//***********************************************************************************************************

int main() {

    unsigned seed;
    seed = time(0);
    srand(seed);

    genMap map;

    genBot gen;
    gen.setGenes();

    int avgScores[6]; //GEN # CHANGE

    for (int p = 0; p < 6; p++) //GEN # CHANGE
    {
        int botScores[200][2];

        for (int i = 0; i < 200; i++)
        {
            map.newMap();

            int power = 5;
            int score = 0;
            int n = 0,
                s = 0,
                e = 0,
                w = 0;
            int m;

            int column = rand() % 10;
            int row = rand() % 10;


            while (power > 0)
            {
                if (row == 0){
                    n = 1;}
                if (row == 9){
                    s = 1;}
                if (column == 0){
                    w = 1;}
                if (column == 9){
                    e = 1;}

                if (map.getValue(row, column) == 1){
                    power = power + 5;
                    score = score + 5;}

                map.changeValue(row,column, 0);

                if (map.getValue(row - 1, column) == 1){
                    n = 2;}
                if (map.getValue(row + 1, column) == 1){
                    s = 2;}
                if (map.getValue(row, column + 1) == 1){
                    e = 2;}
                if (map.getValue(row, column - 1) == 1){
                    w = 2;}

                
                for (int j = 0; j < 16; j++)
                {
                    if (n == gen.getValue(i,j,0) and s == gen.getValue(i,j,1)and s == gen.getValue(i,j,2) and s == gen.getValue(i,j,3))
                    {
                    m = gen.getValue(i,j,4); 
                    }
                    else{
                        m = gen.getValue(i,15,4);}
                }

                if (m == 0) 
                {
                    m = rand() % 4 + 1;
                }

                if (m == 1 and row !=0) 
                {
                    row--;
                }
                else if (m == 2 and row !=9) 
                {
                    row++;
                }
                else if (m == 3 and column !=0) 
                {
                    column--;
                }
                else if (m == 4 and column !=0) 
                {
                    column++;
                }
                else 
                {
                    row = row + 0;
                    column = column + 0;
                }
                
                power--;
            }

            botScores[i][0] = score;
            botScores[i][1] = i; 
            cout << "Bot #"<< p <<"_"<< i+1 << " harvested " << score << " power." << endl;
        }
        cout << endl;

        //sorts 2d array based on power harvested while keeping bot #s attached to corresponding score
        qsort(botScores, 200, sizeof(*botScores),
        [](const void *botScoresg1, const void *botScoresg2)->int
        {
            int const *lhs = static_cast<int const*>(botScoresg1);
            int const *rhs = static_cast<int const*>(botScoresg2);
            return (lhs[0] < rhs[0]) ? -1
                :  ((rhs[0] < lhs[0]) ? 1
                :  (lhs[1] < rhs[1] ? -1
                :  ((rhs[1] < lhs[1] ? 1 : 0))));
        });


        //making new generation
        int tempGen[200][16][5];

        for (int i = 0; i < 100; i = i+2)
        {
            for (int j = 0; j < 8; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    tempGen[i][j][k] = gen.getValue(botScores[i+99][1],j,k);
                    tempGen[i+1][j][k] = gen.getValue(botScores[i+100][1],j,k);

                }
            }
            for (int j = 8; j < 16; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    tempGen[i][j][k] = gen.getValue(botScores[i+100][1],j,k);
                    tempGen[i+1][j][k] = gen.getValue(botScores[i+99][1],j,k);

                }
            }
        }

        for (int i = 100; i < 200; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    tempGen[i][j][k] = gen.getValue(botScores[i][1],j,k);
                }
            }
        }


        for (int i = 0; i < 200; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    gen.changeValue(i,j,k,tempGen[i][j][k]);
                }
            }
        }

        int totalPower = 0;
        for (int i = 0; i < 200; i++)
        {
            totalPower = totalPower + botScores[i][0];
        }

        avgScores[p] = (totalPower/200);

        


    }


    cout << "************************************" << endl << endl;

    for (int i = 0; i < 6; i++) //GEN # CHANGE
    {
        cout << "The average power for gen " << i << " was " << avgScores[i] << endl;
    }





    cout << "\nEND";
    return 0;
}