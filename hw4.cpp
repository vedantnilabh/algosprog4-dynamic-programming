# include <vector>
# include <iostream>
# include "math.h"

using namespace std;
pair<vector<float>, vector<int>> WWWWW(vector<float> w, vector<float> p, int s, int t) {
    int j = w.size();
    vector<float> dp(j, 0);
    vector<int> quit_decision(j, 0);
    // j is num questions + 1
    dp[j-1] = w[j-1];
    for (int i = j - 2; i >= 0; i--) {
        int min = 0;
        if(i+1 > t){
            min = t;
        }
        else if (i+1 > s){
            min = s;
        }
        // we are storing the expected value of the current question
        cout << w[i+1] << " " << p[i+1] << " " << dp[i+1] << " " << w[min] << endl;
        dp[i] = fmax(dp[i+1] * p[i+1] + (1 - p[i+1]) * w[min], w[i]);
        cout << dp[i] << endl;
        // if the expected value is eq1ual to the value of the question, we quit
        if (dp[i] == w[i]) {
            quit_decision[i] = 1;
        }
    }
    quit_decision[j-1] = 0;


    return make_pair(dp, quit_decision);
}







pair< vector< vector<float> > , vector< vector<int> > >  WWWWW_1(vector<float> w, vector<float> p, int s, int t)
{
    vector < vector<float> > fres;
    vector < vector<int> > fres2;

    vector <float> res0;
    vector <int> res1;

    res0.push_back(1.0);
    res0.push_back(2.0);
    res1.push_back(1);

    fres.push_back(res0);
    fres.push_back(res0);
    fres2.push_back(res1);
    fres2.push_back(res1);

    return make_pair(fres, fres2);
}

pair< vector< vector<float> > , vector< vector<int> > >  WWWWW_2(vector<float> w, vector<float> p, int s, int t)
{
    vector < vector<float> > fres;
    vector < vector<int> > fres2;

    vector <float> res0;
    vector <int> res1;

    res0.push_back(1.0);
    res0.push_back(2.0);
    res1.push_back(1);

    fres.push_back(res0);
    fres.push_back(res0);
    fres.push_back(res0);
    fres.push_back(res0);
    fres2.push_back(res1);
    fres2.push_back(res1);
    fres2.push_back(res1);
    fres2.push_back(res1);

    return make_pair(fres, fres2);
}

 
