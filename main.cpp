#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

// Function prototype
bool euclidean(int a, int b);
void extended_euclid();

// Global variables
vector<vector<int>> lines;

int main(){

    int a;
    int b;

    cout << "First number : ";
    cin >> a;
    cout << "Second number : ";
    cin >> b;

    bool extend = euclidean(a,b);
    
    if (extend){

        cout << "\nRemainder is 1 , running extended euclid\n";
        lines.pop_back();
        reverse(lines.begin(),lines.end());
        extended_euclid();
    }
    else {
        cout << "\nRemainder is not 1, not running extended euclid\n";
    }

}


int find_multiplier(int p, int q){

    assert(p >= q);
    int counter = 1;
    while(p >= q*counter){
        counter++;
    }

    return counter-1;
}

int find_remainder(int p, int q, int k){
    assert(p >= q);
    return p-k*q;
}

bool euclidean(int a,int b){

    // maintain a > b
    if (a < b){

        // swap values 
        int temp = a;
        a = b;
        b = temp;
    }

    // a = kp + r

    cout << "\nEUCLIDEAN\n\n";

    int k = find_multiplier(a,b);
    int r = find_remainder(a,b,k);

    int gcd_equals_one = false;

    while(r > 0){
        k = find_multiplier(a,b);
        r = find_remainder(a,b,k);

        // cur_line format : { a , b , k , r }
        vector<int> cur_line = {a,b,k,r};
        lines.push_back(cur_line);

        if (r == 1){
            gcd_equals_one = true;
        }

        string str_line = to_string(a) + " = " + to_string(k) + "(" + to_string(b) + ") + " + to_string(r);
        if (r != 0) cout << str_line << endl;

        // next step
        a = b;
        b = r;
    }

    cout << endl;
    return gcd_equals_one;
}

vector<int> print_cur_line(vector<int> cur_line,vector<int> next_line){

    int num_stay = cur_line[0];
    int coeff_stay = cur_line[1];
    int num_sub = cur_line[2];
    int coeff_sub = cur_line[3];

    // r always = 1
    // int r = cur_line[3];

    int a = next_line[0];
    int b = next_line[1];
    int k = -next_line[2];
    int r = next_line[3];

    string str_cur_line = to_string(1) + " = " + to_string(coeff_stay) + "(" + to_string(num_stay) + ")" + " + " + to_string(coeff_sub) + "(" + to_string(num_sub) + ")";
    string str_subbed = to_string(a) + " - (" + to_string(k) + ")(" + to_string(b) + ")";
    string str_next_line = to_string(r) + " = " + str_subbed;
    string str_sub_line = to_string(1) + " = " + to_string(coeff_stay) + "(" + to_string(num_stay) + ")" + " + (" + to_string(coeff_sub) + ")(" + str_subbed + ")";
    
    
    int new_coeff_sub = coeff_stay + coeff_sub*k;
    int new_num_sub = num_stay;

    int new_coeff_stay = coeff_sub;
    int new_num_stay = a;

    string str_simplify_line = to_string(1) + " = " + to_string(new_coeff_stay) + "(" + to_string(new_num_stay) + ")" + " + (" + to_string(new_coeff_sub) + ")(" + to_string(new_num_sub) + ")";

    cout << "Previous line: " << endl << str_cur_line << endl;
    cout << "To-be-substitute line: " << endl << str_next_line << endl << endl;
    cout << "Raw substituted line: " << endl << str_sub_line << endl;
    cout << "Simplified line: " << endl << str_simplify_line << endl << endl;

    vector<int> result = {new_num_stay,new_coeff_stay,new_num_sub,new_coeff_sub};
    return result;
    
}

void extended_euclid(){

    cout << "Extended Euclid\n\n";

    vector<int> cur_line = *lines.begin();
    int num_stay = cur_line[0];
    int coeff_stay = 1;
    int num_sub = cur_line[1];
    int coeff_sub = -cur_line[2];

    vector<int> first_line = {num_stay,coeff_stay,num_sub,coeff_sub};
    int count = 1;

    for (vector<vector<int>>::iterator it=lines.begin()+1; it!=lines.end(); ++it){
        cout << "<<<< Line " << to_string(count) << " >>>>\n";
        first_line = print_cur_line(first_line,*it);
        count++;
    }
    
}
