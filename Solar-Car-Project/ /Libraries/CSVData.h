#ifndef CSVDATA_H
#define CSVDATA_H

#include <vector>
#include <string>
#include <map>
#include <iostream>

/*
 * Can be constructed from either an input stream or from a list of fieldnames.
 */

class CSVData {
public:

    /*
     * Get the CSV data from a stream.
     * This will throw invalid_argument if the CSV contains
     * anything besides floating-point data.
     */
    explicit CSVData(std::istream& is);

    /*
     * Start an empty CSV with fieldnames
     */
    using Fieldnames_t = std::vector<std::string>;
    explicit CSVData(const Fieldnames_t fieldnames);

    /*
     * Get the data for a particular fieldname/row
     */
    double get(const std::string& fieldname, size_t index) const;

    /*
     * Add a row.
     */
    using DoubleRow = std::map<std::string, double>;
    void append(const DoubleRow& row);

    /*
     * Get the size of the CSV
     */
    size_t size() const
        { return row_count; }

    /*
     * Print the data to an output stream, in CSV form.
     */
    void print(std::ostream& os) const;

    /*
     * Clear all data, leaving fieldname information intact.
     */
    void clear();

private:
    size_t row_count;

    using Column = std::vector<double>;
    std::map<std::string, Column> columns;

    /*
     * Use this function to check whether your CSVData class has entered a bad state.
     *
     * Consider the following:
     * 1. What constitutes a 'bad state' for the member variables (above)?
     * 2. What should the program do if the state is bad?
     *
     * You should call this function at the end of every non-const function (declared above),
     * including constructors.
     */
    bool check_invariant() const;
};

#endif //!CSVDATA_H
