#include <iostream>;
#include <iomanip>;
#include <bitset>;
using namespace std;

template <size_t bitsetsize>
void shift_bitset(bitset<bitsetsize>* source_bitset);

int main()
{
    int number_type;
    cout << "Whith type do you use?(1 - unsigned int; 0 - long double):" << endl;
    cin >> number_type;
    unsigned int _uint;
    long double _ldouble;
    cout << "Input source\n";
    if (number_type == 1) {
        cin >> _uint;
        cout << "Source(_uint): " << _uint << endl;
        auto bits = bitset<sizeof(unsigned int) * 8>(_uint);
        cout << "bin(_uint): " << bits << endl;
        shift_bitset<sizeof(unsigned int) * 8>(&bits);
        cout << "New value:\n" << (unsigned int)(bits.to_ulong());
    }
    else if (number_type == 0) {
        cin >> _ldouble;
        cout << "Source(long double): " << _ldouble << endl;
        unsigned long long bits_source = *reinterpret_cast<unsigned long long*>(&_ldouble);
        auto bits = bitset<sizeof(long double) * 8>(bits_source);
        cout << "bin(_ldoube): " << bits << endl;

        shift_bitset<sizeof(long double) * 8>(&bits);
        cout << "New value:\n" << (long double)(bits.to_ullong());
    }
    else {
        cout << "Uncorrect type!" << endl;
    }
    
    return 0;
}

template <size_t bitsetsize>
void shift_bitset(bitset<bitsetsize>* source_bitset) {
    cout << "Enter start" << "\n";
    int start;
    cin >> start;
    if (start < 0 || start >= bitsetsize) {
        cout << "Invalid start position" << endl;
        return;
    }

    cout << "Enter area lenght" << "\n";
    int len;
    cin >> len;
    if (len < 0 || len + start >= bitsetsize) {
        cout << "Invalid area len" << endl;
    }

    cout << "Enter shift count(>0 move right; <0 move left)" << "\n";
    int l_count;
    cin >> l_count;
    if (l_count == 0) {
        cout << "No shift" << "\n";
    }
    if (l_count < 0) {
        l_count *= -1;
        for (auto i = 0; i < l_count; i++) {
            bool start_bit = (*source_bitset)[start + len];
            for (auto j = start + len; j > start; j--) {
                (*source_bitset)[j] = (*source_bitset)[j - 1];
            }
            (*source_bitset)[start] = start_bit;
        }
    }
    else {
        for (auto i = 0; i < l_count; i++) {
            bool start_bit = (*source_bitset)[start];
            for (auto j = start; j < start + len - 1; j++) {
                (*source_bitset)[j] = (*source_bitset)[j + 1];
            }
            (*source_bitset)[start + len - 1] = start_bit;
        }
    }
    
    cout << (*source_bitset) << endl;
}
