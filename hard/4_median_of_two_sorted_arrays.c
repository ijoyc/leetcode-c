/*
* @Author: yizhuoc
* @Date:   2020-06-04 16:47:53
* @Last Modified by:   cyz
* @Last Modified time: 2020-06-04 16:49:02
*/

#include <stdio.h>
#include <limits.h>

static inline int Max(int a, int b) { return a > b ? a : b; }
static inline int Min(int a, int b) { return a < b ? a : b; }

/**
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

You may assume nums1 and nums2 cannot be both empty.
*/

// learn from solution
// O(log(min(m, n)))
double findMedianSortedArrays(int *nums1, 
  int nums1Size, 
  int *nums2, 
  int nums2Size) {
  // make sure nums1Size <= nums2Size because we will do binary search on the smaller array
  if (nums1Size > nums2Size) {
    return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
  }

  // i must start from zero, j start from length, to cope with two edge cases
  int i = 0;
  int j = nums1Size;
  int isOdd = (nums1Size + nums2Size) & 1;

  // binary search
  while (i <= j) {
    // partition two array such that each side contains same amount of number
    int nums1Left = (i + j) / 2;
    // if the total count of numbers is odd, make left side one more than right side by "+1"
    int nums2Left = (nums1Size + nums2Size + 1) / 2 - nums1Left;

    int nums1LeftMax = nums1Left == 0 ? INT_MIN : nums1[nums1Left - 1];
    int nums2LeftMax = nums2Left == 0 ? INT_MIN : nums2[nums2Left - 1];

    int nums1RightMin = nums1Left == nums1Size ? INT_MAX : nums1[nums1Left];
    int nums2RightMin = nums2Left == nums2Size ? INT_MAX : nums2[nums2Left];

    // cross comparing
    if (nums1LeftMax <= nums2RightMin && nums2LeftMax <= nums1RightMin) {
      if (isOdd) {
        // odd
        return Max(nums1LeftMax, nums2LeftMax);
      } else {
        // even
        return (Max(nums1LeftMax, nums2LeftMax) + Min(nums1RightMin, nums2RightMin)) / 2.0;
      }
    } else if (nums1LeftMax > nums2RightMin) {
      j = nums1Left - 1;
    } else {
      i = nums1Left + 1;
    }
  }

  return 0;
}