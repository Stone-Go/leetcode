/*

https://leetcode.com/problems/two-sum/

Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

 

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Output: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]
 

Constraints:

2 <= nums.length <= 10e4
-10e9 <= nums[i] <= 10e9
-10e9 <= target <= 10e9
Only one valid answer exists.
*/


// 1.C++ solution

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map<int, int> seen;
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (seen.find(nums[i]) != seen.end()) {
                return {seen[nums[i]], i};
            } else {
                seen.insert({target - nums[i], i});
            }
        }
        return {}; // error, not found
    }
};

// 2. C++ solution
class Solution {
public:
    using imap = map<int, int>;
    vector<int> twoSum(vector<int>& nums, int target) {
        imap im;
        for (int i = 0; i < nums.size(); ++i)
            im.insert(make_pair(nums[i], i));

        for (int i = 0; i < nums.size(); ++i) {
            auto it = im.find(target - nums[i]);
            if (it != im.end() && (it->second != i))
                return {i, it->second};
        }
        
        return {};
    }
};

// 3. C solution

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i;
    int* ret = (int*)malloc(sizeof(int) * 2);
    for (i = 0; i < numsSize; ++i) {
        int j;
        for (j = 0; j < numsSize; ++j) {
            if (i == j) continue;
            if (nums[i] + nums[j] == target) {
                ret[0] = j;
                ret[1] = i;
                break;
            }
        }
    }
    *returnSize = 2;
    return ret;
}


//4. c solution

struct number_hash {
  int value;
  int index;
  UT_hash_handle hh;
};

void destroy_table(struct number_hash** table) {
  struct number_hash* curr;
  struct number_hash* tmp;

  HASH_ITER(hh, *table, curr, tmp) {
    HASH_DEL(*table, curr);
    free(curr);
  }
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
  struct number_hash* table = NULL;
  struct number_hash* element;
  int* ret = (int*) malloc(2 * sizeof(int));
  int remaining;
  for (int i = 0; i < numsSize; ++i) {
    remaining = target - nums[i];

    // Find if there has already been an element such that the sum is target
    HASH_FIND_INT(table, &remaining, element);
    if (element) {
      ret[0] = element->index;
      ret[1] = i;
      break;
    }

    // Add the new number to the hash table if it doesn't exist already
    HASH_FIND_INT(table, &nums[i], element);
    if (!element) {
      element = (struct number_hash *) malloc(sizeof(*element));
      element->value = nums[i];
      element->index = i;

      HASH_ADD_INT(table, value, element);
    }
  }

  destroy_table(&table);

  *returnSize = 2;
  return ret;
}


//
//
// 5. c solution
//
//
void swap(int * const a, int * const b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

// Partition indexes that map to nums, without changing nums values or ordering
int partition_indexes(const int* const nums, int* const indexes, int lo, int hi) {
  int pivot = lo++;
  int pivot_val = nums[indexes[pivot]];
  int idx = pivot;
  int tmp;
  for (; lo < hi; ++lo) {
    if (nums[indexes[lo]] <= pivot_val) {
      swap(indexes + lo, indexes + ++idx);
    }
  }
 
  // Swapt the pivot (which is at the front) with the last value less or equal to the pivot
  swap(indexes + pivot, indexes + idx);
  
  return idx;
}

// Sort indexes that map to nums, without changing nums values or ordering
void sort_indexes(const int* const nums, int* const indexes, int lo, int hi) {
  if (lo < hi) {
    int pivot = partition_indexes(nums, indexes, lo, hi);
    sort_indexes(nums, indexes, lo, pivot);
    sort_indexes(nums, indexes, pivot + 1, hi);
  }
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
  int* ret = (int*)malloc(2 * sizeof(int));
  
  // Build index mapping to nums that is sorted assendingly
  int* indexes = (int *)malloc(numsSize * sizeof(int));
  for (int i = 0; i < numsSize; ++i) {
    indexes[i] = i;
  }
  sort_indexes(nums, indexes, 0, numsSize);

  // Move in from either side, if the pair is below target, then left index must increase
  // to increase the sum, while right must decrease if the sum is over
  int lo = 0;
  int hi = numsSize - 1;
  while (nums[indexes[lo]] + nums[indexes[hi]] != target) {
    if (nums[indexes[lo]] + nums[indexes[hi]] < target) {
      ++lo;
    } else {
      --hi;
    }
  }
  
  ret[0] = indexes[lo];
  ret[1] = indexes[hi];
  
  free(indexes);

  *returnSize = 2;
  return ret;
}

// 6. quick sort
void QuickSort(int A[], int I[], int lo, int hi)
{
    if (lo < hi)
    {
        int pivot = A[I[lo + (hi - lo) / 2]];
        int t;
        int i = lo - 1;
        int j = hi + 1;
        while (1)
        {
            while (A[I[++i]] < pivot);
            while (A[I[--j]] > pivot);
            if (i >= j)
                break;
            t = I[i];
            I[i] = I[j];
            I[j] = t;
        }
        QuickSort(A, I, lo, j);
        QuickSort(A, I, j + 1, hi);
    }
}


int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
  int* ret = (int*)malloc(2 * sizeof(int));
  
  // Build index mapping to nums that is sorted assendingly
  int* indexes = (int *)malloc(numsSize * sizeof(int));
  for (int i = 0; i < numsSize; ++i) {
    indexes[i] = i;
  }
  QuickSort(nums, indexes, 0, numsSize - 1);

  // Move in from either side, if the pair is below target, then left index must increase
  // to increase the sum, while right must decrease if the sum is over
  int lo = 0;
  int hi = numsSize - 1;
  while (nums[indexes[lo]] + nums[indexes[hi]] != target) {
    if (nums[indexes[lo]] + nums[indexes[hi]] < target) {
      ++lo;
    } else {
      --hi;
    }
  }
  
  ret[0] = indexes[lo];
  ret[1] = indexes[hi];
  
  free(indexes);

  *returnSize = 2;
  return ret;
}

