#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Định nghĩa cấu trúc cho hỗn số
typedef struct {
    int phan_nguyen;
    int tu_so;
    int mau_so;
} HonSo;

// Hàm tạo mảng chứa hỗn số ngẫu nhiên
void taoMangHonSo(HonSo b[], int n) {
    for (int i = 0; i < n; i++) {
        b[i].phan_nguyen = rand() % 10; // Phần nguyên từ 0 đến 9
        b[i].tu_so = rand() % 10; // Tử số từ 0 đến 9
        do {
            b[i].mau_so = rand() % 10;
        } while (b[i].mau_so == 0); // Mẫu số khác 0
    }
}

// Hàm xuất danh sách hỗn số
void xuatDanhSachHonSo(HonSo b[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d %d/%d\n", b[i].phan_nguyen, b[i].tu_so, b[i].mau_so);
    }
}

// Hàm tìm hỗn số x trong mảng b theo giải thuật Linear Search
int timHonSoLinearSearch(HonSo b[], int n, HonSo x) {
    for (int i = 0; i < n; i++) {
        if (b[i].phan_nguyen == x.phan_nguyen && b[i].tu_so == x.tu_so && b[i].mau_so == x.mau_so) {
            return i;
        }
    }
    return -1;
}

// Hàm sắp xếp b sao cho các phần tử có phần nguyên chẵn lên đầu, phần tử có phần nguyên lẻ ở cuối mảng
void sapXepChanLe(HonSo b[], int n) {
    HonSo temp;
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (b[i].phan_nguyen % 2 == 0) {
            temp = b[j];
            b[j] = b[i];
            b[i] = temp;
            j++;
        }
    }
}

// Hàm so sánh hai hỗn số
int soSanhHonSo(HonSo hs1, HonSo hs2) {
    int tu1 = hs1.phan_nguyen * hs1.mau_so + hs1.tu_so;
    int tu2 = hs2.phan_nguyen * hs2.mau_so + hs2.tu_so;
    int mau1 = hs1.mau_so;
    int mau2 = hs2.mau_so;

    if (tu1 * mau2 > tu2 * mau1) {
        return 1;
    }
    else if (tu1 * mau2 < tu2 * mau1) {
        return -1;
    }
    else {
        return 0;
    }
}

// Hàm tìm hỗn số x theo giải thuật binary search trong mảng b đã được sắp xếp tăng/giảm
int timHonSoBinarySearch(HonSo b[], int n, HonSo x) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = soSanhHonSo(b[mid], x);
        if (cmp == 0) {
            return mid;
        }
        else if (cmp < 0) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

// Hàm chia mảng b thành 2 mảng s1 và s2, với s1 chứa các phần nguyên, s2 chứa phân số
void chiaMang(HonSo b[], int n, int s1[], HonSo s2[]) {
    for (int i = 0; i < n; i++) {
        s1[i] = b[i].phan_nguyen;
        s2[i].phan_nguyen = 0;
        s2[i].tu_so = b[i].tu_so;
        s2[i].mau_so = b[i].mau_so;
    }
}

// Hàm xóa phần tử thứ k trong mảng b
void xoaPhanTu(HonSo b[], int* n, int k) {
    if (k < 0 || k >= *n) {
        printf("Vi tri xoa khong hop le\n");
        return;
    }
    for (int i = k; i < *n - 1; i++) {
        b[i] = b[i + 1];
    }
    (*n)--;
}

// Hàm thêm hỗn số x vào mảng b tại vị trí k
void themHonSo(HonSo b[], int* n, HonSo x, int k) {
    if (k < 0 || k > *n) {
        printf("Vi tri them khong hop le\n");
        return;
    }
    for (int i = *n; i > k; i--) {
        b[i] = b[i - 1];
    }
    b[k] = x;
    (*n)++;
}

// Hàm tạo mảng c chứa các phần tử là phân số được đổi từ các phần tử hỗn số của mảng b
void taoMangPhanSo(HonSo b[], int n, HonSo c[]) {
    for (int i = 0; i < n; i++) {
        c[i].phan_nguyen = 0;
        c[i].tu_so = b[i].phan_nguyen * b[i].mau_so + b[i].tu_so;
        c[i].mau_so = b[i].mau_so;
    }
}

// Hàm tính tổng các phần tử của mảng b
HonSo tongMang(HonSo b[], int n) {
    HonSo tong;
    tong.phan_nguyen = 0;
    tong.tu_so = 0;
    tong.mau_so = 1;

    for (int i = 0; i < n; i++) {
        int tu1 = tong.tu_so * b[i].mau_so + b[i].tu_so * tong.mau_so;
        int mau1 = tong.mau_so * b[i].mau_so;
        tong.phan_nguyen += b[i].phan_nguyen;
        tong.tu_so = tu1;
        tong.mau_so = mau1;
    }
    return tong;
}

// Hàm tìm phần tử lớn nhất/nhỏ nhất của b
HonSo timHonSoLonNhat(HonSo b[], int n) {
    HonSo max = b[0];
    for (int i = 1; i < n; i++) {
        if (soSanhHonSo(b[i], max) > 0) {
            max = b[i];
        }
    }
    return max;
}

HonSo timHonSoNhoNhat(HonSo b[], int n) {
    HonSo min = b[0];
    for (int i = 1; i < n; i++) {
        if (soSanhHonSo(b[i], min) < 0) {
            min = b[i];
        }
    }
    return min;
}

// Hàm xuất vị trí phần tử có phần nguyên chẵn của b
void xuatViTriPhanNguyenChan(HonSo b[], int n) {
    printf("Vi tri phan tu co phan nguyen chan: ");
    for (int i = 0; i < n; i++) {
        if (b[i].phan_nguyen % 2 == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

// Hàm xuất vị trí của phần tử lớn nhất/nhỏ nhất của b
void xuatViTriLonNhat(HonSo b[], int n) {
    int maxIdx = 0;
    for (int i = 1; i < n; i++) {
        if (soSanhHonSo(b[i], b[maxIdx]) > 0) {
            maxIdx = i;
        }
    }
    printf("Vi tri phan tu lon nhat: %d\n", maxIdx);
}

void xuatViTriNhoNhat(HonSo b[], int n) {
    int minIdx = 0;
    for (int i = 1; i < n; i++) {
        if (soSanhHonSo(b[i], b[minIdx]) < 0) {
            minIdx = i;
        }
    }
    printf("Vi tri phan tu nho nhat: %d\n", minIdx);
}


int main() {
    srand((unsigned int)time(0));

    int n = 15;
    HonSo b[100] = { 0 };
    taoMangHonSo(b, n);
    printf("Danh sach hon so ban dau:\n");
    xuatDanhSachHonSo(b, n);

    // 1. Tìm hỗn số x trong mảng b theo giải thuật Linear Search
    HonSo x = { 3, 5, 7 }; // Ví dụ hỗn số x = 3 5/7
    int viTri = timHonSoLinearSearch(b, n, x);
    if (viTri != -1) {
        printf("Tim thay hon so tai vi tri: %d\n", viTri);
    }
    else {
        printf("Khong tim thay hon so\n");
    }

    // 2. Sắp xếp b sao cho các phần tử có phần nguyên chẵn lên đầu, phần tử có phần nguyên lẻ ở cuối mảng
    sapXepChanLe(b, n);
    printf("Mang sau khi sap xep chan le:\n");
    xuatDanhSachHonSo(b, n);

    // 3. Tìm hỗn số x theo giải thuật binary search trong mảng b đã được sắp xếp tăng/giảm
    HonSo x2 = b[7]; // Chọn một phần tử ngẫu nhiên trong mảng b để tìm kiếm
    viTri = timHonSoBinarySearch(b, n, x2);
    if (viTri != -1) {
        printf("Tim thay hon so tai vi tri: %d (Binary Search)\n", viTri);
    }
    else {
        printf("Khong tim thay hon so (Binary Search)\n");
    }

    // 4. Chia mảng b thành 2 mảng s1 và s2, với s1 chứa các phần nguyên, s2 chứa phân số
    int s1[100];
    HonSo s2[100];
    chiaMang(b, n, s1, s2);
    printf("Mang s1 (phan nguyen): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", s1[i]);
    }
    printf("\nMang s2 (phan so): ");
    for (int i = 0; i < n; i++) {
        printf("%d/%d ", s2[i].tu_so, s2[i].mau_so);
    }
    printf("\n");

    // 5. Xóa phần tử thứ k trong mảng b
    int k = 3;
    xoaPhanTu(b, &n, k);
    printf("Mang sau khi xoa phan tu thu %d:\n", k);
    xuatDanhSachHonSo(b, n);

    // 6. Thêm hỗn số x vào mảng b tại vị trí k
    HonSo x3 = { 2, 3, 4 }; // Ví dụ hỗn số x = 2 3/4
    themHonSo(b, &n, x3, k);
    printf("Mang sau khi them hon so tai vi tri %d:\n", k);
    xuatDanhSachHonSo(b, n);

    // 7. Tạo mảng c chứa các phần tử là phân số được đổi từ các phần tử hỗn số của mảng b
    HonSo c[100];
    taoMangPhanSo(b, n, c);
    printf("Mang c (phan so tu hon so): ");
    for (int i = 0; i < n; i++) {
        printf("%d/%d ", c[i].tu_so, c[i].mau_so);
    }
    printf("\n");

    // 8. Tính tổng các phần tử của mảng b
    HonSo tong = tongMang(b, n);
    printf("Tong cac phan tu cua mang b: %d %d/%d\n", tong.phan_nguyen, tong.tu_so, tong.mau_so);

    // 9. Tìm phần tử lớn nhất/nhỏ nhất của b
    HonSo max = timHonSoLonNhat(b, n);
    HonSo min = timHonSoNhoNhat(b, n);
    printf("Hon so lon nhat: %d %d/%d\n", max.phan_nguyen, max.tu_so, max.mau_so);
    printf("Hon so nho nhat: %d %d/%d\n", min.phan_nguyen, min.tu_so, min.mau_so);

    // 10. Xuất vị trí phần tử có phần nguyên chẵn của b
    xuatViTriPhanNguyenChan(b, n);

    // 11. Xuất vị trí của phần tử lớn nhất/nhỏ nhất của b
    xuatViTriLonNhat(b, n);
    xuatViTriNhoNhat(b, n);

    return 0;
}