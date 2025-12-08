#include "../../include/database/QueryBuilder.h"
#include <sstream>
#include <algorithm>

QueryBuilder::QueryBuilder() 
    : queryType("SELECT"), limitCount(-1), offsetCount(-1) {
}

QueryBuilder& QueryBuilder::select(const std::string& columns) {
    queryType = "SELECT";
    selectColumns = columns;
    return *this;
}

QueryBuilder& QueryBuilder::from(const std::string& table) {
    fromTable = table;
    return *this;
}

QueryBuilder& QueryBuilder::where(const std::string& condition) {
    whereConditions.clear();
    whereConditions.push_back(condition);
    return *this;
}

QueryBuilder& QueryBuilder::andWhere(const std::string& condition) {
    whereConditions.push_back("AND " + condition);
    return *this;
}

QueryBuilder& QueryBuilder::orWhere(const std::string& condition) {
    whereConditions.push_back("OR " + condition);
    return *this;
}

QueryBuilder& QueryBuilder::orderBy(const std::string& column, bool ascending) {
    orderByClause = "ORDER BY " + column + (ascending ? " ASC" : " DESC");
    return *this;
}

QueryBuilder& QueryBuilder::limit(int count) {
    limitCount = count;
    return *this;
}

QueryBuilder& QueryBuilder::offset(int count) {
    offsetCount = count;
    return *this;
}

QueryBuilder& QueryBuilder::join(const std::string& table, const std::string& condition) {
    joinClauses.push_back("JOIN " + table + " ON " + condition);
    return *this;
}

QueryBuilder& QueryBuilder::leftJoin(const std::string& table, const std::string& condition) {
    joinClauses.push_back("LEFT JOIN " + table + " ON " + condition);
    return *this;
}

QueryBuilder& QueryBuilder::rightJoin(const std::string& table, const std::string& condition) {
    joinClauses.push_back("RIGHT JOIN " + table + " ON " + condition);
    return *this;
}

QueryBuilder& QueryBuilder::groupBy(const std::string& column) {
    groupByClause = "GROUP BY " + column;
    return *this;
}

QueryBuilder& QueryBuilder::having(const std::string& condition) {
    havingClause = "HAVING " + condition;
    return *this;
}

QueryBuilder QueryBuilder::insert(const std::string& table) {
    QueryBuilder qb;
    qb.queryType = "INSERT";
    qb.fromTable = table;
    return qb;
}

QueryBuilder& QueryBuilder::values(const std::map<std::string, std::string>& data) {
    insertData = data;
    return *this;
}

QueryBuilder QueryBuilder::update(const std::string& table) {
    QueryBuilder qb;
    qb.queryType = "UPDATE";
    qb.fromTable = table;
    return qb;
}

QueryBuilder& QueryBuilder::set(const std::map<std::string, std::string>& data) {
    updateData = data;
    return *this;
}

QueryBuilder QueryBuilder::deleteFrom(const std::string& table) {
    QueryBuilder qb;
    qb.queryType = "DELETE";
    qb.fromTable = table;
    return qb;
}

std::string QueryBuilder::build() {
    std::ostringstream query;
    
    if (queryType == "SELECT") {
        query << "SELECT " << selectColumns;
        if (!fromTable.empty()) {
            query << " FROM " << fromTable;
        }
        
        for (const auto& join : joinClauses) {
            query << " " << join;
        }
        
        if (!whereConditions.empty()) {
            query << " WHERE ";
            for (size_t i = 0; i < whereConditions.size(); i++) {
                if (i > 0) query << " ";
                query << whereConditions[i];
            }
        }
        
        if (!groupByClause.empty()) {
            query << " " << groupByClause;
        }
        
        if (!havingClause.empty()) {
            query << " " << havingClause;
        }
        
        if (!orderByClause.empty()) {
            query << " " << orderByClause;
        }
        
        if (limitCount >= 0) {
            query << " LIMIT " << limitCount;
        }
        
        if (offsetCount >= 0) {
            query << " OFFSET " << offsetCount;
        }
    }
    else if (queryType == "INSERT") {
        query << "INSERT INTO " << fromTable << " (";
        bool first = true;
        for (const auto& [key, value] : insertData) {
            if (!first) query << ", ";
            query << key;
            first = false;
        }
        query << ") VALUES (";
        first = true;
        for (const auto& [key, value] : insertData) {
            if (!first) query << ", ";
            query << "'" << escapeString(value) << "'";
            first = false;
        }
        query << ")";
    }
    else if (queryType == "UPDATE") {
        query << "UPDATE " << fromTable << " SET ";
        bool first = true;
        for (const auto& [key, value] : updateData) {
            if (!first) query << ", ";
            query << key << " = '" << escapeString(value) << "'";
            first = false;
        }
        
        if (!whereConditions.empty()) {
            query << " WHERE ";
            for (size_t i = 0; i < whereConditions.size(); i++) {
                if (i > 0) query << " ";
                query << whereConditions[i];
            }
        }
    }
    else if (queryType == "DELETE") {
        query << "DELETE FROM " << fromTable;
        if (!whereConditions.empty()) {
            query << " WHERE ";
            for (size_t i = 0; i < whereConditions.size(); i++) {
                if (i > 0) query << " ";
                query << whereConditions[i];
            }
        }
    }
    
    return query.str();
}

void QueryBuilder::reset() {
    queryType = "SELECT";
    selectColumns = "*";
    fromTable.clear();
    whereConditions.clear();
    joinClauses.clear();
    orderByClause.clear();
    groupByClause.clear();
    havingClause.clear();
    limitCount = -1;
    offsetCount = -1;
    insertData.clear();
    updateData.clear();
}

std::string QueryBuilder::escapeString(const std::string& str) {
    std::string escaped = str;
    size_t pos = 0;
    while ((pos = escaped.find("'", pos)) != std::string::npos) {
        escaped.replace(pos, 1, "''");
        pos += 2;
    }
    return escaped;
}

