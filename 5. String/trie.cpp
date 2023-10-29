#include <bits/stdc++.h>

// code n drink Pennyroyal tea
#ifdef Pennyroyal
#include <debug.h>
#else
#define debug(...)
#define sdebug(...)
#endif

using namespace std;

namespace tri {
    const int k = 26;
    struct trie_vertex {
        int next[k], cPrefix = 0;
        bool leaf = false;
        trie_vertex() {
            fill(begin(next), end(next), -1);
        }
    };
    struct Trie {
        vector<trie_vertex> trie;
        Trie() {
            trie.resize(1);
        }
        void insert(string const& s) {
            int v = 0;
            for (char ch : s) {
                int c = ch - 'a';
                if (trie[v].next[c] == -1) {
                    trie[v].next[c] = trie.size();
                    trie.emplace_back();
                }
                v = trie[v].next[c];
                trie[v].cPrefix++;
            }
            trie[v].leaf = true;
        }
        int search(string const& key, bool &isWord) {
            int v = 0, level = 0;
            for (char ch : key) {
                int c = ch - 'a';
                v = trie[v].next[c];
                if (v == -1) return -1;
                isWord = trie[v].leaf;
                level++;
            }
            return level;
        }  
        void dbg() {
            for (int vertex = 0; vertex < size(trie); vertex++) {
                auto i = trie[vertex];
                debug(vertex, i.cPrefix, i.leaf);
                sdebug(i.next, k);
            }
        }
    };
}

using namespace tri;

void solve(void) {
    int n, q; cin >> n >> q;
    Trie t;
    for (int i = 1; i <= n; i++) {
        string word; cin >> word;
        t.insert(word);
    }
    while (q--) {
        string s; cin >> s;
        bool isWord = false;
        cout << t.search(s, isWord) << ' ' << isWord << '\n';
    }
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}