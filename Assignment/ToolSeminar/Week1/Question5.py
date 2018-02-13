from collections import OrderedDict


class dict:
    def __init__(self, n):
        self._dict = OrderedDict()
        self._Max = n  # 最大值
        self._num = 0

    def add(self, key, value):
        self._dict[key] = value
        if self._num < self._Max:
            self._num = self._num + 1
        else:
            self._dict.pop(self._dict.keys()[1])

    def searsh(self, key):
        return self._dict[key]

    def isin(self, key):
        return (key in self._dict)

    def revise(self,key,value):
        if (key in self._dict):
            self._dict[key] = value
        else:
            return -1

    