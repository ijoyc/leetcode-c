
int maxProfit(int *prices, int pricesSize) {
  int profit = 0;
  int min = 0;
  for (int i = 1; i < pricesSize; i++) {
    if (prices[i] > prices[min]) {
      int current = prices[i] - prices[min];
      profit = profit > current ? profit : current;
    } else {
      min = i;
    }
  }
  return profit;
}