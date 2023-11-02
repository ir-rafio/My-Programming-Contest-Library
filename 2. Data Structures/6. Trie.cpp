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
    };
}