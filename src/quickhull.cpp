#include<bits/stdc++.h>
using namespace std;

void recursive_quickhull(vector<pair<int,int>> arr,pair<int,int> A,pair<int,int> B,int side,vector<pair<int,int>> &ans)
{
	int ind = -1;
	int distance = INT_MIN;
	for(int i=0;i<arr.size();i++)
	{
		pair<int,int> curr = arr[i];
		int curr_check = (curr.second-A.second)*(B.first-A.first) - (curr.first-A.first)*(B.second-A.second);
		int curr_distance = abs(curr_check);
		if(curr_check<0)
			curr_check = -1;
		else if(curr_check > 0)
			curr_check = 1;
		else
			curr_check = 0;		
		if(curr_check == side && curr_distance > distance)
		{
			distance = curr_distance;
			ind = i;
		}		
	}
	if(ind == -1)
	{
		bool flagA = false,flagB = false;
		for(int i=0;i<ans.size();i++)
		{
			if(ans[i] == A)
			{
				flagA = true;
			}
			if(ans[i] == B)
			{
				flagB = true;
			}
		}
		if(!flagA) 
			ans.push_back(A);
		if(!flagB)	
			ans.push_back(B);
		return;
	}
	int temp1 = (B.second-arr[ind].second)*(A.first - arr[ind].first) - (B.first-arr[ind].first)*(A.second-arr[ind].second);
	int temp2 = (A.second-arr[ind].second)*(B.first - arr[ind].first) - (A.first-arr[ind].first)*(B.second-arr[ind].second);
	if(temp1 < 0)
	{
		temp1 = 1;
	}
	else
	{
		temp1 = -1;
	}
	if(temp2 < 0)
	{
		temp2 = 1;
	}
	else
	{
		temp2 = -1;
	}
	recursive_quickhull(arr,arr[ind],A,temp1,ans);
	recursive_quickhull(arr,arr[ind],B,temp2,ans);
}

vector<pair<int,int> > get_convex_hull_quickhull(vector<pair<int,int> > arr)
{
	vector<pair<int,int> > ans;
	if(arr.size() < 3)
	{
		cout<< "Can't form convex hull for less than 3 elements\n";
		return ans;
	}
	int xmin=0,xmax=0;
	for(int i=0;i<arr.size();i++)
	{
		if(arr[i].first > arr[xmax].first )
			xmax = i;
		if(arr[i].first < arr[xmin].first )
			xmin = i;	
	}
	recursive_quickhull(arr,arr[xmin],arr[xmax],1,ans);
	recursive_quickhull(arr,arr[xmin],arr[xmax],-1,ans);
	return ans;
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		cout << "Please enter filename as command line argument" << endl;
		return 0;
	}
	
	string filename = argv[argc - 1];
    ifstream myfile(filename);
	if (!myfile.is_open())
    {
		cout << "Unable to open file" << endl;
		return 0;
	}

	int n;
	myfile >> n;

	vector< pair<int, int> > arr(n);
	for (int a = 0; a < n; a++)
	{
		myfile >> arr[a].first >> arr[a].second;
	}
	myfile.close();

	if (n < 3)
	{
		cout << "Invalid number of points" << endl;
		return 0;
	}

	sort(arr.begin(), arr.end());
	vector< pair<int, int> > conv_hull = get_convex_hull_quickhull(arr);

	cout << "The points that make up the Convex Hull for this plane are: " << endl;
	for (int a = 0; a < conv_hull.size(); a++)
	{
	   cout << a+1 << ": " << conv_hull[a].first << " " << conv_hull[a].second << endl;
	}
}