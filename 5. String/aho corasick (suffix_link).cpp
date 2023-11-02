const int K = 26;

struct trie_vertex {
    int next[K];			// trie next character edge
    bool leaf = false;		// leaf node
    int p = -1;				// anchestor
    char pch;				// the character of the edge from p to this vertex
    int link = -1;			// suffix link
    int tlink = -1;			// terminal link
    int go[K];				// automaton
    trie_vertex(int p = -1, char ch = '$') : p(p), pch(ch) {
        fill(begin(next), end(next), -1);
        fill(begin(go), end(go), -1);
    }
};

int go(int v, char ch);

struct aho {
    vector<trie_vertex> t;
    aho() {
        t.resize(1);
    }
    void insert(string const& s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) {
                t[v].next[c] = t.size();
                t.emplace_back(v, ch);
            }
            v = t[v].next[c];
        }
        t[v].leaf = true;
    }
    
    int get_link(int v) {
    	if (t[v].link != -1) return t[v].link;
		if (v == 0 or t[v].p == 0) {
			return t[v].link = 0;
		}
		else {
			return t[v].link = go(get_link(t[v].p), t[v].pch);
    	}
    }
    
    int go(int v, char ch) {
    	int c = ch - 'a';
    	if (t[v].go[c] != -1) return t[v].go[c];
    	if (t[v].next[c] != -1) return t[v].go[c] = t[v].next[c];
    	return t[v].go[c] = v ? go(get_link(v), ch) : 0;
    }
    
    int exitlink(int v) {
    	if (t[v].tlink != -1) return t[v].tlink;
    	int nxt = get_link(v);
    	if (nxt == 0 or t[nxt].leaf) return t[v].tlink = nxt;
    	return t[v].tlink = exitlink(nxt);
    }
    
    int match(string const& s) {
    	int v = 0, res = 0;
    	for (auto c : s) {
    		v = go(v, c);
    		int e = t[v].leaf ? v : exitlink(v);
    		while (e) {
    			res++;
    			e = exitlink(e);
    		}
    	}
    	return res;
    }
};