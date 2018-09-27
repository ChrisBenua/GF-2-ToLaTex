#include <bits/stdc++.h>
//From Chris with Love
using namespace std;
#define int int64_t
#define endl '\n'
#define fi first
#define se second

/*struct matrix {
     
     int n, m;
     
     vector<vector<int>> a;
     matrix() {};
     matrix(int n, int m) {
          this->n = n;
          this->m = m;
          a.resize(n, vector<int>(m));
     }
     matrix(int n, int m, vector<vector<int>> pat) {
          this->n = n;
          this->m = m;
          a = pat;
     }
     
     friend matrix operator * (matrix a, matrix b) {
          if (a.m != b.n) {
               cout << "Error";
               exit(0);
          }
          matrix res(a.n, b.m);
          for (int i = 0; i < res.n; ++i) {
               for (int j = 0; j < res.m; ++j) {
                    for (int k = 0; k < a.m; ++k) {
                         res.a[i][j] += a.a[i][k] * b.a[k][j];
                    }
               }
          }
          return res;
     }
     
     friend matrix operator + (matrix a, matrix b) {
          matrix res(a.n, a.m);
          for (int i = 0; i < a.n; ++i) {
               for (int j = 0; j < a.m; ++j) {
                    res.a[i][j] = a.a[i][j] + b.a[i][j];
               }
          }
          return res;
     }
     
     friend matrix operator - (matrix a, matrix b) {
          matrix res(a.n, a.m);
          for (int i = 0; i < a.n; ++i) {
               for (int j = 0; j < a.m; ++j) {
                    res.a[i][j] = a.a[i][j] - b.a[i][j];
               }
          }
          return res;
     }
     
     friend matrix operator ! (matrix a) {
          matrix res = a;
          res.transpone();
          return res;
     }
     
     void transpone() {
          matrix res(m, n);
          for (int i = 0; i < n; ++i) {
               for (int j = 0; j < m; ++j) {
                    res.a[j][i] = a[i][j];
               }
          }
          swap(n, m);
          a = res.a;
     }
     void show() {
          cout << n << ' ' << m << endl;
          for (int i = 0; i < n;++i) {
               for (int j = 0; j < m; ++j) {
                    cout << a[i][j] << ' ';
               }
               cout << endl;
          }
     }
};*/

vector<int> xorr(vector<int> a, vector<int> b) {
     vector<int> ans(a.size());
     for (int i = 0; i < a.size(); ++i) {
          ans[i] = a[i] ^ b[i];
     }
     return ans;
}

vector<int> SolveLinearSystem(vector<vector<int>> a)
{
     int n = a.size();
     int m = a[0].size();
     set<int> selectedRows;
     vector<vector<int>> mark(n, vector<int>(m));
     for (int st = 0; st < n; ++st) {
          int selectedRow = -1;

          for (int j = 0; j < n; ++j) {
               if (a[j][st] == 1 && !selectedRows.count(j) && selectedRow == -1) {
                    selectedRows.insert(j);
                    selectedRow = j;
                    mark[j][st] = 1;
                    break;
               }
          }
          vector<int> updatedRows;
          //cout << "Selected row: " << selectedRow << endl;
          //cout << "Updated rows: ";
          for (int j = 0; j < n; ++j) {
               if (j == selectedRow) {
                    continue;
               }
               if (a[j][st] == 1) {
                    a[j] = xorr(a[selectedRow], a[j]);
                    //cout << j << " ";
                    updatedRows.push_back(j);
               }
          }
          //if (st != 0) {
               cout << "\\symbolsOnStackRel{";
               for (auto el : updatedRows) {
                    cout << "(" << 7 - el << ')' << "\\oplus" <<  "(" << 7 -selectedRow << ") " << "\\\\";
               }
               cout << "}\\quad";
          //}
          //cout << endl;
          cout << "\\begin{bmatrix}\n";
          for (int i = 0; i < 8; ++i) {
               for (int j = 0; j < 9; ++j) {
                    if (mark[i][j]) {
                         cout << "\\bold{" << a[i][j] << "}";
                    } else {
                         cout << a[i][j];
                    }
                    if (j != 8) {
                         cout << " & ";
                    } else {
                         cout << " \\\\";
                    }
               }
               cout << endl;
          }
          cout << "\\end{bmatrix}";
          cout << endl;
          if (st % 3 == 1)
               cout << endl;
     }
     vector<int> rowIsTrue;
     for (int j = 0; j < n; ++j) {
          if (a[j].back()) {
               rowIsTrue.push_back(j);
          }
     }
     vector<int> ans(n);
     for (auto el : rowIsTrue) {
          int pos = n - 1 - (find(a[el].begin(), a[el].end() - 1, 1) - a[el].begin());
          ans[pos] = 1;
     }
     reverse(ans.begin(), ans.end());
     return ans;
}

signed main()
{
     cout << "ADD IT IN THE TOP OF YOUT LATEX DOC\n";
     cout << "\\newcommand{\\symbolsOnStackRel}[1]{\\xrightarrow{\\substack{#1}}%" << endl;
     cout << endl;
     //srand(time(nullptr));
     vector<vector<int>> a(8, vector<int>(9));
     vector<int> coef = {226, 247, 40, 7, 107, 138, 170, 160, 108};
     for (int i = 0; i < 9; ++i) {
          for (int j =0; j < 8; ++j) {
               if ((coef[i] >> j) & 1) {
                    a[8-j-1][i] = 1;
               }
          }
     }
     for (int i = 0; i < 256; ++i) {
          //!!! YOUR COEF HERE
          //vector<int> coef = {82, 107, 168, 62, 87, 153, 84, 129, 61};
          vector<int> znach(8);
          for (int j = 0; j < 8; ++j) {
               if ((i >> j) & 1) {
                    znach[j] = 1;
               }
          }
          int val = 0;
          for (int j = 0; j < 8; ++j) {
               val ^= coef[j] * znach[j];
          }
          if (val == coef.back()) {
               for (int j = 0; j < 8; ++j) {
                    cout << znach[j] << ' ';
                    //cout << endl;
               }
               cout << endl;
               //return 0;

          }
          
     }
     //TRANSLATE EVER NUMBER TO BINARY
     /*vector<vector<int>> a = {
          {1, 1, 1, 0, 1, 0, 0, 0, 1},
          {1, 0, 1, 1, 0, 1, 0, 1, 1},
          {0, 1, 1, 0, 1, 0, 1, 1, 0},
          {0, 0, 0, 1, 1, 0, 0, 0, 0},
          {0, 1, 0, 0, 1, 0, 1, 0, 0},
          {1, 0, 0, 0, 1, 0, 0, 1, 1},
          {1, 1, 1, 1, 1, 1, 0, 0, 0},
          {1, 0, 1, 1, 1, 1, 0, 1, 0}
     };*/
     /*
     
     vector<vector<int>> a = {
          {0, 0, 1, 0, 0, 1, 0, 1, 0},
          {1, 1, 0, 0, 1, 0, 1, 0, 0},
          {0, 1, 1, 1, 0, 0, 0, 0, 1},
          {1, 0, 0, 1, 1, 1, 1, 0, 1},
          {0, 1, 1, 1, 0, 1, 0, 0, 1},
          {0, 0, 0, 1, 1, 0, 1, 0, 1},
          {1, 1, 0, 1, 1, 0, 0, 0, 0},
          {0, 1, 0, 0, 1, 1, 0, 1, 1}
     };*/
     
     cout << "\\begin{bmatrix}\n";

     for (int i = 0; i < 8; ++i) {
          for (int j = 0; j < 9; ++j) {
               
               cout << a[i][j];
               if (j != 8) {
                    cout << " & ";
               } else {
                    cout << " \\\\";
               }
          }
          cout << endl;
     }
     cout << "\\end{bmatrix}";
     cout << endl;
     //cout << endl << endl;
     vector<int> ans = SolveLinearSystem(a);
     cout << "ANSWER: ";
     for (int i = 0; i < ans.size(); ++i) {
          cout << ans[i] << ' ';
     }
     cout << endl;
     return 0;
}
