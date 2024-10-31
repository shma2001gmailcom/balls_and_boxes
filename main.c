#include <stdio.h>
#include <stdbool.h>

void merge(int a[], const int left, const int mid, const int right) {
    int i, j, k;
    const int l_size = mid - left + 1, r_size = right - mid;
    int la[l_size], ra[r_size];
    for (i = 0; i < l_size; la[i] = a[left + i], ++i);
    for (j = 0; j < r_size; ra[j] = a[mid + 1 + j], ++j);
    i = 0, j = 0, k = left;
    while (i < l_size && j < r_size) {
        if (la[i] <= ra[j]) {
            a[k] = la[i];
            ++i;
        } else {
            a[k] = ra[j];
            ++j;
        }
        ++k;
    }
    while (i < l_size) {
        a[k] = la[i];
        ++i;
        ++k;
    }
    while (j < r_size) {
        a[k] = ra[j];
        ++j;
        ++k;
    }
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

bool can_resort(const int size, int **container) {
    int row_sums[size], col_sums[size];
    int row_sum, col_sum;
    for (int i = 0; i < size; ++i) {
        row_sum = col_sum = 0;
        for (int j = 0; j < size; row_sum += container[i][j], col_sum += container[j][i], ++j);
        row_sums[i] = row_sum;
        col_sums[i] = col_sum;
    }
    sort(size, row_sums);
    sort(size, col_sums);
    for (int i = 0; i < size; ++i) if (row_sums[i] != col_sums[i]) return false;
    return true;
}

int main() {
    int *balls_in_boxes[3];
    int a[] = {1, 3, 1};
    int b[] = {2, 1, 2};
    int c[] = {3, 3, 3};
    balls_in_boxes[0] = a;
    balls_in_boxes[1] = b;
    balls_in_boxes[2] = c;
    printf("%s\n", can_resort(3, balls_in_boxes) ? "Possible" : "Impossible");
    int a1[] = {0, 2, 1};
    int b1[] = {1, 1, 1};
    int c1[] = {2, 0, 0};
    balls_in_boxes[0] = a1;
    balls_in_boxes[1] = b1;
    balls_in_boxes[2] = c1;
    printf("%s\n", can_resort(3, balls_in_boxes) ? "Possible" : "Impossible");
    return 0;
}
