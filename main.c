#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/**
 * David has several containers, each with a number of balls in it. He has just enough containers to sort each type
 * of ball he has into its own container. David wants to sort the balls using his sort method.
 * David wants to perform some number of swap operations such that:
 * Each container contains only balls of the same type.
 * No two balls of the same type are located in different containers.
 * In a single operation, David can swap two balls located in different containers.
 * Function Description
 * Complete the organizingContainers function in the editor below.
 * organizingContainers has the following parameter(s):
 * int container[n][m]: a two-dimensional array of integers that represent the number of balls of each color in each
 * container
 * Returns
 * string: either Possible or Impossible
 */
void merge(int a[], const int left, const int mid, const int right) {
    int i, j, k;
    const int l_size = mid - left + 1, r_size = right - mid;
    int la[l_size], ra[r_size];
    for (i = 0; i < l_size; ++i) la[i] = a[left + i];
    for (j = 0; j < r_size; ++j) ra[j] = a[mid + 1 + j];
    i = 0, j = 0, k = left;
    while (i < l_size && j < r_size) {
        a[k++] = (la[i] <= ra[j]) ? la[i++] : ra[j++];
    }
    while (i < l_size) a[k++] = la[i++];
    while (j < r_size) a[k++] = ra[j++];
}

void merge_sort(int a[], const int left, const int right) {
    if (left < right) {
        const int mid = (left + right) / 2;
        merge_sort(a, left, mid);
        merge_sort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

void sort(const int size, int a[]) {
    merge_sort(a, 0, size - 1);
}

bool can_resort(const int size, int *const container[]) {
    int row_sums[size], col_sums[size];
    for (int i = 0; i < size; ++i) {
        row_sums[i] = 0;
        col_sums[i] = 0;
        for (int j = 0; j < size; ++j) {
            row_sums[i] += container[i][j];
            col_sums[i] += container[j][i];
        }
    }
    sort(size, row_sums);
    sort(size, col_sums);
    for (int i = 0; i < size; ++i) {
        if (row_sums[i] != col_sums[i]) return false;
    }
    return true;
}

char* organizingContainers(int size, int* container[]) {
    return can_resort(size, container) ? "Possible" : "Impossible";
}

int main() {
    int a[] = {1, 3, 1};
    int b[] = {2, 1, 2};
    int c[] = {3, 3, 3};
    int *balls_in_boxes0[3] = {a, b, c};
    assert("Impossible" == organizingContainers(3, balls_in_boxes0));
    int a1[] = {0, 2, 1};
    int b1[] = {1, 1, 1};
    int c1[] = {2, 0, 0};
    int *balls_in_boxes1[3] = {a1, b1, c1};
    assert("Possible" == organizingContainers(3, balls_in_boxes1));
    return 0;
}
