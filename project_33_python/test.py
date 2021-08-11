def find_start_idx(str, s1, n):
    s = str
    idx = 0
    for j in range(n):
        i = s.find(s1)
        s = s[i+len(s1):]
        idx += i
        if (j < n-1):
            idx += len(s1)
    return idx

def replace_nth_occ(str, s1, s2, n):
    if str.count(s1) < n:
        print("n ({0}) is too big".format(n))
        return -1
    
    idx = find_start_idx(str, s1, n)
    start=str[:idx]
    end=str[idx+len(s1):]
    return start + s2 + end


str = "asdsdssdSagivsdsdSagivasdasdSagiv"
s1 = "Sagiv"
s2 = "Shiran"
str_new = replace_nth_occ(str, s1, s2, 4)

print("Old string = {0}, New string = {1}".format(str, str_new))