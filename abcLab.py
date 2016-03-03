
import abc
class StackInterface(abc.ABC):
    """
    >>> a = Stack()
    >>> a.push(1)
    >>> a.push(2)
    >>> a.peek()
    2
    >>> a.pop()
    2
    >>> a.pop()
    1
    >>> a.peek()
    >>> a.pop()
    """

    @abc.abstractmethod
    def push(self, value):
        "Push value onto the stack. Return None"

    @abc.abstractmethod
    def pop(self):
        "Pop value from Stack. Return None if nothingon stack"

    @abc.abstractmethod
    def peek(self):
        "Peeak at top of stack. Return None if empty"


class Stack(StackInterface):
    def __init__(self,values=None):
        self._storage = []
        if values:
            for v in values: self.push(v)

    def push(self, value):
        "Push value onto the stack. Return None"
        self._storage.append(value)
        return None

    def pop(self):
        "Pop value from Stack. Return None if nothingon stack"
        if len(self._storage) == 0: return None
        else:
            v = self._storage[-1]
            self._storage = self._storage[:-1]
            return v

    def peek(self):
        "Peeak at top of stack. Return None if empty"
        if len(self._storage) == 0: return None
        else: return self._storage[-1]
