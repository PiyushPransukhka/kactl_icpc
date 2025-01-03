/**
 * Author: piyush_pransukhka
 * Date: 2024-12-23
 * License: CC0
 * Source: self
 * Description: Mo's algorithm
 * Time: $O((N + Q) \sqrt{N})$
 * Status: tested
 */

const int block=350;
struct Query {
    int l, r, idx;
    inline pair<int, int> toPair() const {
        return make_pair(l / block, ((l / block) & 1) ? -r : +r);
    }
};

inline bool operator<(const Query &a, const Query &b) {
    return a.toPair() < b.toPair();
}

void remove(int idx){
}  
void add(int idx){
}    
int get_answer(){
}

vector<int> mo_s_algorithm(vector<Query> queries) {
    vector<int> answers(queries.size());
    sort(queries.begin(), queries.end());
    int cur_l = 0,cur_r = -1;
    for (Query q : queries) {
      while (cur_l > q.l)
          cur_l--, add(cur_l);
      while (cur_r < q.r)
          cur_r++, add(cur_r);
      while (cur_l < q.l)
          remove(cur_l), cur_l++;
      while (cur_r > q.r)
          remove(cur_r), cur_r--;
      answers[q.idx] = get_answer();
    }
    return answers;
}