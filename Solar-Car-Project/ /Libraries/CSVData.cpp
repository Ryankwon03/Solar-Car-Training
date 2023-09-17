#include "CSVData.h"
#include "csvstream.h"

#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <exception>
#include <cassert>

using namespace std;

CSVData::CSVData(std::istream& is): row_count(0)
{
    csvstream csvin(is);

    // This section allows this ADT to work with CSVs that only have
    // a header, and no data.
    vector<string> header = csvin.getheader();
    for (const string& fieldname : header) {
        columns[fieldname] = {};
    }

    map<string, string> row;
    while (csvin >> row) {
        DoubleRow dbl_row;

        for (const auto& [fieldname, datum] : row) {
            dbl_row[fieldname] = stod(datum); // May throw std::invalid_argument.
        }

        append(dbl_row);
    }

    if (columns.empty()) {
        throw invalid_argument("No data was consumed from the stream");
    }

    assert(check_invariant());
}

CSVData::CSVData(const CSVData::Fieldnames_t fieldnames): row_count(0)
{
    if (fieldnames.empty()) {
        throw invalid_argument("Cannot create CSVData objects with no fieldnames");
    }

    for (const string& fieldname : fieldnames) {
        columns[fieldname] = {};
    }

    assert(check_invariant());
}

double CSVData::get(const string& fieldname, size_t index) const
{
    if (index >= row_count) {
        throw invalid_argument("Index out of range");
    }

    auto column_it = columns.find(fieldname);

    if (column_it == columns.end()) {
        throw invalid_argument("Fieldname does not exist in CSV: "+fieldname);
    }

    const Column& col = column_it->second;
    return col.at(index);
}

void CSVData::append(const CSVData::DoubleRow& row)
{
    if (row.size() != columns.size()) {
        string row_size = to_string(row.size());
        string csv_size = to_string(row_count);
        throw invalid_argument("Row width ("+row_size+") does not match the CSV width ("+csv_size+")");
    }

    // First, check that ALL the data can be added.
    for (auto& [fieldname, datum] : row) {
        if (columns.find(fieldname) == columns.end()) {
            throw invalid_argument("Fieldname does not exist in CSV: "+fieldname);
        }
    }

    // Then, we can add the data.
    for (auto& [fieldname, datum] : row) {
        columns[fieldname].push_back(datum);
    }

    ++row_count;

    assert(check_invariant());
}

void CSVData::print(ostream& os) const
{
    if (columns.empty()) {
        return;
    }

    string header;

    for (const auto& [field, column] : columns) {
        header = header + field + ",";
    }

    header.back() = '\n';
    os << header;

    for (size_t i = 0; i < row_count; ++i) {
        string row;
        ostringstream row_oss(row);

        row_oss << std::fixed << std::setprecision(5); // set output to 5 DPs
        bool first = true;
        for(const auto& [field, column] : columns) {
            if (!first) row_oss << ",";
            row_oss << column[i];
            first = false;
        }

        os << row_oss.str() << '\n';
    }
}

void CSVData::clear()
{
    for (auto& [field, column] : columns) {
        column.clear();
    }

    row_count = 0;

    assert(check_invariant());
}

// The invariant is that each column must be the same length.
// A CSV with no fieldnames is not valid, because such a CSV cannot be constructed.
bool CSVData::check_invariant() const
{
    if (columns.empty()) {
        return false;
    }

    for (const auto& [fieldname, column] : columns) {
        if (column.size() != row_count) {
            return false;
        }
    }

    return true;
}
