class Node(object):
    def __init__(self, s):
        self.m_string = s
        self.m_subnodes = []
    def __repr__(self):
        return repr(self.m_string)
'''
    def __str__(self):
        return str((self.m_string, self.m_subnodes))
'''

class CharList(object):
    def __init__(self, char, node_list = None):
        if node_list is None:
            node_list = []
        self.m_char = char
        self.m_node_list = node_list
    def __repr__(self):
        return repr((self.m_char, self.m_node_list))

class SequenceList(object):
    def __init__(self, seq_len, char_list = [CharList(chr(ord('a')+idx)) for idx in range(26)]):
        self.m_seq_len = seq_len
        self.m_char_list = char_list
    def __repr__(self):
        return repr((self.m_seq_len, self.m_char_list))

def find(lst, pred):
    for i in lst:
        if pred(i):
            return i
    return None

def find_word_in_sequence_tree(word, seqtree):
    slen = len(word)
    leading_char = word[0]
    leading_char_ord = ord(leading_char.lower()) - ord('a')
    node_list = seqtree[slen-1].m_char_list[leading_char_ord].m_node_list
    return find(node_list, lambda n: n.m_string == word)

def create_reductive_word_connections(node, seqtree):
    s = node.m_string
    slen = len(s)
    if slen == 1 or slen == 0:
        return
    reduced_words = [s[:i] + s[i+1:] for i in range(slen)]
    for rw in reduced_words:
        found_node = find_word_in_sequence_tree(rw, seqtree)
        if not found_node is None:
            node.m_subnodes.append(found_node)

with open('words.txt') as f:
    words = f.read().split()
print('words loaded!')

words_sorted = sorted(words, key=lambda s: len(s), reverse=True)
print('words sorted!')

if len(words_sorted) == 0:
    print('no words available')
    exit(0)
max_seq_len = len(words_sorted[0])
sequenced_tree = [SequenceList(seq_len) for seq_len in range(max_seq_len)]
for s in reversed(words_sorted):
    slen = len(s)
    leading_char = s[0]
    leading_char_ord = ord(s[0].lower()) - ord('a')
    node = Node(s)
    create_reductive_word_connections(node, sequenced_tree)
    print("({}: {})".format(node.m_string, node.m_subnodes))
    sequenced_tree[slen-1].m_char_list[leading_char_ord].m_node_list.append(node)
