#include <stdio.h>
#include <stdbool.h>

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

bool can_resort(const int size, int *const container[size]) {
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

int main() {
    int a[] = {1, 3, 1};
    int b[] = {2, 1, 2};
    int c[] = {3, 3, 3};
    int *balls_in_boxes[3] = {a, b, c};
    printf("%s\n", can_resort(3, balls_in_boxes) ? "Possible" : "Impossible");
    int a1[] = {0, 2, 1};
    int b1[] = {1, 1, 1};
    int c1[] = {2, 0, 0};
    int *balls_in_boxes2[3] = {a1, b1, c1};
    printf("%s\n", can_resort(3, balls_in_boxes2) ? "Possible" : "Impossible");
    return 0;
}
