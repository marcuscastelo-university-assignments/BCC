#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Group
{
    unordered_set<size_t> members;
    inline size_t size() { return members.size(); }
};

int main(int argc, char const *argv[])
{
    size_t n, m;
    cin >> n >> m;
    vector<Group> groups(m);
    vector<Group *> userGroup(n + 1, nullptr);

    size_t gs;
    for (size_t gi = 0; gi < m; gi++)
    {
        //TODO: tanto faz a ordem de redireçào?
        cin >> gs;
        if (gs == 0) continue;

        vector<size_t> members;
        members.reserve(gs);

        //Initially, try default group
        Group *g = &groups[gi];
        for (size_t i = 0; i < gs; i++)
        {
            size_t m;
            cin >> m;
            members.push_back(m);
            
            //If someone is already part of a group, the greatest one is the new group to be inserted
            if (userGroup[m] != nullptr) {
                if (userGroup[m]->size() > g->members.size())
                    g = userGroup[m];
            }
        }

        for (auto m : members) {
            //If a member is already on a group, 
            if (userGroup[m] != nullptr && userGroup[m] != g) {

                for (auto om : userGroup[m]->members) {
                    g->members.insert(om);
                    userGroup[om] = g;
                }
            } 
            g->members.insert(m);
            userGroup[m] = g;
        }

    }

    for (size_t mi = 1; mi <= n; mi++)
        if (userGroup[mi] == nullptr)
            cout << 1 << " ";
        else
            cout << userGroup[mi]->size() << " ";

    return 0;
}
