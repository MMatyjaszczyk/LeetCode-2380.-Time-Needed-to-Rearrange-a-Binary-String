class Solution {
public:
    int secondsToRemoveOccurrences(std::string s) {
        int iterations = 0;
        bool changed = true;
        while(changed){
            changed = false;
            int ii = 0;
            while(ii < s.length()-1){
                if(s[ii] == '0' and s[ii+1] == '1'){
                    s[ii] = '1';
                    s[ii+1] = '0';
                    ii += 1;
                    change = true;
                }
                ii += 1;
            }
            iterations += 1;
        }
        return iterations - 1;
    }
};