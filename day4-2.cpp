#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

struct Event {
    std::string date;
    std::string desc;
};

std::vector<Event> parseInput(std::ifstream& input)
{
    std::string entry;
    std::stringstream ss;
    std::string tmpstr;
    std::vector<Event> events;
    unsigned fbracket;
    unsigned lbracket;
    while (getline(input, entry)) {
        Event tmpevent;
        fbracket = entry.find('[');
        lbracket = entry.find_last_of(']');
        tmpstr = entry.substr(fbracket + 1, lbracket - fbracket - 1);
        tmpevent.date = tmpstr;
        tmpstr = entry.substr(lbracket - fbracket + 2, entry.size() - 1);
        tmpevent.desc = tmpstr;
        events.push_back(tmpevent);
    }
    return events;
}

int main()
{
    std::ifstream input{"day4.in"};
    std::ofstream output{"day4-2.out"};
    std::vector<Event> events = parseInput(input);
    std::map<int, int> guards; // id to minutes sleeping
    std::map<int, std::map<int, int>>
        sleep_freq_min; // id to (minute to times slept that minute)
    std::sort(
        events.begin(), events.end(),
        [](const Event& lhs, const Event& rhs) { return lhs.date < rhs.date; });

    int id;
    int mm1, mm2;
    for (int i = 0; i < events.size(); ++i) {
        if (events[i].desc.find('#') != std::string::npos) {
            unsigned hash = events[i].desc.find('#');
            unsigned beg = events[i].desc.find('b');
            id = std::stoi(events[i].desc.substr(hash + 1, beg - hash - 2));
        }
        else {
            mm1 = std::stoi(events[i].date.substr(events[i].date.find(':') + 1,
                                                  events[i].date.size() - 1));
            mm2 = std::stoi(
                events[i + 1].date.substr(events[i + 1].date.find(':') + 1,
                                          events[i + 1].date.size() - 1));
            for (int j = mm1; j < mm2; ++j) {
                sleep_freq_min[id][j]++;
            }
            guards[id] += mm2 - mm1;
            ++i;
        }
    }

    int max_id = -1, max_min = -1, max_freq = -1;
    for (auto x : sleep_freq_min) {
        auto max_minute = std::max_element(
            sleep_freq_min[x.first].begin(), sleep_freq_min[x.first].end(),
            [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
                return p1.second < p2.second;
            });
        if (max_minute->second > max_freq) {
            max_min = max_minute->first;
            max_id = x.first;
            max_freq = max_minute->second;
        }
    }

    output << max_id * max_min;
}