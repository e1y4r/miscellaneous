bool isMatch(char* s, char* p) {
    if(p[0] == '\0' && s[0] == '\0') {
        return true;
    } else if(p[0] == '\0' || s[0] == '\0'){ 
        return false;
    } else {
        bool firstCharMatch = s[0] != '\0' && (p[0] == s[0] || p[0] == '.');
        if(p[1] == '*') {
            return isMatch(s, p + 2) || (firstCharMatch && isMatch(s + 1, p));
        } else if(p[1] == '+') {
            return (firstCharMatch && isMatch(s + 1, p + 2)) || (isMatch(s + 1, p));
        } else if(p[1] == '?') {
            return (firstCharMatch && isMatch(s + 1, p + 2)) || (isMatch(s, p + 2));
        } else {
            return firstCharMatch && isMatch(s + 1, p + 1);
        }
    }
}