import math


def generator(list):
    if len(list) == 1:
        yield list
    else:
        for i, j in enumerate(list):
            ans = [j]
            lis = list.copy()
            lis.pop(i)
            g = generator(lis)
            for r in range(math.factorial(len(list) - 1)):
                ans += next(g)
                yield ans
                ans = [j]


if __name__ == '__main__':  # Test
    b = [1, 2, 3, 4]
    g = generator(b)
    print(next(g))
    print(next(g))
    print(next(g))
    print(next(g))
    print(next(g))
    print(next(g))
