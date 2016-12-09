#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <ctime>

using namespace std;
int x, y;
bool MatSort(vector <double> & v, vector <double> & b){
	for (int i = 0; i < x; i++){
		if (!v[i] && !b[i])continue;
		if (!v[i])return 0;
		if (!b[i])return 1;
	}
	return 0;

}
void echelon(vector< vector<double> > &v){

	for (int i = 0; i <x; i++){
		for (int j = i + 1; j < x; j++){
			double m = v[j][i];
#pragma omp parallel
			{
			int sze = y/ omp_get_num_threads();
			int id = omp_get_thread_num();
			int start = id * sze;
			int end = start + sze;
			if (id == omp_get_num_threads()-1)end += v[j].size() % omp_get_num_threads();
			for (int q = start; q < end; q++){
				v[j][q] += (v[i][q] / v[i][i])* m * -1;
			}
		
		
		}
		}
	}
	
}

vector <double>  solve(vector< vector<double> > &v,bool & yes){
	vector <double> ans(x);
	for (int i = x - 1; i >= 0; i--)
	{
		ans[i] = v[i][x];
		for (int j = 0; j<y - 1; j++)
		if (j != i)
			ans[i] = ans[i] - v[i][j] * ans[j];
		if (v[i][i] == 0)
			yes = 1;
		ans[i] = ans[i] / v[i][i];
	}
	return  ans;

}
int main(){
	

	cout << "enter the matrix dimensions\n" ;
	scanf("%d%d", &x, &y);
	vector< vector<double> > v(x, vector<double>(y));
	cout << "enter the matrix elements\n";
	for (int i = 0; i < x; i++)
	for (int j = 0; j < y; j++)scanf("%lf", &v[i][j]);
	clock_t begin = clock();
	sort(v.begin(), v.end(), MatSort);
	
	echelon(v);
	bool yes=0;
	vector <double> ans(solve(v,yes));
	if (yes)
		puts("This Equation is inconsist");
	else
	{
		puts( "This Equation is consist");
		for (int i = 0; i<ans.size(); i++)
		{
			cout << "X" << i + 1 << " = " << ans[i] << endl;
		}
	}


	

	clock_t end = clock();
	printf("\nthe time to get answer =	%lf7 \n", double(end - begin) / CLOCKS_PER_SEC);
	
	return 0;
}