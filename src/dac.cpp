#include<bits/stdc++.h>
using namespace std;

pair<int, int> mid;

int get_quadrant(pair<int, int> point)
{
	if (point.first >= 0 && point.second >= 0)
	{
		return 1;
	}

	if (point.first <= 0 && point.second >= 0)
	{
		return 2;
	}

	if (point.first <= 0 && point.second <= 0)
	{
		return 3;
	}

	return 4;
}

bool compare(pair<int, int> point1, pair<int, int> point2)
{
	point1 = make_pair(point1.first - mid.first, point1.second - mid.second);
	point2 = make_pair(point2.first - mid.first, point2.second - mid.second);

	int quad1 = get_quadrant(point1);
	int quad2 = get_quadrant(point2);

	if (quad1 != quad2)
	{
		return (quad1 < quad2);
	}

	return ((point1.second * point2.first) < (point2.second * point1.first));
}

int crossing_line(pair<int, int> point1, pair<int, int> point2, pair<int, int> point3)
{
	int tmp = (point2.second - point1.second)*(point3.first - point2.first) - (point3.second - point2.second)*(point2.first - point1.first);

	if (tmp == 0)
	{
		return 0;
	}
	if (tmp > 0)
	{
		return 1;
	}
	return -1;
}

vector< pair<int, int> > get_convex_hull_base(vector< pair<int, int> > arr)
{
	set< pair<int, int> > pset;

	for (int a = 0; a < arr.size(); a++)
	{
		for (int b = a+1; b < arr.size(); b++)
		{
			int x1 = arr[a].first, x2 = arr[b].first;
			int y1 = arr[a].second, y2 = arr[b].second;

			int a1 = y1-y2;
			int b1 = x2-x1;
			int c1 = x1*y2 - y1*x2;

			int num_pos = 0, num_neg = 0;
			for (int c = 0; c < arr.size(); c++)
			{
				if ((a1*arr[c].first + b1*arr[c].second + c1) <= 0)
				{
					num_neg++;
				}

				if ((a1*arr[c].first + b1*arr[c].second + c1) >= 0)
				{
					num_pos++;
				}
			}

			if (num_pos == arr.size() || num_neg == arr.size())
			{
				pset.insert(arr[a]);
				pset.insert(arr[b]);
			}
		}
	}

	vector< pair<int, int> > ret;
	for (auto point : pset)
	{
		ret.push_back(point);
	}
	int n = ret.size();

	mid = make_pair(0, 0);
	for (int a = 0; a < n; a++)
	{
		mid.first += ret[a].first;
		mid.second += ret[a].second;
		ret[a].first *= n;
		ret[a].second *= n;
	}

	sort(ret.begin(), ret.end(), compare);
	for (int a = 0; a < n; a++)
	{
		ret[a] = make_pair(ret[a].first / n, ret[a].second / n);
	}

	return ret;
}

vector< pair<int, int> > merge_left_right(vector< pair<int, int> > left, vector< pair<int, int> > right)
{
	int nleft = left.size(), nright = right.size();

	int left_rightmost = 0;
	for (int a = 1; a < nleft; a++)
	{
		if (left[a].first > left[left_rightmost].first)
		{
			left_rightmost = a;
		}
	}

	int right_leftmost = 0;
	for (int a = 1; a < nright; a++)
	{
		if (right[a].first < right[right_leftmost].first)
		{
			right_leftmost = a;
		}
	}

	int ind_left = left_rightmost, ind_right = right_leftmost;
	bool quad = false;
	while (!quad)
	{
		quad = true;
		while (crossing_line(right[ind_right], left[ind_left], left[(ind_left + 1) % nleft]) >=0)
		{
			ind_left = (ind_left + 1) % nleft;
		}

		while (crossing_line(left[ind_left], right[ind_right], right[(nright + ind_right - 1) % nright]) <=0)
		{
			ind_right = (nright + ind_right - 1) % nright;
			quad = true;
		}
	}

	int upper_left = ind_left, upper_right = ind_right;
	ind_left = left_rightmost, ind_right = right_leftmost;
	quad = false;
	while (!quad)
	{
		quad = true;
		while (crossing_line(left[ind_left], right[ind_right], right[(ind_right + 1) % nright]) >= 0)
		{
			ind_right = (ind_right + 1) % nright;
		}

		while (crossing_line(right[ind_right], left[ind_left], left[(nleft + ind_left - 1) % nleft]) <= 0)
		{
			ind_left = (nleft + ind_left - 1) % nleft;
			quad = false;
		}
	}

	int lowera = ind_left, lowerb = ind_right;
	vector< pair<int, int> > ret;

	int ind = upper_left;
	ret.push_back(left[upper_left]);
	while (ind != lowera)
	{
		ind = (ind + 1) % nleft;
		ret.push_back(left[ind]);
	}

	ind = lowerb;
	ret.push_back(right[lowerb]);
	while (ind != upper_right)
	{
		ind = (ind + 1) % nright;
		ret.push_back(right[ind]);
	}

	return ret;
}

vector< pair<int, int> > get_convex_hull(vector< pair<int, int> > arr)
{
	if (arr.size() < 6)
	{
		return get_convex_hull_base(arr);
	}

	vector< pair<int, int> > left, right;
	for (int a = 0; a < arr.size()/2; a++)
	{
		left.push_back(arr[a]);
	}
	for (int a = arr.size()/2; a < arr.size(); a++)
	{
		right.push_back(arr[a]);
	}

	vector< pair<int, int> > left_ans = get_convex_hull(left);
	vector< pair<int, int> > right_ans = get_convex_hull(right);

	return merge_left_right(left_ans, right_ans);
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
	vector< pair<int, int> > conv_hull = get_convex_hull(arr);

	cout << "The points that make up the Convex Hull for this plane are: " << endl;
	for (int a = 0; a < conv_hull.size(); a++)
	{
	   cout << a+1 << ": " << conv_hull[a].first << " " << conv_hull[a].second << endl;
	}
}