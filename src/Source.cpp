// ==============================================================
// Simple Average mark calculator interview programming question 
// ==============================================================

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <numeric>

struct SplitLine
{
    std::string id;
    std::string subjectName;
    std::string marks;
};

int processData(std::vector<struct SplitLine> data)
{
    std::multimap<int, int> idMarkMap;
    int avarageOutputMark = 0;

    // insert student id as key and marks as value in multimap, in multimap we can put multiple values for same key
    for (int index = 0; index < data.size(); index++)
    {
        int studentId = std::atoi((data[index].id).c_str());
        int studentMarks = std::atoi((data[index].marks).c_str());
        idMarkMap.insert(std::pair<int, int>(studentId, studentMarks));
    }

    if (!idMarkMap.empty())
    {
        // take the first element of the map, multimap is ordered map hence first studentId will be small id among all inputs
        std::multimap<int, int>::iterator it = idMarkMap.begin();

        // get all the marks for the studentId we found above and aggregate all those marks
        typedef std::pair<std::multimap<int, int>::iterator, std::multimap<int, int>::iterator> rangePair;
        rangePair range = idMarkMap.equal_range(it->first);

        // addition of marks of first student (with smallest roll no)
        avarageOutputMark = std::accumulate(range.first, range.second, 0, [&](int value, std::multimap<int, int>::value_type& p) { return value + p.second;});

        // now calculate the average marks by dividing count of subjects
        avarageOutputMark /= std::distance(range.first, range.second);;
    }

    return avarageOutputMark;
}

int main(void)
{
    std::ifstream in("input.txt");
    std::vector<struct SplitLine> input_data;

    std::string line1;
    std::string line2;

    // read all the lines in file
    while (in)
    {
        struct SplitLine line;

        std::getline(in, line.id, ',');
        std::getline(in, line.subjectName, ',');
        std::getline(in, line.marks);

        if (line.id != "")
        {
            input_data.push_back(line);
        }
    }
    std::ofstream out("output.txt");
    out << processData(input_data) << std::endl;
    return 0;
}