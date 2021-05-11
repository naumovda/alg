QST = '?'
AST = '*'
LETTERS = frozenset('abcdefghijklmnopqrstuvwxyz')

def check(value, pattern):
    print('*', value, pattern)

    # terminal states
    if pattern == value:
        return True  

    if pattern == '*':
        return True  

    if pattern == '':
        return value == '' 

    # pattern start with QST
    if pattern[0] == QST:
        return check(value[1:], pattern[1:])

    # pattern ends with QST
    if pattern[-1] == QST:
        return check(value[:-1], pattern[:-1])

    # pattern start with letter
    if pattern[0] in LETTERS:
        return value[0] == pattern[0] and check(value[1:], pattern[1:])

    # pattern ends with letter
    if pattern[-1] in LETTERS:
        return value[-1] == pattern[-1] and check(value[:-1], pattern[:-1])

    # find first letter in pattern
    for i in range(len(pattern)):
        if pattern[i] in LETTERS:
        # find letter in value
            j = value.find(pattern[i])
            if j == -1:
                return False
            return check(value[:j], pattern[:i]) and check(value[j+1:], pattern[i+1:])

    # no one letters
    s = 0
    for i in range(len(pattern)):
        if pattern[i] == QST:
            s += 1
    return len(value) >= s
   

def main():
    value = 'foobar'
    pattern = 'f*?????*r'

    print('value =', value)
    print('pattern = ', pattern)
    print('result =', check(value, pattern))

if __name__ == '__main__':
    main()