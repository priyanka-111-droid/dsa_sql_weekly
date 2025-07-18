//Approach-1 (Recur + Memoiz) - 
//T.C :  O(n * 2^n) Because at each index, we eaither split it or not and substr also takes O(n)
class Solution {
public:
    unordered_set<string> st;
    int t[301];
    int n;
    
    bool solve(string &s, int idx) {
        
        if(idx == n) {
            return true;
        }

        if(st.find(s.substr( idx , n - idx )) != st.end()) {
            return true;
        }
        
        if(t[idx] != -1)
            return t[idx];
        
        for(int l = 1; l<=n; l++) {
            
            string temp = s.substr(idx, l);
            if(st.find(temp) != st.end() && solve(s, idx+l))
                return t[idx] = true;
            
        }
        
        return t[idx] = false;
    }
    
    bool wordBreak(string s, vector<string>& wordDict) {
        n = s.length();
        
        memset(t, -1, sizeof(t));
        
        for(string &word : wordDict) {
            st.insert(word);
        }
        
        return solve(s, 0);
    }
};


//Approach-2 (Bottom Up DP)
class Solution {
public:
    bool solve(string s, vector<string>& wordDict) {
        unordered_set<string> st(begin(wordDict), end(wordDict));
        int n = s.length();
        vector<bool> t(n+1, false);
        /*
            t[i] = True;
            It means that for string of length i, its possible to break
            the word such that broken words are in wordDict
        */
        
        t[0] = true; //string of length 0 is always true
        
        for(int i = 1; i<=n; i++) {
            //we choose different point (j) to break
            for(int j = 0; j<i; j++) {
                string temp = s.substr(j, i-j);
                
                if(st.count(temp) && t[j]) {
                    /*
                        It means from s[j...i] is in wordDict
                        And, t[j] = true means s[0...j] could
                        also be broken correctly
                    */
                    
                    t[i] = true;
                    break;
                }
            }
        }
        return t[n]; //length n
    }
    
    bool wordBreak(string s, vector<string>& wordDict) {
        return solve(s, wordDict);
    }
};
