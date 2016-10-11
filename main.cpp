#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using std::vector;
using std::pair;

class solution {
public:
  vector<pair<int,int>> kSmallestPairs(const vector<int> & num1, const vector<int> & num2, int k) {
    vector<pair<int,int>> path = fromToEnd(num1, num2, std::make_pair(0,0));
    // vector<pair<int,int>> result(path.begin(), path.begin()+k);
    // return result;
    return path;
  }

private:
  vector<pair<size_t,size_t>> getNext(const vector<int> & num1, const vector<int> & num2, const pair<size_t,size_t> & curr)
  {
    vector<pair<size_t,size_t>> next;
    if (curr.first < num1.size()-1)
      next.push_back(std::make_pair(curr.first+1, curr.second));
    if (curr.second < num2.size()-1)
      next.push_back(std::make_pair(curr.first, curr.second+1));
    if (curr.first != curr.second && curr.second < num1.size() && curr.first < num2.size())
      next.push_back(std::make_pair(curr.second, curr.first));
    return next;
  }

  vector<pair<int,int>> fromToEnd(const vector<int> & num1, const vector<int> & num2, const pair<size_t,size_t> & curr) {
    vector<pair<int,int>> path;
    auto next = getNext(num1, num2, curr);
    if (next.empty())
      path.push_back(std::make_pair(num1[curr.first], num2[curr.second]));
    else {
      vector<int> sums;
      for (auto nx : next)
	sums.push_back(num1[nx.first]+num2[nx.second]);

      auto it = std::min_element(sums.begin(), sums.end());
      auto nx = *(next.begin()+std::distance(sums.begin(),it));

      auto temp = fromToEnd(num1, num2, nx);
      temp.insert(temp.begin(), std::make_pair(num1[curr.first], num2[curr.second]));
      path = temp;
      
      // int sum1 = num1[next.front().first]+num2[next.front().second];
      // int sum2 = num1[next.back().first]+num2[next.back().second];
      // if (sum1 > sum2) {
      // 	auto temp = fromToEnd(num1, num2, next.front());
      // 	temp.insert(temp.begin(), std::make_pair(num1[curr.first], num2[curr.second]));
      // 	path = temp;
      // }
      // else {
      // 	auto temp = fromToEnd(num1, num2, next.back());
      // 	temp.insert(temp.begin(), std::make_pair(num1[curr.first], num2[curr.second]));
      // 	path = temp;
      // }
    }
    return path;
  }
};

int main() {
  vector<int> nums1{1,1,2}, nums2{1,2,3};
  int k = 2;

  solution soln;
  auto pairs = soln.kSmallestPairs(nums1, nums2, k);
  for (auto pr : pairs)
    std::cout << "(" << pr.first << "," << pr.second << ")";
  std::cout << std::endl;
}
