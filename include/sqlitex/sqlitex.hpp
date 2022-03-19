#ifndef SQLITE_X_HPP
#define SQLITE_X_HPP

#include <string>

#include "sqlite3.h"

namespace sqlitex {

  namespace detail {

  }

  template <typename... Args>
  bool query_one(sqlite3* db, const std::string& sql, std::string& err_msg, Args... args) {
    return true;
  }
}


#endif