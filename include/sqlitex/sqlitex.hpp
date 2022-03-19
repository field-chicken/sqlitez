#ifndef SQLITE_X_HPP
#define SQLITE_X_HPP

#include <string>
#include <vector>
#include <utility>

#include "sqlite3.h"

namespace sqlitex {

  namespace detail {
    inline void get_column(sqlite3_stmt * stmt, int col, int& n) {
      n = sqlite3_column_int(stmt, col);
    }

    template<typename T>
    T get_column(sqlite3_stmt* stmt, int col) {
      return sqlite3_column_int(stmt, col);
    }

    template <typename... Args, size_t... I>
    void get_columns(sqlite3_stmt * stmt, std::index_sequence<I...>, Args&... args) {
      (get_column(stmt, I, args), ...);
    }

    template <typename... Args, size_t... I, typename T>
    void get_columns(sqlite3_stmt * stmt, std::index_sequence<I...>, std::vector<T>& t) {
      t.emplace_back(get_column<Args>(stmt, I)...);
    }
  }

  template <typename... Args>
  bool query_one(sqlite3* db, const std::string& sql, std::string& err_msg, Args&... args) {
    sqlite3_stmt * stmt;
    int rc = sqlite3_prepare_v2(db, sql.data(), sql.size(), &stmt, nullptr);
    if (rc != SQLITE_OK) {
      sqlite3_finalize(stmt);
      err_msg = "Prepare sql failed";
      return false;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
      detail::get_columns(stmt, std::make_index_sequence<sizeof...(Args)>(), args...);
    } else {
      sqlite3_finalize(stmt);
      return false;
    }
    
    sqlite3_finalize(stmt);
    return true;
  }

  template <typename... Args, typename T>
  bool query(sqlite3* db, const std::string& sql, std::string& err_msg, std::vector<T>& results) {
    sqlite3_stmt * stmt;
    int rc = sqlite3_prepare_v2(db, sql.data(), sql.size(), &stmt, nullptr);
    if (rc != SQLITE_OK) {
      sqlite3_finalize(stmt);
      err_msg = "Prepare sql failed";
      return false;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
      detail::get_columns<Args...>(stmt, std::make_index_sequence<sizeof...(Args)>(), results);
    } 

    sqlite3_finalize(stmt);
    return true;
  }
}


#endif