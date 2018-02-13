import collections

deque = collections.deque


class stack:
    def __init__(self):
        self._stack = deque()

    def push(self, x):
        self._stack.append(x)

    def pop(self):
        return self._stack.pop()

    def isempty(self):
        return not (self._stack)
