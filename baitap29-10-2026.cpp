
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

struct Ngay {
    int ngay, thang, nam;
};

struct HangHoa {
    int ma;
    string ten;
    Ngay ngayXuat;
    float gia;
};

void nhap(HangHoa a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "\nNhap hang hoa thu " << i + 1 << ":\n";

        cout << "Ma hang hoa: ";
        cin >> a[i].ma;
        cin.ignore();

        cout << "Ten hang hoa: ";
        getline(cin, a[i].ten);

        char dau1, dau2;
        cout << "Ngay xuat hang (dd/mm/yyyy): ";
        cin >> a[i].ngayXuat.ngay >> dau1
            >> a[i].ngayXuat.thang >> dau2
            >> a[i].ngayXuat.nam;

        cout << "Gia xuat hang (trieu dong): ";
        cin >> a[i].gia;
    }
}

void xuat(HangHoa a[], int n) {
    cout << left
         << setw(10) << "Ma hang"
         << setw(25) << "Ten hang"
         << setw(18) << "Ngay xuat"
         << setw(15) << "Gia (trieu)" << '\n';

    for (int i = 0; i < n; i++) {
        cout << left
             << setw(10) << a[i].ma
             << setw(25) << a[i].ten;

        cout << setfill('0')
             << setw(2) << a[i].ngayXuat.ngay << "/"
             << setw(2) << a[i].ngayXuat.thang << "/"
             << setw(4) << a[i].ngayXuat.nam
             << setfill(' ') << "       ";

        cout << fixed << setprecision(2)
             << a[i].gia << '\n';
    }
}

void quickSort(HangHoa a[], int left, int right) {
    int i = left, j = right;
    float pivot = a[(left + right) / 2].gia;

        while (a[i].gia < pivot)
            i++;

        while (a[j].gia > pivot)
            j--;

        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (left < j)
        quickSort(a, left, j);

    if (i < right)
        quickSort(a, i, right);
}

void timKiemNhiPhan(HangHoa a[], int n, float X) {
    int left = 0, right = n - 1;
    int pos = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (fabs(a[mid].gia - X) < 1e-6) {
            pos = mid;
            break;
        }

        if (a[mid].gia < X)
            left = mid + 1;
        else
            right = mid - 1;
    }

    if (pos == -1) {
        cout << "\nKhong tim thay hang hoa co gia " << X
             << " trieu dong.\n";
        return;
    }

    int first = pos, last = pos;

    while (first > 0 &&
           fabs(a[first - 1].gia - X) < 1e-6)
        first--;

    while (last < n - 1 &&
           fabs(a[last + 1].gia - X) < 1e-6)
        last++;

    cout << "\nCac hang hoa co gia xuat hang bang "
         << X << " trieu dong:\n";

    xuat(a + first, last - first + 1);
}

int main() {
    HangHoa a[100];
    int n;
    float X;

    do {
        cout << "Nhap so luong hang hoa (1-100): ";
        cin >> n;
    } while (n < 1 || n > 100);

    cout << "\n========== NHAP HANG HOA ==========\n";
    nhap(a, n);

    cout << "\n========== DANH SACH VUA NHAP ==========\n";
    xuat(a, n);

    quickSort(a, 0, n - 1);

    cout << "\n========== DANH SACH SAU KHI SAP XEP ==========\n";
    xuat(a, n);

    cout << "\nNhap gia X can tim (trieu dong): ";
    cin >> X;

    timKiemNhiPhan(a, n, X);

    return 0;
}

