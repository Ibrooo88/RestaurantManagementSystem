#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H

#include <string>
#include <vector>
#include <map>

class QueryBuilder {
public:
    QueryBuilder();
    QueryBuilder& select(const std::string& columns = "*");
    QueryBuilder& from(const std::string& table);
    QueryBuilder& where(const std::string& condition);
    QueryBuilder& andWhere(const std::string& condition);
    QueryBuilder& orWhere(const std::string& condition);
    QueryBuilder& orderBy(const std::string& column, bool ascending = true);
    QueryBuilder& limit(int count);
    QueryBuilder& offset(int count);
    QueryBuilder& join(const std::string& table, const std::string& condition);
    QueryBuilder& leftJoin(const std::string& table, const std::string& condition);
    QueryBuilder& rightJoin(const std::string& table, const std::string& condition);
    QueryBuilder& groupBy(const std::string& column);
    QueryBuilder& having(const std::string& condition);
    
    std::string build();
    void reset();
    
    // Insert query builder
    static QueryBuilder insert(const std::string& table);
    QueryBuilder& values(const std::map<std::string, std::string>& data);
    
    // Update query builder
    static QueryBuilder update(const std::string& table);
    QueryBuilder& set(const std::map<std::string, std::string>& data);
    
    // Delete query builder
    static QueryBuilder deleteFrom(const std::string& table);

private:
    std::string queryType;
    std::string selectColumns;
    std::string fromTable;
    std::vector<std::string> whereConditions;
    std::vector<std::string> joinClauses;
    std::string orderByClause;
    std::string groupByClause;
    std::string havingClause;
    int limitCount;
    int offsetCount;
    std::map<std::string, std::string> insertData;
    std::map<std::string, std::string> updateData;
    
    std::string escapeString(const std::string& str);
};

#endif // QUERYBUILDER_H

