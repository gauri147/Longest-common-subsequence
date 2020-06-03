/* Dynamic Programming C++ implementation of LCS problem */
/******************************************************************************
Reference: https://www.geeksforgeeks.org/printing-longest-common-subsequence/
Program to compute the longest common subsequence of two sequences
using elementary cost matrix method

Sample Input sequence 1 = 1,2,3,4,5
sample Input sequence 2 = 1,2,3,4,5,6

Input format:
5 (Length of sequence 1)
6 (Length of sequence 2)
1
2
3
4
5
-1
1
2
3
4
5
6
-1

*******************************************************************************/
#include <iostream>
#include <string>
#include <iterator> 
#include <ctime>
using namespace std;

int max(int a, int b);

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
void lcs(int* X, int* Y, int m, int n)
{
	int rows = m + 1; //Any Expression
	int cols = n + 1;
	int** L;
	L = new int* [rows];

	for (int i = 0; i < rows; ++i)
	{
		L[i] = new int[cols];
	}

	/* Following steps build L[m+1][n+1] in bottom up fashion. Note that L[i][j]
	contains length of LCS of X[0..i-1] and Y[0..j-1] */
	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			if (i == 0 || j == 0)
				L[i][j] = 0;

			else if (X[i - 1] == Y[j - 1])
				L[i][j] = L[i - 1][j - 1] + 1;

			else
				L[i][j] = max(L[i - 1][j], L[i][j - 1]);
		}
	}

	//To print LCS
	int index = *(*(L + m) + n);
	int lcsLength = index;
	//charcater array to store LCS
   // int LCS[index + 1];
	int* LCS = new int[index];
	// LCS[index] = '\0'; // Set the terminating character

	 //Stroing characters in LCS
	 //Start from the right bottom corner character
	int i = m, j = n;
	while (i > 0 && j > 0)
	{
		//if current character in s1 and s2 are same, then include this character in LCS[]
		if (X[i - 1] == Y[j - 1])
		{
			LCS[index - 1] = X[i - 1]; // Put current character in result
			i--; j--; index--;     // reduce values of i, j and index
		}
		// compare values of L[i-1][j] and L[i][j-1] and go in direction of greater value.
		else if (L[i - 1][j] > L[i][j - 1])
			i--;
		else
			j--;
	}

	//Print the lenght of the LCS
	cout << "Length of the Longest Subsequence is: " << *(*(L + m) + n) << endl;

	// Print the LCS
	cout << "Longest Subsequence: " << endl;
	for (int i = 0; i < lcsLength; ++i)
		cout << endl << *(LCS + i);
	cout << endl;
}

/* Utility function to get max of 2 integers */
int max(int a, int b)
{
	return (a > b) ? a : b;
}

// Driver Code 
int main()
{
	int l1;
	int l2;

	int input;
	cout << "Enter values for first and second vector seperated by -1." << endl;
	cout << "Add length of sequence 1 and 2 at the start" << endl;
	cin >> l1;
	cin >> l2;

	int* a1 = new int[l1];
	int* a2 = new int[l2];
	int i = 0, j = 0;
	while (cin >> input && input != -1 && i < l1) {
		a1[i] = input;
		i++;
	}
	while (cin >> input && input != -1 && j < l2) {
		a2[j] = input;
		j++;
	}
	clock_t c_start = std::clock();
	// your_algorithm
	lcs(a1, a2, l1, l2);
	clock_t c_end = std::clock();

	long double time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
	cout << "CPU time used: " << time_elapsed_ms << " ms\n";

	return 0;
}

