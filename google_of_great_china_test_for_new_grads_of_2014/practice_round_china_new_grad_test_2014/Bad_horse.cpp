#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<unordered_set>
#include<unordered_map>

using namespace std;

class Bad_horse{
public:
    void solve(){
        string ipath, opath;
        cout << "input file: ";
        cin >> ipath;
        cout << "output file: ";
        cin >> opath;

        ifstream ifs(ipath);
        if(!ifs.is_open()){
            cout << "No " << ipath << " found!" << endl;
            return;
        }
        int count;
        ifs >> count;
        vector<bool> res(count);
        int num;
        for(int i = 0; i < count; i++){
            ifs >> num;
            rules.clear();
            constraints.clear();
            left_set.clear();
            right_set.clear();
            for(int j = 0; j < num; j++){
                string left_member, right_member;
                ifs >> left_member >> right_member;
                rules.push_back(pair<string, string>(left_member, right_member));
            }
            res[i] = canSeperate();
        }
        ifs.close();

        ofstream ofs(opath);
        if(!ofs.is_open()){
            cout << "Can't open " << opath << "!" << endl;
            return;
        }

        for(int i = 0; i < count; i++){
            ofs << "Case #" << i+1 << ": ";
            if(res[i]){
                ofs << "Yes";
            }
            else{
                ofs << "No";
            }
            ofs << endl;
        }
        ofs.close();
    }

private:
    bool canSeperate(){
        for(auto it = rules.begin(); it != rules.end(); it++){
            constraints[it->first].insert(it->second);
            constraints[it->second].insert(it->first);
        }

        return canSeperate(0);
    }

    bool canSeperate(int index){
        if(index == rules.size()){
            return true;
        }

        // left to left_set, right to right_set
        bool flag = true;
        for(auto it = left_set.begin(); it != left_set.end(); it++){
            if(constraints[*it].find(rules[index].first) != constraints[*it].end()){
                flag = false;
                break;
            }
        }
        if(flag){
            for(auto it = right_set.begin(); it != right_set.end(); it++){
                if(constraints[*it].find(rules[index].second) != constraints[*it].end()){
                    flag = false;
                    break;
                }
            }
            if(flag){
                // insert flags, if false, can't erase when recursing
                bool left_flag = true, right_flag = true;
                if(left_set.find(rules[index].first) == left_set.end()){
                    left_set.insert(rules[index].first);
                }
                else{
                    left_flag = false;
                }
                if(right_set.find(rules[index].first) == right_set.end()){
                    right_set.insert(rules[index].second);
                }
                else{
                    right_flag = false;
                }
                if(canSeperate(index + 1)){
                    return true;
                }
                if(left_flag){
                    left_set.erase(rules[index].first);
                }
                if(right_flag){
                    right_set.erase(rules[index].second);
                }
            }
        }

        // left to right_set, right to left_set
        flag = true;
        for(auto it = right_set.begin(); it != right_set.end(); it++){
            if(constraints[*it].find(rules[index].first) != constraints[*it].end()){
                flag = false;
                break;
            }
        }
        if(flag){
            for(auto it = left_set.begin(); it != left_set.end(); it++){
                if(constraints[*it].find(rules[index].second) != constraints[*it].end()){
                    flag = false;
                    break;
                }
            }
            if(flag){
                // insert flags, if false, can't erase when recursing
                bool left_flag = true, right_flag = true;
                if(right_set.find(rules[index].first) == right_set.end()){
                    right_set.insert(rules[index].first);
                }
                else{
                    left_flag = false;
                }
                if(left_set.find(rules[index].first) == left_set.end()){
                    left_set.insert(rules[index].second);
                }
                else{
                    right_flag = false;
                }
                if(canSeperate(index + 1)){
                    return true;
                }
                if(left_flag){
                    right_set.erase(rules[index].first);
                }
                if(right_flag){
                    left_set.erase(rules[index].second);
                }
            }
        }

        return false;
    }

    unordered_map<string, unordered_set<string> > constraints;
    vector<pair<string, string> > rules;
    unordered_set<string> left_set, right_set;
};

int main(int argc, char *argv[]){
    Bad_horse bh;
    bh.solve();
    return 0;
}
