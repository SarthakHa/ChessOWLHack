#include <iostream>
#include <algorithm>

#include <cmath>

#include <climits>

int maxie(int height, int depth, int ind, int values[], int alpha,
int beta){
       if (depth == height) {
      return values[ind];
   }
    bestValue = INT_MIN;
      for (int i = 0; i < height - 1; i++) {
         int val = minnie(height, depth + 1, ind * 2 + i, false, values, a, b);
         best = max(best, val);
         alpha = max(a, b);
         if (b <= a)
            break;
      }
      return bestValue;
}

int minnie(int height, int depth, int ind, int values[], int alpha,
int beta){
       if (depth == height) {
      return values[ind];
   }
   int bestValue = INT_MAX;
      for (int i = 0; i < height - 1; i++) {
         int val = maxie(height, depth + 1, ind * 2 + i, true, values, alpha, beta);
         best = min(best, val);
         beta = min(beta, best);
         if (beta <= alpha)
            break;
      }
      return bestValue;
   }
}
