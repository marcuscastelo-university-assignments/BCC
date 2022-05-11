#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Group
{
    unordered_set<int> members;
    Group *redirect_to = nullptr;

public:
    void Redirect(Group *to)
    {
        while (to->redirect_to != nullptr)
            to = to->redirect_to;
        

        redirect_to = to;
        for (auto &member : members)
            redirect_to->Insert(member);
    };

    void Insert(int member)
    {
        if (redirect_to != nullptr)
            redirect_to->Insert(member);
        else
            members.insert(member);
    }

    size_t GetSize()
    {
        if (redirect_to != nullptr)
            return redirect_to->GetSize();
        return members.size();
    }
};

int main(int argc, char const *argv[])
{
    int n, m;
    cin >> n >> m;
    vector<Group> groups(m);
    vector<Group *> userGroup(n + 1, nullptr);

    int gs;
    for (int gi = 0; gi < m; gi++)
    {
        //TODO: tanto faz a ordem de redireçào?
        Group *redirected_to = nullptr;
        cin >> gs;
        Group &g = groups[gi];
        for (int i = 0; i < gs; i++)
        {
            int m;
            cin >> m;

            //TODO: redirecionar antes de adicionar o primeiro? O(n * logn) -> O(n + logn) = O(n)
            if (userGroup[m] != nullptr)
            {
                //User already in a group
                if (redirected_to == nullptr) {
                    g.Redirect(userGroup[m]);
                    redirected_to = userGroup[m];
                } else {
                    //If redirection process aready started, move all members of other groups as well
                    userGroup[m]->Redirect(redirected_to);
                }
            }

            g.Insert(m);
            userGroup[m] = &g;
        }
    }

    for (int mi = 1; mi <= n; mi++)
        if (userGroup[mi] == nullptr)
            cout << 1 << " ";
        else
            cout << userGroup[mi]->GetSize() << " ";

    return 0;
}
