// #include <iostream>
// #include <vector>
// #include <utility>
// #include <algorithm>

// using std::vector;
// using std::pair;

// class solution {
// public:
//   vector<pair<int,int>> kSmallestPairs(const vector<int> & num1, const vector<int> & num2, int k) {
//     vector<pair<int,int>> path = fromToEnd(num1, num2, std::make_pair(0,0));
//     // vector<pair<int,int>> result(path.begin(), path.begin()+k);
//     // return result;
//     return path;
//   }

// private:
//   vector<pair<size_t,size_t>> getNext(const vector<int> & num1, const vector<int> & num2, const pair<size_t,size_t> & curr)
//   {
//     vector<pair<size_t,size_t>> next;
//     if (curr.first < num1.size()-1)
//       next.push_back(std::make_pair(curr.first+1, curr.second));
//     if (curr.second < num2.size()-1)
//       next.push_back(std::make_pair(curr.first, curr.second+1));
//     if (curr.first != curr.second && curr.second < num1.size() && curr.first < num2.size())
//       next.push_back(std::make_pair(curr.second, curr.first));
//     return next;
//   }

//   vector<pair<int,int>> fromToEnd(const vector<int> & num1, const vector<int> & num2, const pair<size_t,size_t> & curr) {
//     vector<pair<int,int>> path;
//     auto next = getNext(num1, num2, curr);
//     if (next.empty())
//       path.push_back(std::make_pair(num1[curr.first], num2[curr.second]));
//     else {
//       vector<int> sums;
//       for (auto nx : next)
// 	sums.push_back(num1[nx.first]+num2[nx.second]);

//       auto it = std::min_element(sums.begin(), sums.end());
//       auto nx = *(next.begin()+std::distance(sums.begin(),it));

//       auto temp = fromToEnd(num1, num2, nx);
//       temp.insert(temp.begin(), std::make_pair(num1[curr.first], num2[curr.second]));
//       path = temp;
//     }
//     return path;
//   }
// };


#include <iostream>
#include <vector>
#include <utility>
#include <set>

using std::vector;
using std::pair;

struct pairComp {
    bool operator()(const pair<int,int> & p1, const pair<int,int> & p2) {
        return p1.first+p1.second < p2.first+p2.second;
    }
};

class solution {
  public:
    vector<pair<int,int>> kSmallestPairs(const vector<int> & nums1, const vector<int> & nums2, int k) {
        std::multiset<pair<int,int>, pairComp> sorted;
        for (auto i1 : nums1)
            for (auto i2 : nums2)
                sorted.insert(std::make_pair(i1, i2));

        auto itend = sorted.begin();
        while (k-- > 0)
            itend++;
        vector<pair<int,int>> result(sorted.begin(), itend);
        return result;
    }
};

int main() {
  // vector<int> nums1{1,1,2}, nums2{1,2,3};
  // int k = 2;

    // vector<int> nums1{1,7,11}, nums2{2,4,6};
    // int k = 3;

    vector<int> nums1{1,2}, nums2{3};
    int k = 2;

  solution soln;
  auto pairs = soln.kSmallestPairs(nums1, nums2, k);
  for (auto pr : pairs)
    std::cout << "(" << pr.first << "," << pr.second << ")";
  std::cout << std::endl;
}
