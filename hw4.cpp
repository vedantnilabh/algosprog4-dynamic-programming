# include <vector>
# include <iostream>
# include "math.h"

using namespace std;
pair<vector<float>, vector<int>> WWWWW(vector<float> w, vector<float> p, int s, int t) {
    int j = w.size();
    vector<float> dp(j, 0);
    vector<int> quit_decision(j, 1);
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
        //cout << w[i+1] << " " << p[i+1] << " " << dp[i+1] << " " << w[min] << endl;
        dp[i] = fmax(dp[i+1] * p[i+1] + (1 - p[i+1]) * w[min], w[i]);
        //cout << dp[i] << endl;
        // if the expected value is eq1ual to the value of the question, we quit
        if (dp[i] == w[i]) {
            quit_decision[i] = 0;
        }
    }
    quit_decision[j-1] = 1;


    return make_pair(dp, quit_decision);
}







pair<vector<vector<float>>, vector<vector<int>>> WWWWW_1(vector<float> w, vector<float> p, int s, int t) {
    int j = w.size();
    vector<vector<float>> dp(2, vector<float>(j, 0));
    vector<vector<int>> quit_decision(2, vector<int>(j, 0));

    dp[0][j-1] = w[j-1];
    dp[1][j-1] = w[j-1];

    for (int i = j - 2; i >= 0; i--) {
        int min = 0;
        if (i + 1 > t) {
            min = t;
        } else if (i + 1 > s) {
            min = s;
        }

        //float p_get_easier = fmin(0.999f, 0.5f + p[i+1] / 2.0f);
        float p_get_easier = fmax(0.6f, p[i+1]);

        dp[0][i] = fmax(dp[0][i+1] * p[i+1] + (1 - p[i+1]) * w[min], w[i]);

        float no_lifeline = dp[1][i+1] * p[i+1] + (1 - p[i+1]) * w[min];
        float lifeline = dp[0][i+1] * p_get_easier + (1 - p_get_easier) * w[min];
        //cout << no_lifeline << " " << lifeline << endl;

        dp[1][i] = fmax(fmax(no_lifeline, lifeline), w[i]);

        quit_decision[0][i] = (dp[0][i] == w[i]) ? 0 : 1;
        quit_decision[1][i] = (dp[1][i] == w[i]) ? 0 : (dp[1][i] == no_lifeline) ? 1 : 2;
    }

    quit_decision[0][j-1] = 1;
    quit_decision[1][j-1] = 1;

    return make_pair(dp, quit_decision);
}


pair<vector<vector<float>>, vector<vector<int>>> WWWWW_2(vector<float> w, vector<float> p, int s, int t) {
    int j = w.size();
    vector<vector<float>> dp(4, vector<float>(j, 0));
    vector<vector<int>> quit_decision(4, vector<int>(j, 0));

    for (int k = 0; k < 4; k++) {
        dp[k][j-1] = w[j-1];
    }

    for (int i = j - 2; i >= 0; i--) {
        int min = 0;
        if (i + 1 > t) {
            min = t;
        } else if (i + 1 > s) {
            min = s;
        }

        float p_get_easier = fmin(0.999f, 0.5f + p[i+1] / 2.0f);

        // Case 0: No lifelines available
        dp[0][i] = fmax(dp[0][i+1] * p[i+1] + (1 - p[i+1]) * w[min], w[i]);

        // Case 1: "Get Easier" lifeline available
        float no_lifeline_case1 = dp[1][i+1] * p[i+1] + (1 - p[i+1]) * w[min];
        float lifeline_case1 = dp[0][i+1] * p_get_easier + (1 - p_get_easier) * w[min];
        dp[1][i] = fmax(fmax(no_lifeline_case1, lifeline_case1), w[i]);

        // Case 2: "Get Through" lifeline available
        float no_lifeline_case2 = dp[2][i+1] * p[i+1] + (1 - p[i+1]) * w[min];
        float lifeline_case2 = dp[0][i+1] * 1.0f - (i * 10);
        dp[2][i] = fmax(fmax(no_lifeline_case2, lifeline_case2), w[i]);

        // Case 3: Both lifelines available
        float no_lifeline_case3 = dp[3][i+1] * p[i+1] + (1 - p[i+1]) * w[min];
        float lifeline_case3_get_easier = dp[1][i+1] * p_get_easier + (1 - p_get_easier) * w[min];
        float lifeline_case3_get_through = dp[2][i+1] * 1.0f - (i * 10);
        dp[3][i] = fmax(fmax(fmax(no_lifeline_case3, lifeline_case3_get_easier), lifeline_case3_get_through), w[i]);

        quit_decision[0][i] = (dp[0][i] == w[i]) ? 1 : 0;
        quit_decision[1][i] = (dp[1][i] == w[i]) ? 0 : (dp[1][i] == no_lifeline_case1) ? 1 : 2;
        quit_decision[2][i] = (dp[2][i] == w[i]) ? 0 : (dp[2][i] == no_lifeline_case2) ? 1 : 2;

        if (dp[3][i] == w[i]) {
            quit_decision[3][i] = 0;
        } else if (dp[3][i] == no_lifeline_case3) {
            quit_decision[3][i] = 1;
        } else if (dp[3][i] == lifeline_case3_get_easier) {
            quit_decision[3][i] = 2;
        } else {
            quit_decision[3][i] = 3;
        }
    }

    quit_decision[0][j-1] = 0;
    quit_decision[1][j-1] = 0;
    quit_decision[2][j-1] = 0;
    quit_decision[3][j-1] = 0;

    return make_pair(dp, quit_decision);
}





 
