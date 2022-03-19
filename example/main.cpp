#include "sqlitex/sqlitex.hpp"
#include <iostream>
using namespace std;
using namespace sqlitex;

class A {
public:
  A(int a, int b) {}

private:
  int a, b;
};

int main(int argc, char** argv) {
  int n1, n2;
  std::string err_msg;
  auto sql = "";
  sqlite3* db;
  if (sqlite3_open("x", &db) != SQLITE_OK) {
    cerr << "Open db failed" << endl;
  }
  ;
  if (!query_one(db, sql, err_msg, n1, n2)) {
    cerr << err_msg << endl;
  }

  std::vector<A> as;
  if (!query<int, int>(db, sql, err_msg, as)) {
    cerr << err_msg << endl;
  }
  
  cout << "Done" << endl;
  return 0;
}