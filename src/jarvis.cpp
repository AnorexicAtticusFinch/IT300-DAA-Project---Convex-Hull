#include <bits/stdc++.h> 
using namespace std; 
  
struct Point 
{ 
    int x, y; 
}; 
   
int rotation(Point p, Point q, Point i) 
{ 
    int val = (q.y - p.y) * (i.x - q.x) - (q.x - p.x) * (i.y - q.y); 
  
    if (val == 0) return 0;
    return (val > 0)? 1: 2; 
} 
  
void jarvis(Point points[], int n) 
{ 
    if (n < 3) return; 
  
    vector<Point> convexhull; 
  
    int first = 0; 
    for (int i = 1; i < n; i++) 
        if (points[i].x < points[first].x) 
            first = i; 
  
    int p = first, q; 
    do
    { 

        convexhull.push_back(points[p]);  
  
        q = (p+1)%n; 
        for (int i = 0; i < n; i++) 
        { 
           if (rotation(points[p], points[i], points[q]) == 2)
               q = i; 
        } 
        p = q; 
  
    } 
    while (p != first);
  
    for (int i = 0; i < convexhull.size(); i++) 
        cout << "(" << convexhull[i].x << ", "<< convexhull[i].y << ")\n"; 
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

	Point arr[n];
	for (int a = 0; a < n; a++)
	{
		myfile >> arr[a].x >> arr[a].y;
	}
	myfile.close();

	if (n < 3)
	{
		cout << "Invalid number of points" << endl;
		return 0;
	}

    jarvis(arr, n); 
}