#include <bits/stdc++.h>
using namespace std;

pair<int, int> pt0;

pair<int, int> secondEle(stack<pair<int, int>> &st)
{
    pair<int, int> pt = st.top();
    st.pop();
    assert(!st.empty());
    pair<int, int> res = st.top();
    st.push(pt);
    return res;
}

int checkDirection(pair<int, int> p1, pair<int, int> p2, pair<int, int> p3)
{
    int val = (p2.second - p1.second) * (p3.first - p2.first) -
              (p2.first - p1.first) * (p3.second - p2.second);

    if (val == 0)
        return 0;

    return (val > 0) ? 1 : 2;
}

int distance(pair<int, int> pt1, pair<int, int> pt2)
{
    return (pt1.first - pt2.first) * (pt1.first - pt2.first) +
           (pt1.second - pt2.second) * (pt1.second - pt2.second);
}

double getSlope(pair<int, int> p1, pair<int, int> p2)
{
    double slope = (1.0 * (p2.second - p1.second)) / (1.0 * (p2.first - p1.first));
    return slope;
}

bool cmp(pair<int, int> x, pair<int, int> y)
{
    double slope1 = getSlope(pt0, x);
    double slope2 = getSlope(pt0, y);
    if (slope1 != slope2)
    {
        return slope1 < slope2;
    }
    return distance(pt0, y) >= distance(pt0, x);
}

pair<int, int> getBottommostPoint(vector<pair<int, int>> &arr, int n)
{
    int idx = 0;
    int val = arr[0].second;
    for (int i = 1; i < n; i++)
    {
        if ((arr[i].second < val) || (arr[i].second == val && arr[i].first < arr[idx].first))
        {
            idx = i;
            val = arr[i].second;
        }
    }
    pair<int, int> tmp = arr[0];
    arr[0] = arr[idx];
    arr[idx] = tmp;
    return arr[0];
}

vector<pair<int, int>> grahamScan(vector<pair<int, int>> arr, int n)
{
    vector<pair<int, int>> convex_hull;

    pt0 = getBottommostPoint(arr, n);

    sort(arr.begin() + 1, arr.end(), cmp);

    vector<pair<int, int>> pts;
    pts.push_back(pt0);

    for (int i = 1; i < n; i++)
    {
        while (i < n - 1 && getSlope(pt0, arr[i]) == getSlope(pt0, arr[i + 1]))
        {
            i++;
        }

        pts.push_back(arr[i]);
    }

    int sz = pts.size();

    if (sz < 3)
        return convex_hull;

    stack<pair<int, int>> st;
    st.push(pts[0]);
    st.push(pts[1]);
    st.push(pts[2]);

    for (int i = 3; i < sz; i++)
    {
        while (!st.empty() && checkDirection(secondEle(st), st.top(), pts[i]) != 2)
            st.pop();
        st.push(pts[i]);
    }
    while (!st.empty())
    {
        pair<int, int> p = st.top();
        convex_hull.push_back(p);
        st.pop();
    }
    return convex_hull;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
	{
		cout << "Please enter filename" << endl;
		return 0;
	}
    
    string filename = argv[argc - 1];
    ifstream myfile(filename);

    if (myfile.is_open())
    {
        int n;
        myfile >> n;

        vector<pair<int, int>> arr(n);
        for (int i = 0; i < n; i++)
        {
            int x, y;
            myfile >> x >> y;
            arr[i] = {x, y};
        }
        vector<pair<int, int>> conv_hull = grahamScan(arr, n);

        cout << "The points that make up the Convex Hull for this plane are: " << endl;
        for (int a = 0; a < conv_hull.size(); a++)
        {
            cout << a + 1 << ": (" << conv_hull[a].first << "," << conv_hull[a].second << ")" << endl;
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
}