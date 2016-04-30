import time

def gen_reduced_words(word):
    return [word[:i] + word[i+1:] for i in range(len(word))]


with open('words.txt') as f:
    words = f.read().split()
print('words loaded!')

words_sorted = sorted(words, key=len)
print('words sorted!')

if len(words_sorted) == 0:
    print('no words available')
    exit(0)

reductive_dict = {}
for word in words_sorted:
    if len(word) == 1:
        reductive_dict[word] = None
    else:
        reduced_words = gen_reduced_words(word)
        reduced_words = list(filter(lambda rword: rword in reductive_dict, reduced_words))
        if len(reduced_words) > 0:
            reductive_dict[word] = reduced_words

# --------------------------------------------------
print('Answer: ' + sorted(reductive_dict.keys(), key=len, reverse=True)[0])
print('After 2 seconds, print all of them.')
time.sleep(2)
# --------------------------------------------------

# format: (split, [(plit, ...), (slit, ...)])
def gen_reductive_tree(reductive_dict, cache, word):
    if len(word) <= 1:
        return (word,)
    if word in cache:
        return (word, cache[word])
    rtree = list(map(lambda rword: gen_reductive_tree(reductive_dict, cache, rword), reductive_dict[word]))
    cache[word] = rtree
    return (word, rtree)

'''
split
 plit
  lit
   it
    i
    t
 slit
  sit
   it
    i
    t
  lit
   it
    i
    t
'''
def str_node(node, indent=0):
    display_s = ' ' * indent
    display_s += node[0] + '\n'

    if len(node) <= 1:
        return display_s
    for recur_node in node[1]:
        display_s += str_node(recur_node, indent+1)
    return display_s

reductive_cache = {}
reductive_tree = sorted([gen_reductive_tree(reductive_dict, reductive_cache, word) for word in reductive_dict], key=lambda pair: len(pair[0]))

for node in reductive_tree:
    print(str_node(node))

