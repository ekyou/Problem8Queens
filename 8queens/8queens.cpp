#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <set>
 
using namespace std;

const int SIZE = 8; // ������.
 
int board[SIZE][SIZE];
int results_count = 0; // ���������� �������.

set<int> sols; //���������
 
// ������� showBoard() - ���������� �����.
void showBoard()
{
    for(int i = 0; i < SIZE; ++i)
    {
        for(int j = 0; j < SIZE; ++j)
        {
            cout << ((board[i][j]) ? "Q " : ". ");
        }
        cout << endl;
    }
}

// ������� tryQueen() - ��������� ��� �� ��� ������������� ������,
// �� ���������, ����������.
bool tryQueen(int a, int b)
{
    for(int i = 0; i < a; ++i)
    {
        if(board[i][b])
        {
            return false;
        }
    }
    
    for(int i = 1; i <= a && b-i >= 0; ++i)
    {
        if(board[a-i][b-i])
        {
            return false;
        }
    }
    
    for(int i = 1; i <= a && b+i < SIZE; i++)
    {
        if(board[a-i][b+i])
        {
            return false;
        }
    }
}

//������� ���������� ���������
bool solution()
{
    int s[8][SIZE]; 
    for(int i = 0; i < SIZE; ++i)
    {
        for(int j = 0; j < SIZE; ++j)
        {
            if (board[i][j])
            {
                s[0][i] = j;
                break;
            }
        }
    }
    for(int i = 0; i < SIZE; ++i)
    {
        // ��������� ���� ���������.
        s[1][i] = SIZE-1-s[0][i];
        s[2][SIZE-1-i] = s[0][i];
        s[3][SIZE-1-i] = SIZE-1-s[0][i];
        s[4][s[0][i]] = i;
        s[5][s[0][i]] = SIZE-1-i;
        s[6][SIZE-1-s[0][i]] = i;
        s[7][SIZE-1-s[0][i]] = SIZE-1-i;
    }

    int S[8];
    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < SIZE; ++j)
        {
            S[i] = S[i] * SIZE + s[i][j];
        }
    }
    sort(S, S+8);
    auto res = sols.insert(S[0]);
    if (!res.second) return false;
    return true;
}
 
// ������� setQueen() - ������� ����� ���������� �������.
void setQueen(int a) 
{
    if(a == SIZE)
    {
        if (!solution()) return;
		showBoard();
		cout << "Result #" << ++results_count << endl << endl;
    }
    
    for(int i = 0; i < SIZE; ++i)
    {

		// ����� ���������, ��� ���� �������� � board[a][i] ����� (�������),
        // �� �� ����� ������������ � ���� ������, ������� � ����������.
        if(tryQueen(a, i))
        {
            board[a][i] = 1;
            setQueen(a+1);
            board[a][i] = 0;
        }
    }
    
    return; 
}
 
int main()
{
    setQueen(0);

    system("pause");
}