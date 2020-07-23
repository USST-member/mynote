# Leetcode(力扣)题解--C++实现(一)

[TOC]



## 题目 1 [平方数之和](https://leetcode-cn.com/problems/sum-of-square-numbers/)

给定一个非负整数 c ，你要判断是否存在两个整数 a 和 b，使得 a2 + b2 = c。

示例1:

输入: 5
输出: True
解释: 1 * 1 + 2 * 2 = 5

 

示例2:

输入: 3
输出: False

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sum-of-square-numbers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
class Solution {
public:
    bool judgeSquareSum(int c) 
    {
        unsigned int sqr=sqrt(c);
        unsigned int i=0,j=sqr;
        while(i<=j)
        {
            if((i*i+j*j)==c)
                return true;
            if((i*i+j*j)>c)
                j--;
            else
                i++;
        }
        return false;
    }
};
```

## 题目 2 [两数之和 II - 输入有序数组](https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/)

给定一个已按照升序排列 的有序数组，找到两个数使得它们相加之和等于目标数。

函数应该返回这两个下标值 index1 和 index2，其中 index1 必须小于 index2。

说明:

    返回的下标值（index1 和 index2）不是从零开始的。
    你可以假设每个输入只对应唯一的答案，而且你不可以重复使用相同的元素。

示例:

输入: numbers = [2, 7, 11, 15], target = 9
输出: [1,2]
解释: 2 与 7 之和等于目标数 9 。因此 index1 = 1, index2 = 2 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target)
    {
        vector<int> twoSum;
        int i=0,j=numbers.size()-1;
        while(i<j)
        {
            if((numbers.at(i)+numbers.at(j))==target)
            {
                twoSum.push_back(i+1);
                twoSum.push_back(j+1);
                return twoSum;
            }
            if (numbers[i] + numbers[j] > target) 
                j--;
            else
                i++;
        }
        return {}; 
    }
};
```

## 题目 3 [反转字符串中的元音字母](https://leetcode-cn.com/problems/reverse-vowels-of-a-string/)

编写一个函数，以字符串作为输入，反转该字符串中的元音字母。

示例 1:

输入: "hello"
输出: "holle"

示例 2:

输入: "leetcode"
输出: "leotcede"

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-vowels-of-a-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
class Solution {
public:
    string reverseVowels(string s) 
    {
        int i=0,j=s.size()-1;
        int i_flag=0,j_flag=0;
        while(i<j)
        {
            if(is_have_char( s.at(i) )  )
            {
                i_flag=1;
            }
            else
                i++;
            if(is_have_char(s.at(j)))
            {
                j_flag=1;
            }
            else
                j--;
            if(i_flag==1&&j_flag==1)
            {
                swap(s.at(i),s.at(j));
                i_flag=0;
                j_flag=0;
                i++;
                j--;
            }
        }
        return s;
    }
    bool is_have_char(char c)
    {
        						if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||c=='A'||c=='E'||c=='I'||c=='O'||c=='U')
            return true;
        else
            return false;
    }
};
```

## 题目 4 [验证回文字符串 Ⅱ](https://leetcode-cn.com/problems/valid-palindrome-ii/)

给定一个非空字符串 s，最多删除一个字符。判断是否能成为回文字符串。

示例 1:

输入: "aba"
输出: True

示例 2:

输入: "abca"
输出: True
解释: 你可以删除c字符。

注意:

    字符串只包含从 a-z 的小写字母。字符串的最大长度是50000。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/valid-palindrome-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
class Solution {
public:
    bool validPalindrome(string s) 
    {
        int i=0,j=s.size()-1;
        bool x=true,t=true;
        while(i<j)
        {
            if(s.at(i)==s.at(j))
            {
                i++;
                j--;
            }
            else
            {
                x=is_true(s,i+1,j);
                t=is_true(s,i,j-1);
                break;
            }
        }
        if(x==true||t==true)
            return true;
        else
            return false;
    }
    bool is_true(string s,int i,int j)
	{
        while(i<j)
        {
             if(s.at(i)==s.at(j))
            {
                i++;
                j--;
            }
            else
            {
               return false;
            }
        }
        return true;
	}
};
```

## 题目 5 [合并两个有序数组](https://leetcode-cn.com/problems/merge-sorted-array/)

给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。

 

说明:

    初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。
    你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。

示例:

输入:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

输出: [1,2,2,3,5,6]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/merge-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) 
    {
        if(n<1)
        return;
        int i=0,j=0;
        while(i<m)
        {
          if(nums2.at(j)<nums1.at(i))
            {
                nums1.insert(nums1.begin()+i,nums2.at(j));
                j++;
                nums1.pop_back();
                m++;
                if(j==n)
                break;
            }
            else
                i++;
        }
        for(;j<n;j++)
        {
            nums1.insert(nums1.begin()+m,nums2.at(j));
            nums1.pop_back();
            m++;
        }
        return;
    }
};
```

## 题目 6 [环形链表](https://leetcode-cn.com/problems/linked-list-cycle/)

给定一个链表，判断链表中是否有环。

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。

示例 1：

输入：head = [3,2,0,-4], pos = 1
输出：true
解释：链表中有一个环，其尾部连接到第二个节点。

示例 2：

输入：head = [1,2], pos = 0
输出：true
解释：链表中有一个环，其尾部连接到第一个节点。

示例 3：

输入：head = [1], pos = -1
输出：false
解释：链表中没有环。

进阶：

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/linked-list-cycle
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) 
    {
        if(head==NULL)
            return false;
        else
        {
            ListNode *temp=head;
            vector<ListNode *> vet;
            while(temp->next!=NULL)
            {
                if(is_int(vet,temp))
                    return true;
                 else
                {
                    vet.push_back(temp);
                    temp=temp->next;
                }
            }
            return false;
        }
    }
    bool is_int(vector<ListNode *> &vet,ListNode * head)
    {
        for(int i=0;i<vet.size();i++)
        {
            if(vet.at(i)==head)
                return true;
        }
        return false;
    }
};
```

## 题目 7 [通过删除字母匹配到字典里最长单词](https://leetcode-cn.com/problems/longest-word-in-dictionary-through-deleting/)

给定一个字符串和一个字符串字典，找到字典里面最长的字符串，该字符串可以通过删除给定字符串的某些字符来得到。如果答案不止一个，返回长度最长且字典顺序最小的字符串。如果答案不存在，则返回空字符串。

**示例 1:**

```
输入:
s = "abpcplea", d = ["ale","apple","monkey","plea"]

输出: 
"apple"
```

**示例 2:**

```
输入:
s = "abpcplea", d = ["a","b","c"]

输出: 
"a"
```

**说明:**

1. 所有输入的字符串只包含小写字母。

2. 字典的大小不会超过 1000。

3. 所有输入的字符串长度不会超过 1000。

   

```c++
class Solution {
public:
    string findLongestWord(string s, vector<string>& d) 
    {
        string max_str="";
        if(d.size()<1)
            return {};
        else
        {
            int i=0;
            while(i<d.size())
            {
                if(is_have(s,d.at(i)))
                {
                     if(d.at(i).size()>max_str.size())
                        max_str=d.at(i);
                    else if(d.at(i).size()==max_str.size())
                    {
                        int j=0;
                        while(j<max_str.size())
                        {
                            if(d.at(i).at(j)==max_str.at(j))
                            {
                                j++;
                                continue;
                            }
                            else if(d.at(i).at(j)<max_str.at(j))
                            {
                                max_str=d.at(i);
                                break;
                            }
                            break;
                        }
                    }
                }
                i++;
            }
        }
        return max_str;
    }
    bool is_have(string &s,string &d)
    {
        int m=0,n=0;
        while(m<s.size()&&n<d.size())
        {
            if(s.at(m)==d.at(n))
            {
                 n++;
            }
            m++;   
        }
        if(n<d.size())
            return false;
        else
            return true;
    }
};
```





## 题目 8 [计数质数](https://leetcode-cn.com/problems/count-primes/)

统计所有小于非负整数 n 的质数的数量。

示例:

输入: 10
输出: 4
解释: 小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/count-primes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
// class Solution {
// public:
//     int countPrimes(int n) 
//     {
//         int count=0;
//         if(n>2)
//         {
//             count++;
//             for(int i=3;i<n;i=i+2)
//             {
//                 bool flag=true;
//                 for(int j=2;j<sqrt(i)+1;j++)
//                 {
//                     if((i%j)==0)
//                     {
//                         flag=false;
//                         break;
//                     }
//                 }
//                 if(flag)
//                     count++;
//             }
//         }  
//         return count;
//     }
// };
/*上述的时间复杂度不符合，但是结果是对的*/

```



## 题目 9 [数组中的第K个最大元素](https://leetcode-cn.com/problems/kth-largest-element-in-an-array/)

在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

示例 1:

输入: [3,2,1,5,6,4] 和 k = 2
输出: 5

示例 2:

输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
输出: 4

说明:

你可以假设 k 总是有效的，且 1 ≤ k ≤ 数组的长度。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/kth-largest-element-in-an-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) 
    {
        for(int i=0;i<k;i++)
        {
            for(int j=i+1;j<nums.size();j++)
            {
                if(nums.at(j)>nums.at(i))
                    swap(nums.at(i),nums.at(j));
            }
        }
        return nums.at(k-1);
    }
};
```



## 题目 10 [前 K 个高频元素](https://leetcode-cn.com/problems/top-k-frequent-elements/)

给定一个非空的整数数组，返回其中出现频率前 k 高的元素。

 

示例 1:

输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]

示例 2:

输入: nums = [1], k = 1
输出: [1]

 

提示：

    你可以假设给定的 k 总是合理的，且 1 ≤ k ≤ 数组中不相同的元素的个数。
    你的算法的时间复杂度必须优于 O(n log n) , n 是数组的大小。
    题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的。
    你可以按任意顺序返回答案。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/top-k-frequent-elements
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
class Solution {
public:
    typedef struct two_int{
        int m;
        unsigned short count;
    }two_int;
    vector<int> topKFrequent(vector<int>& nums, int k) 
    {
        vector<two_int> vet;
        for(int i=0;i<nums.size();i++)
        {
            if(!is_have(vet,nums.at(i)))
            {
                two_int two_int_x;
                two_int_x.m=nums.at(i);
                two_int_x.count=1;
                vet.push_back(two_int_x);
            }
        }
        for(int i=0;i<k;i++)
        {
            for(int j=i+1;j<vet.size();j++)
            {
                if(vet.at(j).count>vet.at(i).count)
                {
                    swap(vet.at(i),vet.at(j));
                }
            }
        }
         vector<int> result;
         int n=0;
         while(n<k)
         {
             result.push_back(vet.at(n).m);
             n++;
         }
         return result;
    }
    bool is_have(vector<two_int>& nums,int x)
    {
        for(int i=0;i<nums.size();i++)
        {
            if(nums.at(i).m==x)
            {
                nums.at(i).count++;
                return true;
            }
        }
        return false;
    }
};
```

## 题目 11 [根据字符出现频率排序](https://leetcode-cn.com/problems/sort-characters-by-frequency/)

给定一个字符串，请将字符串里的字符按照出现的频率降序排列。

**示例 1:**

```
输入:
"tree"

输出:
"eert"

解释:
'e'出现两次，'r'和't'都只出现一次。
因此'e'必须出现在'r'和't'之前。此外，"eetr"也是一个有效的答案。
```

**示例 2:**

```
输入:
"cccaaa"

输出:
"cccaaa"

解释:
'c'和'a'都出现三次。此外，"aaaccc"也是有效的答案。
注意"cacaca"是不正确的，因为相同的字母必须放在一起。
```

**示例 3:**

```
输入:
"Aabb"

输出:
"bbAa"

解释:
此外，"bbaA"也是一个有效的答案，但"Aabb"是不正确的。
注意'A'和'a'被认为是两种不同的字符。
```

```c++
class Solution {
public:
    typedef struct str{
        char c;
        unsigned short count;
    }str;
    string frequencySort(string s) 
    {
        vector<str> two_ch;
        str st;
        for(int i=0;i<s.size();i++)
        {
            if(!is_have(two_ch,s.at(i)))
            {
                st.c=s.at(i);
                st.count=1;
                two_ch.push_back(st);
            }
        }
        string s1="";
        for(int i=0;i<two_ch.size();i++)
        {
            for(int j=i+1;j<two_ch.size();j++)
            {
                if(two_ch.at(i).count<two_ch.at(j).count)
                {
                    swap(two_ch.at(i),two_ch.at(j));
                }
            }
            for(int k=0;k<two_ch.at(i).count;k++)
            {
                s1.push_back(two_ch.at(i).c);
            }
        }
        return s1;
    }
    bool is_have(vector<str> &two_ch,char c)
    {
        for(int i=0;i<two_ch.size();i++)
        {
            if(c==two_ch.at(i).c)
            {
                two_ch.at(i).count++;
                return true;
            }
        }
        return false;
    }
};
```

## 题目 12 [颜色分类](https://leetcode-cn.com/problems/sort-colors/)

给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

注意:
不能使用代码库中的排序函数来解决这道题。

示例:

输入: [2,0,2,1,1,0]
输出: [0,0,1,1,2,2]

进阶：

    一个直观的解决方案是使用计数排序的两趟扫描算法。
    首先，迭代计算出0、1 和 2 元素的个数，然后按照0、1、2的排序，重写当前数组。
    你能想出一个仅使用常数空间的一趟扫描算法吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sort-colors
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
class Solution {
public:
    void sortColors(vector<int>& nums) 
    {
        unsigned short m=0,n=0,k=0;
        for(int i=0;i<nums.size();i++)
        {
            if(nums.at(i)==0)
                m++;
            else if(nums.at(i)==1)
                n++;
            else
                k++;
        }
        nums.clear();
        for(int i=0;i<m+n+k;i++)
        {
            if(i<m)
                nums.push_back(0);
            else if(i<m+n)
                nums.push_back(1);
            else
                nums.push_back(2);
        }
    }
};
```





## 题目 13 [分发饼干](https://leetcode-cn.com/problems/assign-cookies/)

假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。对每个孩子 i ，都有一个胃口值 gi ，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j ，都有一个尺寸 sj 。如果 sj >= gi ，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。

注意：

你可以假设胃口值为正。
一个小朋友最多只能拥有一块饼干。

示例 1:

输入: [1,2,3], [1,1]

输出: 1

解释: 
你有三个孩子和两块小饼干，3个孩子的胃口值分别是：1,2,3。
虽然你有两块小饼干，由于他们的尺寸都是1，你只能让胃口值是1的孩子满足。
所以你应该输出1。

示例 2:

输入: [1,2], [1,2,3]

输出: 2

解释: 
你有两个孩子和三块小饼干，2个孩子的胃口值分别是1,2。
你拥有的饼干数量和尺寸都足以让所有孩子满足。
所以你应该输出2.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/assign-cookies
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++

```



## 题目 14 [相交链表](https://leetcode-cn.com/problems/intersection-of-two-linked-lists/)

编写一个程序，找到两个单链表相交的起始节点。

如下面的两个链表：

在节点 c1 开始相交。

 

示例 1：

输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2, skipB = 3
输出：Reference of the node with value = 8
输入解释：相交节点的值为 8 （注意，如果两个链表相交则不能为 0）。从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B 为 [5,0,1,8,4,5]。在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。

 

示例 2：

输入：intersectVal = 2, listA = [0,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
输出：Reference of the node with value = 2
输入解释：相交节点的值为 2 （注意，如果两个链表相交则不能为 0）。从各自的表头开始算起，链表 A 为 [0,9,1,2,4]，链表 B 为 [3,2,4]。在 A 中，相交节点前有 3 个节点；在 B 中，相交节点前有 1 个节点。

 

示例 3：

输入：intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
输出：null
输入解释：从各自的表头开始算起，链表 A 为 [2,6,4]，链表 B 为 [1,5]。由于这两个链表不相交，所以 intersectVal 必须为 0，而 skipA 和 skipB 可以是任意值。
解释：这两个链表不相交，因此返回 null。

 

注意：

    如果两个链表没有交点，返回 null.
    在返回结果后，两个链表仍须保持原有的结构。
    可假定整个链表结构中没有循环。
    程序尽量满足 O(n) 时间复杂度，且仅用 O(1) 内存。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/intersection-of-two-linked-lists
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) 
    {
        ListNode *a=headA;
        ListNode *b=headB;
        while(a!=NULL)
        {
            while(b!=NULL)
            {
                if(a==b)
                    return a;
                b=b->next;
            }
            a=a->next;
            b=headB;
        }
        return NULL;
    }
};
```

## 题目 15 [反转链表](https://leetcode-cn.com/problems/reverse-linked-list/)

反转一个单链表。

示例:

输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL

进阶:
你可以迭代或递归地反转链表。你能否用两种方法解决这道题？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-linked-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) 
    {
        if(head!=NULL)
        {
            ListNode* cur=head;
            ListNode* next=cur->next;
            while(next!=NULL)
            {
                cur->next=next->next;
                next->next=head;
                head=next;

                next=cur->next;
            }
            return head;
        }
        return NULL;
    }
};
```

## 题目 16[合并两个有序链表](https://leetcode-cn.com/problems/merge-two-sorted-lists/)

将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

 

示例：

输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/merge-two-sorted-lists
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) 
    {
        ListNode *head=(ListNode *)malloc(sizeof(ListNode));
        ListNode *p=head;
        while(l1!=nullptr&&l2!=nullptr)
        {
            if(l1->val<l2->val)
            {
                p->next=l1;
                l1=l1->next;
            }
            else
            {
                p->next=l2;
                l2=l2->next;
            }
            p=p->next;
        }
        if(l2!=nullptr)
            p->next=l2;
        else
            p->next=l1;
        return head->next;
    }
};
```

## 题目 17 [ 删除排序链表中的重复元素](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/)

给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。

示例 1:

输入: 1->1->2
输出: 1->2

示例 2:

输入: 1->1->2->3->3
输出: 1->2->3

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) 
    {
        if(head==NULL)
            return NULL;
        vector<int> vet;
        ListNode *pre=head;
        vet.push_back(head->val);
        ListNode *cur=head->next;
        while(cur!=NULL)
        {
            if(is_have(vet,cur->val))
            {
                pre->next=cur->next;
                cur=cur->next;
            }
            else
            {
                vet.push_back(cur->val);
                cur=cur->next;
                pre=pre->next;
            }
        }
        return head;
    }
    bool is_have(vector<int> &vet,int value)
    {
        for(unsigned short i=0;i<vet.size();i++)
        {
            if(value==vet.at(i))
                return true;
        }
        return false;
    }
};
```

## 题目 18 [删除链表的倒数第N个节点](https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/)

#### 

给定一个链表，删除链表的倒数第 *n* 个节点，并且返回链表的头结点。

**示例：**

```
给定一个链表: 1->2->3->4->5, 和 n = 2.

当删除了倒数第二个节点后，链表变为 1->2->3->5.
```

**说明：**

给定的 *n* 保证是有效的。

**进阶：**

你能尝试使用一趟扫描实现吗？

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) 
    {
        ListNode* p=head;
        unsigned short i=0;
        while(p!=NULL)
        {
            i++;
            p=p->next;
        }
        p=head;
        if(i==n)
            return head->next;
        i=i-n;
        while(--i)
        {
            p=p->next;
        }
        p->next=p->next->next;
        return head;  
    }
};
```

## 题目 19 [两两交换链表中的节点](https://leetcode-cn.com/problems/swap-nodes-in-pairs/)

给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。

你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

 

示例:

给定 1->2->3->4, 你应该返回 2->1->4->3.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/swap-nodes-in-pairs
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) 
    {
        ListNode *cur=head;
        vector<ListNode *> vet;
        while(cur!=NULL)
        {
            vet.push_back(cur);
            cur=cur->next;
        }
        ListNode *h= new ListNode;
        ListNode *p= h;
        
        if(vet.size()%2==0)
        {
            short i=0;
            short j=vet.size()-2;
            while(i<=j)
            {
                p->next=vet.at(i+1);
                p->next->next=vet.at(i);

                p=p->next->next;
                i=i+2;
            }
            p->next=NULL;
        }   
        else
        {
            short i=0;
            short j=vet.size()-3;
            while(i<=j)
            {
                p->next=vet.at(i+1);
                p->next->next=vet.at(i);

                p=p->next->next;
                i=i+2;
            }
            p->next=vet.at(vet.size()-1);
        } 
        return h->next;
    }
};
```

## 题目 20 [分发饼干](https://leetcode-cn.com/problems/assign-cookies/)

假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。对每个孩子 i ，都有一个胃口值 gi ，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j ，都有一个尺寸 sj 。如果 sj >= gi ，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。

注意：

你可以假设胃口值为正。
一个小朋友最多只能拥有一块饼干。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/assign-cookies
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) 
    {
        quick_sort(g,0,g.size()-1);
        quick_sort(s,0,s.size()-1);
        unsigned short i=0,j=0;
        unsigned short count=0;
        while(j<g.size() && i<s.size())
        {
            if(s.at(i)>=g.at(j))
            {
                count++;
                i++;
                j++;
            }
            else
            {
                i++;
            }
        }
        return count;
    }
    void quick_sort(vector<int> &g,int low,int high)
    {
        if(low<high)
        {
            int r=low,l=high,temp=g.at(low);
            while(r<l)
            {
                while(r<l&&g.at(l)>temp)
                {
                    l--;
                }
                if(r<l)
                {
                    g.at(r)=g.at(l);
                    r++;
                }
                while(r<l&&g.at(r)<temp)
                {
                    r++;
                }
                if(r<l)
                {
                    g.at(l)=g.at(r);
                    l--;
                }
            }
            g.at(r)=temp;
            quick_sort(g,r+1,high);
            quick_sort(g,low,r-1);
        }
        return;
    }
};
```

## 题目 21 [无重叠区间](https://leetcode-cn.com/problems/non-overlapping-intervals/)

给定一个区间的集合，找到需要移除区间的最小数量，使剩余区间互不重叠。

注意:

    可以认为区间的终点总是大于它的起点。
    区间 [1,2] 和 [2,3] 的边界相互“接触”，但没有相互重叠。

示例 1:

输入: [ [1,2], [2,3], [3,4], [1,3] ]

输出: 1

解释: 移除 [1,3] 后，剩下的区间没有重叠。

示例 2:

输入: [ [1,2], [1,2], [1,2] ]

输出: 2

解释: 你需要移除两个 [1,2] 来使剩下的区间没有重叠。

示例 3:

输入: [ [1,2], [2,3] ]

输出: 0

解释: 你不需要移除任何区间，因为它们已经是无重叠的了。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/non-overlapping-intervals
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) 
    {
        if(intervals.size()<1)
            return 0;
        sort(intervals.begin(), intervals.end(),camp);
        unsigned short i=1,count=1;
        int cmp=intervals[0][1];
        while(i<intervals.size())
        {
            if(intervals[i][0]<cmp)
            {
                ++i;
            }
            else
            {
                cmp=intervals[i][1];
                ++i;
                ++count;
            }
        }
        return intervals.size()-count;
    }
      static bool camp(vector<int>a,vector<int>b){
        return a[1]<b[1];
    }
};
```

## 题目 22 [用最少数量的箭引爆气球](https://leetcode-cn.com/problems/minimum-number-of-arrows-to-burst-balloons/)

在二维空间中有许多球形的气球。对于每个气球，提供的输入是水平方向上，气球直径的开始和结束坐标。由于它是水平的，所以y坐标并不重要，因此只要知道开始和结束的x坐标就足够了。开始坐标总是小于结束坐标。平面内最多存在104个气球。

一支弓箭可以沿着x轴从不同点完全垂直地射出。在坐标x处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足  xstart ≤ x ≤ xend，则该气球会被引爆。可以射出的弓箭的数量没有限制。 弓箭一旦被射出之后，可以无限地前进。我们想找到使得所有气球全部被引爆，所需的弓箭的最小数量。

Example:

输入:
[[10,16], [2,8], [1,6], [7,12]]

输出:
2

解释:
对于该样例，我们可以在x = 6（射爆[2,8],[1,6]两个气球）和 x = 11（射爆另外两个气球）。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-number-of-arrows-to-burst-balloons
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) 
    {
        if(points.size()<1)
            return 0;
        quick_sort(points,0,points.size()-1);
        unsigned short i=1;
        int temp=points[0][1];
        unsigned short count=1;
        while(i<points.size())
        {
            if(points[i][0]<=temp)
            {
                i++;

            }
            else
            {
                count++;
                temp=points[i][1];
                i++;
            }
        }
        return count;
    }
    void quick_sort(vector<vector<int>>& points,int low,int high)
    {
        if(low>=high)
        {
            return;
        }
        unsigned short r=low,l=high;
        int temp1=points[r][0];
        int temp2=points[r][1];
        while(r<l)
        {
            while(r<l&&temp2<points[l][1])
            {
                l--;
            }
            if(r<l)
            {
                points[r][1]=points[l][1];
                points[r][0]=points[l][0];
                r++;
            }
            while(r<l&&temp2>points[r][1])
            {
                r++;
            }
            if(r<l)
            {
                points[l][1]=points[r][1];
                points[l][0]=points[r][0];
            }
        }
        points[r][0]=temp1;
        points[r][1]=temp2;
        quick_sort(points,low,r-1);
        quick_sort(points,r+1,high);
        return;
    }
};
```

## 题目 23 [根据身高重建队列](https://leetcode-cn.com/problems/queue-reconstruction-by-height/)

假设有打乱顺序的一群人站成一个队列。 每个人由一个整数对(h, k)表示，其中h是这个人的身高，k是排在这个人前面且身高大于或等于h的人数。 编写一个算法来重建这个队列。

注意：
总人数少于1100人。

示例

输入:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

输出:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/queue-reconstruction-by-height
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) 
    {
        if(people.size()<1)
            return people;
       select_sort(people);
       for(unsigned short i=1;i<people.size();i++)
       {
           if(people[i][1]<i)
           {
               int j=i-1;
               int temp1=people[i][0];
               int temp2=people[i][1];
               while(j>=temp2)
               {
                   people[j+1][0]=people[j][0];
                   people[j+1][1]=people[j][1];
                   j--;
               }
               people[j+1][0]=temp1;
               people[j+1][1]=temp2;
           }
       }
       return people;
    }

       /*按照身高由高到低排序，相等时按照次序由低到高*/
   void select_sort(vector<vector<int>>& people)
   {
       for(int i=0;i<people.size()-1;i++)
       {
           for(int j=i+1;j<people.size();j++)
           {
               if(people[i][0]<people[j][0])
               {
                   swap(people.at(i),people.at(j));
               }
               else if(people[i][0]==people[j][0]&&people[i][1]>people[j][1])
               {
                   swap(people.at(i),people.at(j));
               }
           }
       }
       return;
   }
};
```

## 题目 24 [买卖股票的最佳时机](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/)

给定一个数组，它的第 *i* 个元素是一支给定股票第 *i* 天的价格。

如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。

注意：你不能在买入股票前卖出股票。

 

**示例 1:**

```
输入: [7,1,5,3,6,4]
输出: 5
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
```

**示例 2:**

```
输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
```

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) 
    {
        if(prices.size()<=1)
            return 0;
        unsigned input=prices.at(0);
        int profit=0;
        for(unsigned short i=1;i<prices.size();i++)
        {
            input=prices.at(i)<input?prices.at(i):input;
            profit=profit>prices.at(i)-input?profit:prices.at(i)-input;
        }
        return profit;
    }
};
```

## 题目 25 [买卖股票的最佳时机 II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/)

给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

 

示例 1:

输入: [7,1,5,3,6,4]
输出: 7
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
     随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6-3 = 3 。

示例 2:

输入: [1,2,3,4,5]
输出: 4
解释: 在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。
     注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。
     因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。

示例 3:

输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。

 

提示：

    1 <= prices.length <= 3 * 10 ^ 4
    0 <= prices[i] <= 10 ^ 4

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) 
    {
        if(prices.size()<1)
            return 0;
        int profit=0;
        int input=prices.at(0);
        for(unsigned short i=1;i<prices.size();++i)
        {
            if(prices.at(i)>input)
            {
                profit=profit+prices.at(i)-input;
                input=prices.at(i);
            }
            else
            {
                input=prices.at(i);
            }
        }
        return profit;   
    }
};
```

## 题目 26 [种花问题](https://leetcode-cn.com/problems/can-place-flowers/)

假设你有一个很长的花坛，一部分地块种植了花，另一部分却没有。可是，花卉不能种植在相邻的地块上，它们会争夺水源，两者都会死去。

给定一个花坛（表示为一个数组包含0和1，其中0表示没种植花，1表示种植了花），和一个数 n 。能否在不打破种植规则的情况下种入 n 朵花？能则返回True，不能则返回False。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/can-place-flowers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) 
    {
        unsigned short count=0;
        for(unsigned short i=0;i<flowerbed.size();i++)
        {
            /*注意为容器中首尾的特殊情况，这个判断条件看的题解，属实写的漂亮*/
if (flowerbed[i]==0&&(i == 0||flowerbed[i-1]==0)&&(i==flowerbed.size()-1||flowerbed[i+1]==0))
            {
                flowerbed[i]=1;
                count++;
            }
        }
        return count>=n;
    }
};
```

## 题目 27 [判断子序列](https://leetcode-cn.com/problems/is-subsequence/)

给定字符串 s 和 t ，判断 s 是否为 t 的子序列。

你可以认为 s 和 t 中仅包含英文小写字母。字符串 t 可能会很长（长度 ~= 500,000），而 s 是个短字符串（长度 <=100）。

字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，"ace"是"abcde"的一个子序列，而"aec"不是）。

示例 1:
s = "abc", t = "ahbgdc"

返回 true.

示例 2:
s = "axc", t = "ahbgdc"

返回 false.

后续挑战 :

如果有大量输入的 S，称作S1, S2, ... , Sk 其中 k >= 10亿，你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/is-subsequence
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
class Solution {
public:
    bool isSubsequence(string s, string t) 
    {
        unsigned short i=0,j=0;
        while(i<s.size()&&j<t.size())
        {
            if(s.at(i)==t.at(j))
            {
                ++i;
                ++j;
            }
            else
                j++;
        }
        return i==s.size();
    }
};
```

## 题目 28 [非递减数列](https://leetcode-cn.com/problems/non-decreasing-array/)

给你一个长度为 n 的整数数组，请你判断在 最多 改变 1 个元素的情况下，该数组能否变成一个非递减数列。

我们是这样定义一个非递减数列的： 对于数组中所有的 i (0 <= i <= n-2)，总满足 nums[i] <= nums[i + 1]。

示例 :

输入: nums = [4,2,3]
输出: true
解释: 你可以通过把第一个4变成1来使得它成为一个非递减数列。

示例 2:

输入: nums = [4,2,1]
输出: false
解释: 你不能在只改变一个元素的情况下将其变为非递减数列。

说明：

    1 <= n <= 10 ^ 4
    - 10 ^ 5 <= nums[i] <= 10 ^ 5

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/non-decreasing-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
class Solution {
public:
    bool checkPossibility(vector<int>& nums) 
    {
        unsigned short count=0;
        for(unsigned short i=1;i<nums.size()&&count<2;i++)
        {
            if(nums.at(i)>=nums.at(i-1))
                continue;
            count++;
            /* 两种情况：
             * 1.当前位置i的值小于位置i-1的值小于i-2位置的值
             * 2.当前位置i的值小于前一个位置i-1的值,大于i-2位置的值
             */
            if(i-2>=0&&nums.at(i)<nums.at(i-2))
                nums.at(i)=nums.at(i-1);
            else
                nums.at(i-1)=nums.at(i);
        }
        return count<=1;
    }
};
```

## 题目 29 [最大子序和](https://leetcode-cn.com/problems/maximum-subarray/)

给定一个整数数组 `nums` ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

**示例:**

```
输入: [-2,1,-3,4,-1,2,1,-5,4],
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
```

**进阶:**

如果你已经实现复杂度为 O(*n*) 的解法，尝试使用更为精妙的分治法求解。

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) 
    {
        /*贪心算法：先让最大值取第一个
         *
         */
        if(nums.size()<1)
            return 0;
        int count=nums[0],pre_count=0;
        for(unsigned short i=0;i<nums.size();i++)
        {
            pre_count=max(nums.at(i)+pre_count,nums.at(i));
            count=max(count,pre_count);
        }
        return count;
    }
};
```

## 题目 30 [划分字母区间](https://leetcode-cn.com/problems/partition-labels/)

字符串 S 由小写字母组成。我们要把这个字符串划分为尽可能多的片段，同一个字母只会出现在其中的一个片段。返回一个表示每个字符串片段的长度的列表

示例 1：

输入：S = "ababcbacadefegdehijhklij"
输出：[9,7,8]
解释：
划分结果为 "ababcbaca", "defegde", "hijhklij"。
每个字母最多出现在一个片段中。
像 "ababcbacadefegde", "hijhklij" 的划分是错误的，因为划分的片段数较少。

提示：

    S的长度在[1, 500]之间。
    S只包含小写字母 'a' 到 'z' 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/partition-labels
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
class Solution {
public:
    /*贪心算法：两次遍历，找到后面与当前位置重复的下标，保证两下标中间位置与后续的位置没有重合的值
     *        然后将两个下标相减加1即为一个片段的长度，如果后面没有与之重合的值本身就是一个片段。
     */
    vector<int> partitionLabels(string S) 
    {
        if(S.size()<1)
            return {};
        unsigned short m=0,n=0;
        vector<int> vet;
        for(unsigned short i=0;i<S.size()-1;i++)
        {
            for(unsigned short j=i+1;j<S.size();j++)
            {
                if(S[j]==S[i]&&j>n)
                {
                    n=j;
                }
            }
            if(i==n)
            {
                vet.push_back(n-m+1);
                m=n+1;
                n=n+1;
            }
            if(i>n)/*表示后面没有与之重合的值，所以本身就是一个片段*/
            {
                vet.push_back(1);
                m=i;
                n=i;
            }
        }
        vet.push_back(n-m+1);
        return vet;
    }
};
```

## 题目 31 [两数相加 II](https://leetcode-cn.com/problems/add-two-numbers-ii/)

#### 

给你两个 **非空** 链表来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。

你可以假设除了数字 0 之外，这两个数字都不会以零开头。

**进阶：**

如果输入链表不能修改该如何处理？换句话说，你不能对列表中的节点进行翻转。

**示例：**

```
输入：(7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 8 -> 0 -> 7
```

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
    {
        /* 本题用栈更好，但是第一想法没想到，就用这种试一下
         * 将链表中的值存入容器中
         */
        vector<unsigned short> vet1,vet2;
        while(l1!=NULL)
        {
            vet1.insert(vet1.begin(), l1->val);
            l1=l1->next;
        }
        while(l2!=NULL)
        {
            vet2.insert(vet2.begin(), l2->val);
            l2=l2->next;
        }
        unsigned short i=0,j=0;
        unsigned short shang=0,yu=0;
        ListNode *head=new ListNode;
        ListNode *p=head;
        while(i<vet1.size()||j<vet2.size())
        {
            unsigned short temp,a,b;
            a=i<vet1.size()?vet1[i]:0;
            b=j<vet2.size()?vet2[j]:0;
            temp=a+b+shang;
            if(temp<10)
            {
                p->next=new ListNode;
                p->next->val=temp;
                p=p->next;
                shang=0;
                yu=0;
            }
            else
            {
                shang=temp/10;
                yu=temp%10;
                p->next=new ListNode;
                p->next->val=yu;
                p=p->next;
            }
            i++;
            j++;
        }
        if(shang>0)
        {
            p->next=new ListNode;
            p->next->val=shang;
            p->next->next=NULL;
        }
        else
        {
            p->next=NULL;
        }
        reverse(head);
        return head->next;
    }
    /*顺道练手，反转一个链表*/
    void reverse(ListNode *head)
    {
        if(head==NULL)
            return;
        ListNode *current=head->next;
        ListNode *next=current->next;
        while(next!=NULL)
        {
            current->next=next->next;
            next->next=head->next;
            head->next=next;

            next=current->next;
        }
        return;
    }
};
```

## 题目 32 [回文链表](https://leetcode-cn.com/problems/palindrome-linked-list/)

请判断一个链表是否为回文链表。

示例 1:

输入: 1->2
输出: false

示例 2:

输入: 1->2->2->1
输出: true

进阶：
你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/palindrome-linked-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    /* 先遍历一遍链表得到所有的值。
     * 在遍历一次与之对边即可。
     */
    bool isPalindrome(ListNode* head) 
    {
        vector<int> vet;
        ListNode *p=head;
        while(p!=NULL)
        {
            vet.push_back(p->val);
            p=p->next;
        }
        unsigned short i=vet.size()-1;
        p=head;
        while(p!=NULL&&i>=0)
        {
            if(p->val == vet[i])
            {
                i--;
                p=p->next;
            }
            else
                return false;
        }
        return true;
    }
};
```

## 题目 33 [分隔链表](https://leetcode-cn.com/problems/split-linked-list-in-parts/)

给定一个头结点为 root 的链表, 编写一个函数以将链表分隔为 k 个连续的部分。

每部分的长度应该尽可能的相等: 任意两部分的长度差距不能超过 1，也就是说可能有些部分为 null。

这k个部分应该按照在链表中出现的顺序进行输出，并且排在前面的部分的长度应该大于或等于后面的长度。

返回一个符合上述规则的链表的列表。

举例： 1->2->3->4, k = 5 // 5 结果 [ [1], [2], [3], [4], null ]

示例 1：

输入: 
root = [1, 2, 3], k = 5
输出: [[1],[2],[3],[],[]]
解释:
输入输出各部分都应该是链表，而不是数组。
例如, 输入的结点 root 的 val= 1, root.next.val = 2, \root.next.next.val = 3, 且 root.next.next.next = null。
第一个输出 output[0] 是 output[0].val = 1, output[0].next = null。
最后一个元素 output[4] 为 null, 它代表了最后一个部分为空链表。

示例 2：

输入: 
root = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], k = 3
输出: [[1, 2, 3, 4], [5, 6, 7], [8, 9, 10]]
解释:
输入被分成了几个连续的部分，并且每部分的长度相差不超过1.前面部分的长度大于等于后面部分的长度。

 

提示:

    root 的长度范围： [0, 1000].
    输入的每个节点的大小范围：[0, 999].
    k 的取值范围： [1, 50].

 

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/split-linked-list-in-parts
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    /*
     * 首先遍历一遍链表，将每一个节点的地址存入容器中，判断链表被分成多少段，总共三种情况：
     * 第一种，k>链表长度--------shang=0
     * 第二种，k<链表长度，链表刚好被等分，此时shang>0,yu=0
     * 第三种，k<链表长度，链表不能被等分，此时shang>0,yu>0
     */
    vector<ListNode*> splitListToParts(ListNode* root, int k) 
    {
        vector<ListNode *> vet;
        ListNode *p=root;
        while(p!=NULL)
        {
            vet.push_back(p);
            p=p->next;
        }
        unsigned short shang=vet.size()/k;
        unsigned short yu=vet.size()%k;
        if(shang==0)
        {
            unsigned short i=0;
            while(i<vet.size())
            {
                vet[i]->next=NULL;
                i++;
            }
            while(i<k)
            {
                vet.push_back(NULL);
                i++;
            }
            return vet;
        }
        else if(shang>0 && yu==0)
        {
            vector<ListNode *> vet1;
            unsigned short i=0;
            while(i<vet.size())
            {
                vet1.push_back(vet[i]);
                i=i+shang;
                vet[i-1]->next=NULL;
            }
            return vet1;
        }
        else
        {
            vector<ListNode *> vet1;
            unsigned short i=0;
            while(i<vet.size())
            {
                if(yu>0)
                {
                    vet1.push_back(vet[i]);
                    i=i+shang+1;
                    vet[i-1]->next=NULL;
                    yu--;
                }
                else
                {
                    vet1.push_back(vet[i]);
                    i=i+shang;
                    vet[i-1]->next=NULL;
                }
            }
            return vet1;
        }
        return {};
    }
};
```

## 题目 34 [奇偶链表](https://leetcode-cn.com/problems/odd-even-linked-list/)

给定一个单链表，把所有的奇数节点和偶数节点分别排在一起。请注意，这里的奇数节点和偶数节点指的是节点编号的奇偶性，而不是节点的值的奇偶性。

请尝试使用原地算法完成。你的算法的空间复杂度应为 O(1)，时间复杂度应为 O(nodes)，nodes 为节点总数。

示例 1:

输入: 1->2->3->4->5->NULL
输出: 1->3->5->2->4->NULL

示例 2:

输入: 2->1->3->5->6->4->7->NULL 
输出: 2->3->6->7->1->5->4->NULL

说明:

    应当保持奇数节点和偶数节点的相对顺序。
    链表的第一个节点视为奇数节点，第二个节点视为偶数节点，以此类推。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/odd-even-linked-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    /* 首先判断链表的合法性，合法之后在进行操作
     * 奇数和偶数各取一个链表头用于遍历，同时保存偶数的链表头
     * 遍历时注意判断，以防越界
     * 最后将奇数和偶数拼接在一起即可
     *
     */
    ListNode* oddEvenList(ListNode* head) 
    {
        if(head==nullptr||head->next==nullptr)
            return head;
        ListNode *ji=head;
        ListNode *ou=head->next;
        ListNode *ou1=head->next;
        while(ji->next->next!=nullptr)
        {
            ji->next=ji->next->next;
            ji=ji->next;
            if(ou->next->next!=nullptr)
            {
                ou->next=ou->next->next;
                ou=ou->next;
            }
            else
            {
                ou->next=nullptr;
                break;
            }
        }
        ji->next=ou1;
        return head;
    }
};
```

