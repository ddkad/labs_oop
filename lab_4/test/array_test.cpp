#include <gtest/gtest.h>
#include "array.h"

TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_GE(arr.capacity(), 0);
}

TEST(ArrayTest, PushAndSize) {
    Array<int> arr;
    arr.push(1);
    arr.push(2);
    EXPECT_EQ(arr.size(), 2);
}

TEST(ArrayTest, AccessOperator) {
    Array<int> arr;
    arr.push(10);
    arr.push(20);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST(ArrayTest, MoveConstructor) {
    Array<int> arr1;
    arr1.push(1);
    arr1.push(2);
    
    Array<int> arr2 = std::move(arr1);  
    
    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
    EXPECT_EQ(arr1.size(), 0);  
}

TEST(ArrayTest, MoveAssignment) {
    Array<int> arr1;
    arr1.push(1);
    
    Array<int> arr2;
    arr2 = std::move(arr1); 
    
    EXPECT_EQ(arr2.size(), 1);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr1.size(), 0);
}

TEST(ArrayTest, Erase) {
    Array<int> arr;
    arr.push(1);
    arr.push(2);
    arr.push(3);
    
    arr.erase(1);  
    
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(ArrayTest, Pop) {
    Array<int> arr;
    arr.push(1);
    arr.push(2);
    
    arr.pop();
    
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 1);
}

TEST(ArrayTest, Clear) {
    Array<int> arr;
    arr.push(1);
    arr.push(2);
    
    arr.clear();
    
    EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, InitializerList) {
    Array<int> arr{1, 2, 3};
    
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, ResizeGrowsCapacity) {
    Array<int> arr;
    size_t initial_capacity = arr.capacity();
    
    for (int i = 0; i < 20; ++i) {
        arr.push(i);
    }
    
    EXPECT_GT(arr.capacity(), initial_capacity);
    EXPECT_EQ(arr.size(), 20);
}